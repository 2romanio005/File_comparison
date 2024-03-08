#pragma once
#include "0Include.h"

class Slider
{
public:
	Slider(void (*subordinate)(long changes) = [](long changes) {}, long step = 1, long stepPage = 1, long pos = 0, long min_pos = 0, long max_pos = 0);
	~Slider();

	void Create(LPCSTR Name, DWORD dwStyle, long x, long y, long width, long height, HWND hWnd);

	void Update() const;


	void Scroll(long koef);
	void ScrollPage(long koef);

	void setRange(long min_pos, long max_pos);

	void setPos(long pos);
	long getPos();

	long step;
	long stepPage;

	HWND slider;
private:
	long min_pos;
	long max_pos;
	long pos;
	void (*subordinate)(long changes);

	HWND FatherhWnd;
};


