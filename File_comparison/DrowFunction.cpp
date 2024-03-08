#pragma once
#include "Main.h"




void Draw(HDC mainHDC) {
	//HDC tmp = GetDC(TextFieldLeft.StaticText);
	//BitBlt(hdc, screen_middle + 40, margin_y + 40, screen_middle - 20 - margin_x, size_screen_y - margin_y - 40 - margin_y, tmp, 0, SliderTextFieldY.getPos(), SRCCOPY);
	//BitBlt(hdc, margin_x + 10, margin_y + 40, screen_middle - 20 - margin_x, size_screen_y - margin_y - 40 - margin_y, TextFieldLeft.LineColour_HDC, 0, SliderTextFieldY.getPos(), SRCCOPY);
	RowSelectionButtons.Draw(mainHDC);

	VisualTextFieldLeft.Draw(mainHDC);
	VisualTextFieldRight.Draw(mainHDC);
}

//void FullUpdateDraw(HWND hWnd)
//{
//	UpdateDraw(hWnd);
//	DrawInterface();
//}
//
//void UpdateDraw(HWND hWnd) {
//	int x = margin_x + FlagFullscreen * (size_screen_x - 2 * margin_x - size_cell * size_map_x) / 2;
//	int y = margin_y + FlagFullscreen * (size_screen_y - 2 * margin_y - size_cell * size_map_y) / 2;
//	RECT update{ x, y, x + size_cell * size_map_x, y + size_cell * size_map_y };
//	InvalidateRect(hWnd, &update, false);
//}


void UpdateSizeScreen(HWND hWnd, const int size_x, const int size_y)
{
	size_screen_x = size_x;
	size_screen_y = size_y;

	MoveWidget();
	UpdateWidget();
}

void MoveWidget()
{
}

void UpdateWidget()
{
	RowSelectionButtons.UpdateAll();
	UpdateWindow(ButtonChooseFile);

	SliderTextFieldY.Update();
	SliderTextFieldLeftX.Update();
	SliderTextFieldRightX.Update();

	VisualTextFieldLeft.UpdateAll();
	VisualTextFieldRight.UpdateAll();
}





void BuildWidget(HWND hWnd) {
	//TextField::PairTextFieldComparisonResult::CompareTextField(*VoidTextFieldSelectionButton.getTextField(), *VoidTextFieldSelectionButton.getTextField());
	//CreateWindowA("BUTTON", "", WS_VISIBLE | WS_CHILD | ES_CENTER, width + screen_middle - 1, height + 100, 1, 1000, hWnd, HMENU(0), NULL, NULL);
	//SliderTextFieldY.slider = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);

	//SliderTextFieldY.Create(NULL, WS_VISIBLE | WS_CHILD | SBS_VERT, width, height += 20, 220, 20, hWnd);
	//CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);

	int height = 0;
	int width = margin_x;
	int new_size_sceen_x = size_screen_x - slider_width - 2 * margin_x;
	//int screen_middle_x = (size_screen_x - letter_height) / 2;

	// выбор файлов
	RowSelectionButtons.Create(width, height, new_size_sceen_x - letter_height - 2 * letter_margin - RowTextFeildSelectionButtonTopSize, letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize, hWnd);

	// добавление файлов
	ButtonChooseFile = CreateWindowA("BUTTON", "+", WS_VISIBLE | WS_CHILD | ES_CENTER, width + new_size_sceen_x - letter_height - letter_margin, height + letter_margin + RowTextFeildSelectionButtonTopSize, letter_height, letter_height, hWnd, HMENU(IndexButtonChooseFile), NULL, NULL);
	SendMessage(ButtonChooseFile, WM_SETFONT, WPARAM(F_Main), true);
	/*
		ButtonChooseFile = CreateWindowA("BUTTON", "+", WS_VISIBLE | WS_CHILD | ES_CENTER, width + (screen_middle - margin_x) / 2 - 60, height, 120, 20, hWnd, HMENU(IndexButtonChooseFileLeft), NULL, NULL);
	SendMessage(ButtonChooseFileLeft, WM_SETFONT, WPARAM(F_Main), true);
	*/
#define space_between 10
	height += letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize + margin_y;
	// левое поле
	VisualTextFieldLeft.Create(width, height, new_size_sceen_x / 2 - space_between, size_screen_y - height - slider_width, hWnd);

	// правое поле
	width += new_size_sceen_x / 2 + space_between;
	VisualTextFieldRight.Create(width, height, new_size_sceen_x / 2 - space_between, size_screen_y - height - slider_width, hWnd);

	// Y слайдер
	width += new_size_sceen_x / 2 - space_between + margin_x;
	SliderTextFieldY.Create(NULL, WS_VISIBLE | WS_CHILD | SBS_VERT, width, height + letter_height, slider_width, size_screen_y - height - slider_width - letter_height, hWnd);
	SliderTextFieldY.stepPage = (std::max)(VisualTextFieldLeft.getNumberVisiblePixelRows(), VisualTextFieldRight.getNumberVisiblePixelRows()) - letter_height;



	width = margin_x;
	height = size_screen_y - slider_width;
	// левый слайдер
	SliderTextFieldLeftX.Create(NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height, new_size_sceen_x / 2 - space_between, slider_width, hWnd);
	SliderTextFieldLeftX.stepPage = VisualTextFieldLeft.getNumberVisiblePixelColumns() - letter_width;

	// правый слайдер
	width += new_size_sceen_x / 2 + space_between;
	SliderTextFieldRightX.Create(NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height, new_size_sceen_x / 2 - space_between, slider_width, hWnd);
	SliderTextFieldRightX.stepPage = VisualTextFieldRight.getNumberVisiblePixelColumns() - letter_width;


	// заполнить текстовые поля
	VisualTextFieldLeft.setActiveTextField(VoidTextFieldSelectionButton);

	// ###############
	//for (int i = 0; i < 7; i++)
	//{
	//	try {
	//		RowSelectionButtons.addTextFieldSelectionButton("F:\\Папка с програми Романа\\Projects\\C++\\Полезные проги\\File_comparison\\Test\\MORE_L1.txt");
	//	}
	//	catch (...) {
	//		MessageBoxA(hWnd, "Ошибка открытия файла.", "Ошибка!", MB_OK | MB_ICONERROR);
	//	}
	//}
	//RowSelectionButtons.UpdateAll();
}

