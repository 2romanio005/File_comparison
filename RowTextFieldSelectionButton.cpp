#pragma once
#include "Main.h"

RowTextFieldSelectionButton::RowTextFieldSelectionButton()
{
	this->x = 0;
	this->y = 0;
	this->height = 0;
	this->width = 0;
	this->FatherhWnd = nullptr;

	this->SliderX = 0;
	this->arrow_buf = 0;

	this->RowButton_HDC = {};

	this->RowButtons.push_back(VoidTextFieldSelectionButton);
	this->Start = this->RowButtons.begin();
	this->ActiveLeft = this->RowButtons.begin();
	this->ActiveRight = this->RowButtons.begin();

	this->ButtonScrollLeft = this->ButtonScrollRight = nullptr;
}

RowTextFieldSelectionButton::RowTextFieldSelectionButton(long x, long y, long width, long height, HWND FatherhWnd) : RowTextFieldSelectionButton()
{
	this->Create(x, y, width, height, FatherhWnd);
}

RowTextFieldSelectionButton::~RowTextFieldSelectionButton()
{
	DestroyWindow(this->ButtonScrollLeft);
	DestroyWindow(this->ButtonScrollRight);
}

void RowTextFieldSelectionButton::Create(long x, long y, long width, long height, HWND FatherhWnd) {
	this->x = x;
	this->y = y;
	this->height = height;
	//this->SliderX = letter_height + 2 * letter_margin;
	this->width = width;
	this->FatherhWnd = FatherhWnd;

	this->RowButton_HDC.Create(FatherhWnd, width, height);

	this->ButtonScrollLeft = CreateWindowA("BUTTON", "<", WS_CHILD | ES_CENTER, x + width - 2 * (letter_margin + letter_height), y + height - letter_margin - letter_height, letter_height, letter_height, this->FatherhWnd, HMENU(IndexButtonRowTextFieldSelectionScrollLeft), NULL, NULL);
	SendMessage(this->ButtonScrollLeft, WM_SETFONT, WPARAM(F_Main), true);
	this->ButtonScrollRight = CreateWindowA("BUTTON", ">", WS_CHILD | ES_CENTER, x + width - (letter_margin + letter_height), y + height - letter_margin - letter_height, letter_height, letter_height, this->FatherhWnd, HMENU(IndexButtonRowTextFieldSelectionScrollRight), NULL, NULL);
	SendMessage(this->ButtonScrollRight, WM_SETFONT, WPARAM(F_Main), true);

	this->CreateRowButton_HDC();
}



void RowTextFieldSelectionButton::UpdateRowButton() {
	RECT update { this->x, this->y, this->x + this->width - this->arrow_buf, this->y + this->height };
	InvalidateRect(this->FatherhWnd, &update, false);
}

void RowTextFieldSelectionButton::UpdateAll() {
	RECT update { this->x, this->y, this->x + this->width, this->y + this->height };
	InvalidateRect(this->FatherhWnd, &update, false);
	//if (this->arrow_buf > 0) {
	//	UpdateWindow(this->ButtonScrollLeft);
	//	UpdateWindow(this->ButtonScrollRight);
	//}
}



void RowTextFieldSelectionButton::HideArrow()
{
	this->arrow_buf = 0;
	this->SliderX = 0;
	this->Start = this->RowButtons.begin();
	ShowWindow(this->ButtonScrollLeft, SW_HIDE);
	ShowWindow(this->ButtonScrollRight, SW_HIDE);
}

void RowTextFieldSelectionButton::ShowArrow()
{
	this->arrow_buf = 2 * (letter_height + letter_margin);
	ShowWindow(this->ButtonScrollLeft, SW_SHOW);
	ShowWindow(this->ButtonScrollRight, SW_SHOW);
}



void RowTextFieldSelectionButton::Draw(HDC mainHDC)
{
	this->RowButton_HDC.Draw(mainHDC, this->x, this->y, this->width - this->arrow_buf, this->height, this->SliderX, 0, SRCCOPY);
}


void RowTextFieldSelectionButton::addTextFieldSelectionButton() {
	OPENFILENAMEA ofn;
	char PathFile[260] {};
	SetOpenFileParams(this->FatherhWnd, &ofn, PathFile, ".txt", "Частое(*.txt *.cpp *.h)\0*.txt;*.cpp;*.h\0Любой файл(*.*)\0*.*\0\0", OFN_PATHMUSTEXIST);
	if (GetOpenFileNameA(&ofn)) {
		this->addTextFieldSelectionButton(PathFile);
	}
}

