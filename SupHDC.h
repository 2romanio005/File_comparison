#pragma once
#include "0Include.h"

class SupHDC
{
public:
	SupHDC();
	SupHDC(HWND FatherhWnd, std::size_t width, std::size_t height);
	~SupHDC();

	void Create(HWND FatherhWnd, std::size_t width, std::size_t height);
	void Resize(std::size_t width, std::size_t height);
	void Clear();

	std::size_t getWidth();
	std::size_t getHeight();

	void Draw(HDC mainHDC, int mx, int my, int width, int height, int sx, int sy, DWORD rop) const;
	void DrawLoopedY(HDC mainHDC, int mx, int my, int width, int height, int sx, int sy, DWORD rop) const;
	void DrawLoopedX(HDC mainHDC, int mx, int my, int width, int height, int sx, int sy, DWORD rop) const;
	// !!!!!!!!!!!!!!!! добавить по обеим одновременно

	HDC supHDC;
private:
	std::size_t width, height;
	HWND FatherhWnd;

	HBITMAP supHBM;
	HANDLE supHOLD;
};

