#pragma once
#include "Main.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wcex = { 0 };

	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//HBRUSH Background = CreateSolidBrush(RGB(170, 0, 196));
	wcex.hbrBackground = B_COLOUR[COLOUR::BACKGROUND] = CreateSolidBrush(RGB(40, 40, 40));;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.lpszClassName = L"File_comparison";
	wcex.lpfnWndProc = WndProc;
	//wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = NULL;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	//wcex.lpszMenuName = NULL;
	//wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassW(&wcex)) { return -1; }

	size_screen_x = GetSystemMetrics(SM_CXSCREEN) - 26;
	size_screen_y = GetSystemMetrics(SM_CYSCREEN) - 79;
	CreateWindow(L"File_comparison", L"File_comparison", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, size_screen_x + 16, size_screen_y + 39, NULL, NULL, NULL, NULL);


	// Main message loop:
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  // обработка событий
{
	switch (message)
	{
		case WM_HSCROLL:   // горизонтальные
		case WM_VSCROLL:   // вертикальные
		{
			Slider *slider = nullptr;

			{
#define SliderCheck(S) if ((S.slider) == (HWND)lParam) { slider = &S; }

				SliderCheck(SliderTextFieldY) else
					SliderCheck(SliderTextFieldLeftX) else
					SliderCheck(SliderTextFieldRightX)

#undef SliderCheck
			}

			if (slider == nullptr) {
				throw "Slider";
			}

			switch (LOWORD(wParam)) {
				case SB_LINERIGHT:     // стрелочки
					slider->Scroll(1);
					break;
				case SB_LINELEFT:     // стрелочки
					slider->Scroll(-1);
					break;
				case SB_PAGERIGHT:     // пустая область
					slider->ScrollPage(1);
					break;
				case SB_PAGELEFT:     // пустая область
					slider->ScrollPage(-1);
					break;
				case SB_THUMBTRACK:    // тянем за ползунок
				//case SB_THUMBPOSITION:  // отпускаем ползунок
					slider->setPos(long(HIWORD(wParam)));
					break;
			}

			break;
		}

		case WM_COMMAND:
		{
			switch (wParam) {
				case IndexButtonChooseFile:
				{
					SetFocus(hWnd);

					RowSelectionButtons.addTextFieldSelectionButton();
					RowSelectionButtons.UpdateAll();

					break;
				}
				case IndexButtonRowTextFieldSelectionScrollLeft:
				{
					SetFocus(hWnd);

					RowSelectionButtons.ScrollLeft();
					RowSelectionButtons.UpdateAll();
					break;
				}
				case IndexButtonRowTextFieldSelectionScrollRight:
				{
					SetFocus(hWnd);

					RowSelectionButtons.ScrollRight();
					RowSelectionButtons.UpdateAll();
					break;
				}
			}

			break;
		}

		case WM_KEYDOWN :
		{
			switch (wParam)
			{
				case 'O':
				{
					if (GetKeyState(VK_CONTROL) & 0x8000) {
						RowSelectionButtons.addTextFieldSelectionButton();
						RowSelectionButtons.UpdateAll();
					}
					break;
				}
			}
			break;
		}

		case WM_LBUTTONDOWN:
		{
			long x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
			RowSelectionButtons.LBUTTONDOWN(x, y);
			RowSelectionButtons.ActiveLeftLBUTTONDOWN(VisualTextFieldLeft.getPART_BUTTON_PRESSED(x, y));
			RowSelectionButtons.ActiveRightLBUTTONDOWN(VisualTextFieldRight.getPART_BUTTON_PRESSED(x, y));
			break;
		}
		case WM_RBUTTONDOWN:
		{
			long x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
			RowSelectionButtons.RBUTTONDOWN(x, y);
			RowSelectionButtons.ActiveLeftRBUTTONDOWN(VisualTextFieldLeft.getPART_BUTTON_PRESSED(x, y));
			RowSelectionButtons.ActiveRightRBUTTONDOWN(VisualTextFieldRight.getPART_BUTTON_PRESSED(x, y));
			break;
		}

		case WM_PAINT:
		{
			MainHdc = BeginPaint(hWnd, &MainPs);

			Draw(MainHdc);

			//SelectObject(MainHdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
			//SelectObject(MainHdc, CreatePen(PS_NULL, 1, RGB(0, 0, 0)));
			//SelectObject(hdc, B_Gray[min(this->free_energy / (limit_energy / 200), 199)]);
			//SelectObject(hdc, (HGDIOBJ)NULL_PEN);
			//SelectObject(MainHdc, B_Gray[0]);
			//Rectangle(MainHdc, 30, 30, 130, 130);
			//SelectObject(MainHdc, B_Gray[140]);
			//Rectangle(MainHdc, 120, 30, 230, 230);
			EndPaint(hWnd, &MainPs);

			//if (!position_WM_SETREDRAW) { SendMessage(hWnd, WM_SETREDRAW, false, 0); }  // убрать отрисовку если она не нужна

			break;
		}

		case WM_SIZE:
		{
			UpdateSizeScreen(hWnd, LOWORD(lParam), HIWORD(lParam));   // это можно перенести в WM_EXITSIZEMOVE только нужно получать размеры экрана
			return 0;
		}


		case WM_CTLCOLORSCROLLBAR:
		case WM_CTLCOLORSTATIC:
		{
			//return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
			SetTextColor((HDC)wParam, RGB(255, 255, 255));  
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (LRESULT)B_COLOUR[COLOUR::BORDERLINE];   // !!!!!!!! поменять 
			break;
		}

		case WM_CREATE:
		{
			InitialSettings(hWnd);

			BuildDrawEffecter(hWnd);
			BuildWidget(hWnd);
			//BuildObject();

			//FullUpdateDraw(hWnd);
			break;
		}
		case WM_DESTROY:
		{
			DestroyDrawEffecter(hWnd);
			DestroyWidget(hWnd);
			//DestroyObject();

			PostQuitMessage(0);
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	}

	return 0;
}