void RowTextFieldSelectionButton::addTextFieldSelectionButton(const std::string &path)
{
	int new_x = 0;
	for (auto &button : this->RowButtons) {
		new_x += button.getWidth();
	}

	int iter = path.size();
	while (iter > 0 && path[iter - 1] != '\\') {
		--iter;
	}

	try {
		this->RowButtons.push_back(TextFieldSelectionButton(&(*AllTextField.insert(TextField(path)).first), std::string(path, iter), new_x, 0, this->height));

		iter--;
		for (int i = 0; i < iter; i++)
		{
			LastOpenDirectory[i] = path[i];
		}
		LastOpenDirectory[iter] = '\0';

		std::size_t new_width = (new_x + this->RowButtons.back().getWidth() + this->width - 1) / this->width * this->width;
		if (new_width > this->RowButton_HDC.getWidth()) {
			this->RowButton_HDC.Resize(new_width, this->height);
			this->ShowArrow();

			this->CreateRowButton_HDC();
		}
		else {
			RowButtons.back().Draw(this->RowButton_HDC.supHDC);
		}

		while (this->SliderX + this->width - this->arrow_buf < new_x + this->RowButtons.back().getWidth()) {
			this->ScrollRight();
		}
	}
	catch (const char* str) {
		MessageBoxA(this->FatherhWnd, str, "Ошибка открытия файла!", MB_OK | MB_ICONERROR);
	}
	catch (...) {
		MessageBoxA(this->FatherhWnd, "Возможно неправильный путь или тип файла", "Ошибка открытия файла!", MB_OK | MB_ICONERROR);
	}
}




void RowTextFieldSelectionButton::ScrollLeft()
{
	auto sta = this->RowButtons.begin();
	sta++;
	if (this->Start != sta) {
		this->Start--;
		this->SliderX -= this->Start->getWidth();
	}
}

void RowTextFieldSelectionButton::ScrollRight()
{
	auto end = this->RowButtons.end();
	end--;
	if (this->Start != end) {
		this->SliderX += this->Start->getWidth();
		this->Start++;
	}
}




void RowTextFieldSelectionButton::DeleteTextFieldSelectionButton(std::list<TextFieldSelectionButton>::iterator delete_button)
{
	if (delete_button == this->ActiveLeft) {
		VisualTextFieldLeft.setActiveTextField(VoidTextFieldSelectionButton);
		this->ActiveLeft = this->RowButtons.begin();
	}
	if (delete_button == this->ActiveRight) {
		VisualTextFieldRight.setActiveTextField(VoidTextFieldSelectionButton);
		this->ActiveRight = this->RowButtons.begin();
	}

	std::size_t count = 0;
	TextField const *const eraseTextFiled = delete_button->getTextField();
	for (auto &button : this->RowButtons) {
		count += (eraseTextFiled->getMyHASH() == button.getTextField()->getMyHASH());
	}

	if (count <= 1) {
		std::set<TextField::PairTextFieldComparisonResult>::iterator iter = AllPairTextFieldComparisonResult.begin();
		while (iter != AllPairTextFieldComparisonResult.end()) {
			if (iter->basic == TextField::PairTextFieldComparisonResult::TextFieldComparisonResult { eraseTextFiled->getMyHASH() } ||
				iter->secondary == TextField::PairTextFieldComparisonResult::TextFieldComparisonResult { eraseTextFiled->getMyHASH() })
			{
				std::set<TextField::PairTextFieldComparisonResult>::iterator erase_iter = iter;
				iter++;
				AllPairTextFieldComparisonResult.erase(erase_iter);
			}
			else
			{
				iter++;
			}
		}

		AllTextField.erase(*eraseTextFiled);
	}


	if (this->Start == delete_button) {
		this->Start++;
		if (this->RowButtons.size() > 1 && this->Start == this->RowButtons.end()) {
			this->Start--;
			this->ScrollLeft();
		}
	}
	this->RowButtons.erase(delete_button);

	int new_x = 0;
	for (auto &button : this->RowButtons) {
		new_x += button.getWidth();
	}
	std::size_t new_width = (std::max)((new_x + this->width - 1) / this->width, long(1)) * this->width;
	if (new_width < this->RowButton_HDC.getWidth()) {
		this->RowButton_HDC.Resize(new_width, this->height);
		this->HideArrow();
	}

	this->CreateRowButton_HDC();
}


void RowTextFieldSelectionButton::CreateRowButton_HDC() {
	SelectObject(this->RowButton_HDC.supHDC, B_COLOUR[COLOUR::BACKGROUND]);
	Rectangle(this->RowButton_HDC.supHDC, 0, 0, this->RowButton_HDC.getWidth() + 1, this->height + 1);

	int iter_x = 0;


	for (auto &button : RowButtons) {
		button.setPosition(iter_x, this->y);
		iter_x += button.getWidth();
		button.Draw(this->RowButton_HDC.supHDC);
	}

	//this->DrawActiveButton(this->ActiveLeft, COLOUR::ERASED);
	//this->DrawActiveButton(this->ActiveRight, COLOUR::ADDED);
}

void RowTextFieldSelectionButton::DrawActiveButton(std::list<TextFieldSelectionButton>::iterator ActiveButton, COLOUR top_colour)
{
	/*if (ActiveButton != this->RowButtons.end()) {
		ActiveButton->setTopColour(top_colour);
		ActiveButton->DrawTop(this->RowButton_HDC.supHDC);
	}*/
	ActiveButton->setTopColour(top_colour);
	ActiveButton->DrawTop(this->RowButton_HDC.supHDC);
}







