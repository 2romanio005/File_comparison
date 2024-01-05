#pragma once
#include "Definition.h"

void InitialSettings(HWND hWnd);

void SetOpenFileParams(HWND hWnd, OPENFILENAMEA *ofn, char *path, const char *def_expansion, const char *filter, DWORD flag);
bool CheckExpansion(const char *check_expansion, const char *right_expansion, unsigned int size = 3);



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



