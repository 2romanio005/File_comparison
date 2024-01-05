#pragma once
#include "Definition.h"

void Draw(HDC hdc);

void UpdateSizeScreen(HWND hWnd, const int size_x, const int size_y);

void MoveWidget();

void UpdateWidget();



void BuildWidget(HWND hWnd);

void BuildDrawEffecter(HWND hWnd);


void DestroyWidget(HWND hWnd);

void DestroyDrawEffecter(HWND hWnd);