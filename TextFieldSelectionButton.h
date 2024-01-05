#pragma once
#include "2Connection.h"
class TextFieldSelectionButton
{
public:
	TextFieldSelectionButton(TextField const *const Text, const std::string &FileName, long x, long y, long width, long height);
	TextFieldSelectionButton(TextField const *const Text, const std::string &FileName, long x, long y, long height);
	TextFieldSelectionButton(const TextFieldSelectionButton &original, long x, long y, long width, long height);
	TextFieldSelectionButton(const TextFieldSelectionButton &original);
	~TextFieldSelectionButton();

	void Draw(HDC mainHDC) const;
	void DrawTop(HDC mainHDC) const;

	PART_BUTTON_PRESSED PartButtonPressed(long pos_x, long pos_y) const;

	TextField const *const getTextField() const;
	const std::string &getFileName() const;
	long getWidth() const;

	void setPosition(long x, long y);
	void resize(long width, long height);

	void setTopColour(COLOUR TopColour);

	//TextFieldSelectionButton &operator=(const TextFieldSelectionButton &original);

private:
	long x, y;
	long width, height, margin_top;

	//HWND FatherhWnd;
	//HWND StaticButtonSelect;
	//HWND StaticButtonClose;

	TextField const *const Text;
	const std::string FileName;

	COLOUR TopColour;
};