void BuildDrawEffecter(HWND hWnd) {
	//UpdateSizeScreen(hWnd, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//DPIScale::Initialize(hWnd);


	//HDC hdc;        //создаём контекст устройства
	//PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

	//hdc = BeginPaint(hWnd, &ps);
	//SupHdc = CreateCompatibleDC(hdc);
	//SupHbm = CreateCompatibleBitmap(hdc, size_cell * size_map_x, size_cell * size_map_y);
	//SupHold = SelectObject(SupHdc, SupHbm);
	//EndPaint(hWnd, &ps);

	B_COLOUR[COLOUR::ERASED] = CreateSolidBrush(RGB(255, 0, 0));
	B_COLOUR[COLOUR::ADDED] = CreateSolidBrush(RGB(0, 255, 0));
	B_COLOUR[COLOUR::CHANGED] = CreateSolidBrush(RGB(0, 0, 255));
	B_COLOUR[COLOUR::NOT_CHANGED] = B_COLOUR[COLOUR::BACKGROUND]; //CreateSolidBrush(RGB(40, 40, 40));
	B_COLOUR[COLOUR::EMPTY] = CreateSolidBrush(RGB(0, 0, 0));

	B_COLOUR[COLOUR::SYMBOL] = CreateSolidBrush(RGB(255, 255, 255));
	B_COLOUR[COLOUR::BORDERLINE] = CreateSolidBrush(RGB(100, 100, 100));

	P_Null = CreatePen(PS_NULL, 1, RGB(255, 255, 255));

	F_Main = CreateFontA(start_letter_height, start_letter_width, 0, 0, FW_REGULAR, false, false, false, RUSSIAN_CHARSET/*DEFAULT_CHARSET*/, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FIXED_PITCH | FF_MODERN, "Courier New");

	HDC tmp_hdc = GetDC(NULL);
	SelectObject(tmp_hdc, F_Main);
	TEXTMETRIC tm;
	GetTextMetrics(tmp_hdc, &tm);
	
	letter_width = tm.tmAveCharWidth;
	letter_height = tm.tmHeight;

	

	//void (*ReadI)(HDC & I_, std::string way) = [](HDC& I_, std::string way) {
	//	I_ = CreateCompatibleDC(hdcMem);
	//	HANDLE tmp = LoadImageA(NULL, way.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//	SelectObject(I_, tmp);
	//	DeleteObject(tmp);
	//};

	//ReadI(I_Player, "images\\I_Player.bmp");
}



void DestroyWidget(HWND hWnd) {
	DestroyWindow(ButtonChooseFile);

	//DestroyWindow(ButtonChooseFileRight);
}

void DestroyDrawEffecter(HWND hWnd) {
	for (unsigned int i = 0; i < B_COLOUR.size(); i++)
	{
		DeleteObject(B_COLOUR[i]);
	}
	DeleteObject(P_Null);

	DeleteObject(F_Main);
}

