#pragma once
#include "Main.h"

void InitialSettings(HWND hWnd) {
	int size = GetCurrentDirectoryA(266, LastOpenDirectory);
	//for (int i = 0; i < 22; i++)
	//{
	//	LastOpenDirectory[size + i] = "\\Saves_Life_simulation"[i];
	//}
	if (size <= 260) {
		for (int i = 0; i < 5; i++)
		{
			LastOpenDirectory[size + i] = "\\Test"[i];  // !!!!!!!!!!!!   // ################
		}
	}
	CreateDirectoryA(LastOpenDirectory, NULL);

	// SendMessage(hWnd, WM_SETFONT, WPARAM(F_Main), true); 
}

void SetOpenFileParams(HWND hWnd, OPENFILENAMEA *ofn, char *path, const char *def_expansion, const char *filter, DWORD flag) {
	ZeroMemory(ofn, sizeof(*ofn));

	ofn->lStructSize = sizeof(*ofn);
	ofn->hwndOwner = hWnd;
	ofn->lpstrFile = path;
	ofn->nMaxFile = 260;
	ofn->lpstrFilter = filter;
	ofn->lpstrFileTitle = NULL;
	ofn->nMaxFileTitle = 0;
	ofn->lpstrInitialDir = LastOpenDirectory;
	ofn->lpstrDefExt = def_expansion;
	ofn->Flags = flag;
}

bool CheckExpansion(const char *check_expansion, const char *right_expansion, unsigned int size) {
	for (unsigned int i = 0; i < size; i++) {
		if (check_expansion[i] != right_expansion[i]) {
			return true;
		}
	}
	return false;
}



