#pragma once
#include "Main.h"


VisualTextField::VisualTextField(const TextFieldSelectionButton &ActiveTextField)
{
	this->ActiveComparisonResult = nullptr;;
	this->ActiveTextField = new TextFieldSelectionButton(ActiveTextField);

	this->ScrollPosY = 0;
	this->ScrollPosX = 0;
	this->LastUpdateScrollPosY = 0;

	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;

	this->margin_top = 0;
	this->margin_bottom = 0;
	this->margin_left = 0;

	this->NumberVisibleRows = 0;
	this->NumberVisiblePixelRows = 0;

	this->NumberVisibleColumns = 0;
	this->NumberPixelColumns = 0;
	this->NumberVisiblePixelColumns = 0;

	this->FatherhWnd = nullptr;

	this->ColourText_HDC = {};
	this->Number_HDC = {};
}

VisualTextField::~VisualTextField()
{
	delete this->ActiveTextField;
}

void VisualTextField::Create(long x, long y, long width, long height, HWND hWnd)
{
	this->FatherhWnd = hWnd;

	this->x = x;
	this->y = y;
	this->setWidth(width);
	this->setHeight(height);

	this->setMargin_top(letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize);
	this->setMargin_bottom(1);
	this->setMargin_right(1);
	//this->setMargin_bottom(0);

	this->ActiveTextField->setPosition(0, 0);
	this->ActiveTextField->resize(this->width + 1, letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize);

	//this->StaticFileName = CreateWindowA("STATIC", "", WS_VISIBLE | WS_CHILD | ES_CENTER, x, y, width, letter_height, hWnd, NULL, NULL, NULL);
	//SendMessage(this->StaticFileName, WM_SETFONT, WPARAM(F_Main), true);
	this->FileName_HDC.Create(this->FatherhWnd, this->width, letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize);
	this->Number_HDC.Create(this->FatherhWnd, this->margin_left, (this->getNumberVisibleRows() + 1) * letter_height);
	this->ColourText_HDC.Create(this->FatherhWnd, this->getNumberPixelColumns(), (this->getNumberVisibleRows() + 1) * letter_height);
}



void VisualTextField::UpdateText()
{
	RECT update { this->x, this->y + this->margin_top, this->x + this->width, this->y + this->height - this->margin_bottom };
	InvalidateRect(this->FatherhWnd, &update, false);
}

void VisualTextField::UpdateAll()
{
	RECT update { this->x, this->y, this->x + this->width, this->y + this->height};
	InvalidateRect(this->FatherhWnd, &update, false);
}

void VisualTextField::Draw(HDC hdc)
{
	/*this->ActiveTextField->Draw(hdc);*/
	this->FileName_HDC.Draw(hdc, this->x, this->y, this->width, letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize, 0, 0, SRCCOPY);

	this->Number_HDC.DrawLoopedY(hdc, this->x, this->y + this->margin_top, this->margin_left, this->height - this->margin_top - this->margin_bottom, 0, this->ScrollPosY % ((this->getNumberVisibleRows() + 1) * letter_height), SRCCOPY);
	this->ColourText_HDC.DrawLoopedY(hdc, this->x + this->margin_left, this->y + this->margin_top, this->NumberVisiblePixelColumns, this->height - this->margin_top - this->margin_bottom, this->ScrollPosX, this->ScrollPosY % ((this->getNumberVisibleRows() + 1) * letter_height), SRCCOPY);

	SelectObject(hdc, P_Null);
	SelectObject(hdc, B_COLOUR[COLOUR::BORDERLINE]);
	Rectangle(hdc, this->x + this->width - this->margin_right, this->y + this->margin_top, this->x + this->width + 1, this->y + this->height + 1);

	//BitBlt(hdc, this->x, this->y + this->margin_top, 10, this->getNumberVisiblePixelRows(), this->ColourText_HDC.supHDC, 0, this->ScrollPos, SRCCOPY);  // слева
	//BitBlt(hdc, this->x + this->width - 10, this->y + this->margin_top, 10, this->getNumberVisiblePixelRows(), this->ColourText_HDC.supHDC, 0, this->ScrollPos, SRCCOPY);  // спарва
	//long ost = this->getNumberVisiblePixelRows() + SliderTextFieldY.getPos() - this->getNumberRows() * letter_height;
	//if (ost > 0) {
	//	SelectObject(hdc, P_Null);
	//	SelectObject(hdc, B_COLOUR[COLOUR::NOT_CHANGED]);
	//	Rectangle(hdc, this->x, this->y + this->height - ost, this->x + 11, this->y + this->height + 1);
	//	Rectangle(hdc, this->x + this->width - 10, this->y + this->height - ost, this->x + this->width + 1, this->y + this->height + 1);
	//}
}


void VisualTextField::Resize(long width, long height)
{
	this->setWidth(width);
	this->setHeight(height);

	this->FileName_HDC.Resize(this->width, letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize);
	this->ActiveTextField->resize(this->width + 1, letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize);

	this->Number_HDC.Resize(this->margin_left, (this->getNumberVisibleRows() + 1) * letter_height);
	this->ColourText_HDC.Resize(this->getNumberPixelColumns(), (this->getNumberVisibleRows() + 1) * letter_height);

	this->CreateColourText_HDC();
}

