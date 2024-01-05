#pragma once
#include "Main.h"


Slider::Slider(void (*subordinate)(long changes), long step, long stepPage, long pos, long min_pos, long max_pos)
{
	this->subordinate = subordinate;
	this->pos = pos;
	this->step = step;
	this->stepPage = stepPage;
	this->min_pos = min_pos;
	this->max_pos = max_pos;

	this->slider = NULL;
	this->FatherhWnd = nullptr;
}

Slider::~Slider()
{
	DestroyWindow(this->slider);
}

void Slider::Create(LPCSTR Name, DWORD dwStyle, long x, long y, long width, long height, HWND hWnd)
{
	this->slider = CreateWindowA("SCROLLBAR", Name, dwStyle, x, y, width, height, hWnd, NULL, NULL, NULL);
	this->setRange(this->min_pos, this->max_pos);
	this->setPos(this->pos);
	SendMessage(this->slider, WM_SETFONT, WPARAM(F_Main), true);

	this->FatherhWnd = hWnd;
}

void Slider::Update() const
{
	UpdateWindow(this->slider);
}



void Slider::Scroll(long koef)
{
	this->setPos(this->pos + this->step * koef);
}

void Slider::ScrollPage(long koef)
{
	this->setPos(this->pos + this->stepPage * koef);
}

void Slider::setRange(long min_pos, long max_pos)
{
	this->min_pos = min_pos;
	this->max_pos = max_pos;
	if (this->pos > this->max_pos || this->pos < this->min_pos) {
		this->setPos(this->pos);
	}
	SetScrollRange(this->slider, SB_CTL, this->min_pos, this->max_pos, TRUE);
}

void Slider::setPos(long pos)
{
	long tmp = this->pos;
	this->pos = (std::min)((std::max)(pos, this->min_pos), this->max_pos);
	SetScrollPos(this->slider, SB_CTL, this->pos, TRUE);
	this->subordinate(this->pos - tmp);
}
long Slider::getPos()
{
	return this->pos;
}
