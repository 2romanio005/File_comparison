#pragma once
#include "Main.h"

SupHDC::SupHDC()
{
	this->width = 0;
	this->height = 0;

	this->FatherhWnd = nullptr;
	this->supHDC = nullptr;
	this->supHBM = nullptr;
	this->supHOLD = nullptr;
}

SupHDC::SupHDC(HWND FatherhWnd, std::size_t width, std::size_t height) : SupHDC()
{
	this->Create(FatherhWnd, width, height);
}

SupHDC::~SupHDC()
{
	this->Clear();
}


void SupHDC::Create(HWND FatherhWnd, std::size_t width, std::size_t height)
{
	this->FatherhWnd = FatherhWnd;
	this->width = width;
	this->height = height;

	HDC tmpHDC;
	PAINTSTRUCT ps;
	tmpHDC = BeginPaint(this->FatherhWnd, &ps);
	this->supHDC = CreateCompatibleDC(tmpHDC);
	this->supHBM = CreateCompatibleBitmap(tmpHDC, width, height);
	this->supHOLD = SelectObject(this->supHDC, this->supHBM);
	EndPaint(this->FatherhWnd, &ps);

	SelectObject(this->supHDC, F_Main);

	SetBkMode(this->supHDC, TRANSPARENT);
	SetTextColor(this->supHDC, RGB(255, 255, 255));   // !!!!!!!!! цвет
	SelectObject(this->supHDC, P_Null);
}

void SupHDC::Resize(std::size_t width, std::size_t height)
{
	if (this->width != width || this->height != height) {
		this->Clear();

		this->Create(this->FatherhWnd, width, height);
	}
}

void SupHDC::Clear()
{
	SelectObject(this->supHDC, GetStockObject(NULL_BRUSH));

	SelectObject(this->supHDC, this->supHOLD);
	DeleteObject(this->supHBM);
	DeleteDC(this->supHDC);
}


std::size_t SupHDC::getWidth()
{
	return this->width;
}

std::size_t SupHDC::getHeight()
{
	return this->height;
}



void SupHDC::Draw(HDC mainHDC, int mx, int my, int width, int height, int sx, int sy, DWORD rop) const
{
	BitBlt(mainHDC, mx, my, width, height, this->supHDC, sx, sy, rop);  // слева
}

void SupHDC::DrawLoopedY(HDC mainHDC, int mx, int my, int width, int height, int sx, int sy, DWORD rop) const
{
	int ost_y = height - (this->height - sy);  
	if (ost_y > 0) {
		BitBlt(mainHDC, mx, my + height - ost_y, width, ost_y, this->supHDC, 0, 0, rop);
		BitBlt(mainHDC, mx, my, width, height - ost_y, this->supHDC, sx, sy, rop);
	}
	else {
		this->Draw(mainHDC, mx, my, width, height, sx, sy, rop);
	}
}

void SupHDC::DrawLoopedX(HDC mainHDC, int mx, int my, int width, int height, int sx, int sy, DWORD rop) const
{
	int ost_x = width - (this->width - sx);
	if (ost_x > 0) {
		BitBlt(mainHDC, mx + width - ost_x, my, ost_x, height, this->supHDC, 0, 0, rop);
		BitBlt(mainHDC, mx, my, width - ost_x, height, this->supHDC, sx, sy, rop);
	}
	else {
		this->Draw(mainHDC, mx, my, width, height, sx, sy, rop);
	}
}