void VisualTextField::ScrollY(long changes)
{
	this->ScrollPosY += changes;
	while (this->ScrollPosY - this->LastUpdateScrollPosY > letter_height) {
		this->CreateRowColourText_HDC(LastUpdateScrollPosY / letter_height + this->getNumberVisibleRows() + 1, this->LastUpdateScrollPosY);
		LastUpdateScrollPosY += letter_height;
	}
	while (this->ScrollPosY - this->LastUpdateScrollPosY < 0) {
		LastUpdateScrollPosY -= letter_height;
		this->CreateRowColourText_HDC(LastUpdateScrollPosY / letter_height, this->LastUpdateScrollPosY);
	}
}

void VisualTextField::ScrollX(long changes)
{
	this->ScrollPosX += changes;
}






void VisualTextField::CreateColourText_HDC()
{
	//SetBkMode(this->FileName_HDC.supHDC, TRANSPARENT);
	//SetTextColor(this->FileName_HDC.supHDC, RGB(255, 255, 255));   // !!!!!!!!! цвет
	//SelectObject(this->FileName_HDC.supHDC, P_Null);
	//SetBkMode(this->Number_HDC.supHDC, TRANSPARENT);
	//SetTextColor(this->Number_HDC.supHDC, RGB(255, 255, 255));   // !!!!!!!!! цвет
	//SelectObject(this->Number_HDC.supHDC, P_Null);
	//SetBkMode(this->ColourText_HDC.supHDC, TRANSPARENT);
	//SetTextColor(this->ColourText_HDC.supHDC, RGB(255, 255, 255));   // !!!!!!!!! цвет
	//SelectObject(this->ColourText_HDC.supHDC, P_Null);

	SelectObject(this->FileName_HDC.supHDC, B_COLOUR[COLOUR::BORDERLINE]);
	Rectangle(this->FileName_HDC.supHDC, 0, 0, this->FileName_HDC.getWidth() + 1, this->height + 1);
	if (this->ActiveTextField->getFileName().size() > 0) {
		this->ActiveTextField->Draw(this->FileName_HDC.supHDC);
	}
	else {
		this->ActiveTextField->DrawTop(this->FileName_HDC.supHDC);
	}

	for (long i = LastUpdateScrollPosY / letter_height; i < LastUpdateScrollPosY / letter_height + this->getNumberVisibleRows() + 1; i++)
	{
		this->CreateRowColourText_HDC(i, i * letter_height);
	}
}

void VisualTextField::CreateRowColourText_HDC(std::size_t row_index/*, int x*/, long y) {
	y %= (this->getNumberVisibleRows() + 1) * letter_height;
	HDC Text_HDC = this->ColourText_HDC.supHDC;
	HDC Num_HDC = this->Number_HDC.supHDC;


	SelectObject(Num_HDC, B_COLOUR[COLOUR::BORDERLINE]);
	Rectangle(Num_HDC, 0, y, 2, y + letter_height + 1);

	if (long(row_index) >= this->getNumberRows()) {
		SelectObject(Text_HDC, B_COLOUR[COLOUR::BACKGROUND]);
		Rectangle(Text_HDC, 0, y, this->getNumberPixelColumns() + 1, y + letter_height + 1);
		SelectObject(Num_HDC, B_COLOUR[COLOUR::BACKGROUND]);
		Rectangle(Num_HDC, 1, y, this->margin_left + 1, y + letter_height + 1);
		return;
	}
	Rectangle(Num_HDC, this->margin_left - 8, y, this->margin_left + 1, y + letter_height + 1);

	std::vector<COLOUR> const &row_col = (*this->ActiveComparisonResult)[row_index].ColourRow;
	TextField::TextLenthRow const &row_text = *(*this->ActiveComparisonResult)[row_index].TextLenthRow;

	//long((std::min)(this->getNumberVisibleColumns() + 1, this->TextLenth[i].second.size())); j++)
	SelectObject(Text_HDC, B_COLOUR[row_col[0]]);
	if (row_col[0] != COLOUR::CHANGED) {
		Rectangle(Text_HDC, 0, y, this->getNumberPixelColumns() + 1, y + letter_height + 1);
	}
	else {
		for (std::size_t i = 0; i < row_text.lenth; i++)
		{
			SelectObject(Text_HDC, B_COLOUR[row_col[i + 1]]);
			Rectangle(Text_HDC, letter_width * i, y, letter_width * (i + 1) + 1, y + letter_height + 1);
		}
	}

	SelectObject(Num_HDC, B_COLOUR[row_col[0]]);
	Rectangle(Num_HDC, 1, y, this->margin_left - 8 + 1, y + letter_height + 1);
	RECT word_place { 1, y, this->margin_left - 8, y + letter_height };
	DrawTextA(Num_HDC, LPCSTR(std::to_string(row_index + 1).c_str()), -1, &word_place, DT_RIGHT);
	if (row_col[0] != COLOUR::EMPTY) {
		long ost = this->getNumberPixelColumns() - this->margin_left - row_text.lenth * letter_width;
		if (ost > 0) {
			SelectObject(Text_HDC, B_COLOUR[COLOUR::BACKGROUND]);
			Rectangle(Text_HDC, row_text.lenth * letter_width, y, this->getNumberPixelColumns() + 1, y + letter_height + 1);
		}
		word_place = {0, y, this->getNumberPixelColumns(), y + letter_height };
		DrawTextA(Text_HDC, LPCSTR(row_text.text.c_str()), -1, &word_place, DT_LEFT | DT_EXPANDTABS | DT_TABSTOP | (tab_len << 8));
	}
}





