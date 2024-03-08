#pragma once
#include "Main.h"


TextFieldSelectionButton::TextFieldSelectionButton(TextField const *const Text, const std::string &FileName, long x, long y, long width, long height) : Text(Text), FileName(FileName)
{
	this->setPosition(x, y);
	this->resize(width, height);
	/*this->width = this->FileName.size() * letter_width + 2 * (this->height - this->margin_top) + 1;*/

	//this->FatherhWnd = FatherhWnd;
	this->TopColour = COLOUR::BACKGROUND;
}

TextFieldSelectionButton::TextFieldSelectionButton(TextField const *const Text, const std::string &FileName, long x, long y, long height) : TextFieldSelectionButton(Text, FileName, x, y, 0, height)
{
	this->width = this->FileName.size() * letter_width + 2 * (this->height - this->margin_top) + 1;
}

TextFieldSelectionButton::TextFieldSelectionButton(const TextFieldSelectionButton &original, long x, long y, long width, long height) : TextFieldSelectionButton(original.Text, original.FileName, x, y, width, height)
{
}

TextFieldSelectionButton::TextFieldSelectionButton(const TextFieldSelectionButton &original) : TextFieldSelectionButton(original, original.x, original.y, original.width, original.height)
{
}

TextFieldSelectionButton::~TextFieldSelectionButton()
{

}



void TextFieldSelectionButton::Draw(HDC mainHDC) const
{
	this->DrawTop(mainHDC);

	RECT word_place { this->x + this->height - this->margin_top, this->y + this->margin_top + letter_margin, this->x + this->width - this->height + this->margin_top - 1 , this->y + this->height - letter_margin };
	DrawTextA(mainHDC, LPCSTR(this->FileName.c_str()), -1, &word_place, DT_CENTER);
	word_place = { this->x + this->width - this->height + this->margin_top - 1, this->y + this->margin_top + letter_margin, this->x + this->width - 1, this->y + this->height - letter_margin };
	DrawTextA(mainHDC, "X", 1, &word_place, DT_CENTER);

	SelectObject(mainHDC, B_COLOUR[COLOUR::BORDERLINE]); // рамка справа
	Rectangle(mainHDC, this->x + this->width - 1, this->y, this->x + this->width + 1, this->y + this->height + 1);
}

void TextFieldSelectionButton::DrawTop(HDC mainHDC) const
{
	SelectObject(mainHDC, B_COLOUR[this->TopColour]); // верх
	Rectangle(mainHDC, this->x, this->y, this->x + this->width, this->y + this->margin_top + 1);
}



PART_BUTTON_PRESSED TextFieldSelectionButton::PartButtonPressed(long pos_x, long pos_y) const
{
	if (pos_x >= x && pos_x < x + width - 1 && pos_y >= y && pos_y <= y + height) {
		if (pos_x >= x + width - height - 1) {
			return PART_BUTTON_PRESSED::CLOSE;
		}
		return PART_BUTTON_PRESSED::MAIN;
	}
	return PART_BUTTON_PRESSED::NONE;
}



TextField const *const TextFieldSelectionButton::getTextField() const
{
	return this->Text;
}

const std::string &TextFieldSelectionButton::getFileName() const
{
	return this->FileName;
}

long TextFieldSelectionButton::getWidth() const
{
	return this->width;
}



void TextFieldSelectionButton::setPosition(long x, long y)
{
	this->x = x;
	this->y = y;
}

void TextFieldSelectionButton::resize(long width, long height)
{
	this->height = height;
	this->margin_top = (std::max)(this->height - letter_height - 2 * letter_margin, long(0));
	this->width = width;
}

void TextFieldSelectionButton::setTopColour(COLOUR TopColour)
{
	this->TopColour = TopColour;
}

//TextFieldSelectionButton &TextFieldSelectionButton::operator=(const TextFieldSelectionButton &original)
//{
//
//	return *this;
//}

