#pragma once
#include "3Connection.h"

class RowTextFieldSelectionButton
{
public:
	RowTextFieldSelectionButton();
	RowTextFieldSelectionButton(long x, long y, long width, long height, HWND FatherhWnd);
	~RowTextFieldSelectionButton();
	void Create(long x, long y, long width, long height, HWND FatherhWnd);

	void UpdateRowButton();
	void UpdateAll();

	void HideArrow();
	void ShowArrow();

	void Draw(HDC mainHDC);

	void addTextFieldSelectionButton();
	void addTextFieldSelectionButton(const std::string &path);

	void LBUTTONDOWN(long pos_x, long pos_y);
	void ActiveLeftLBUTTONDOWN(PART_BUTTON_PRESSED part);
	void ActiveRightLBUTTONDOWN(PART_BUTTON_PRESSED part);
	
	void RBUTTONDOWN(long pos_x, long pos_y);
	void ActiveLeftRBUTTONDOWN(PART_BUTTON_PRESSED part);
	void ActiveRightRBUTTONDOWN(PART_BUTTON_PRESSED part);


	void ScrollLeft();
	void ScrollRight();

private:
	std::list<TextFieldSelectionButton> RowButtons;

	std::list<TextFieldSelectionButton>::iterator Start, ActiveLeft, ActiveRight;

	long x, y;
	long width, height, arrow_buf;

	long SliderX;
	HWND ButtonScrollLeft, ButtonScrollRight;


	std::pair<std::list<TextFieldSelectionButton>::iterator, PART_BUTTON_PRESSED> getTextFieldButtonPressed(long pos_x, long pos_y);

	void processLBUTTONDOWN(std::list<TextFieldSelectionButton>::iterator button, PART_BUTTON_PRESSED part);
	void processRBUTTONDOWN(std::list<TextFieldSelectionButton>::iterator button, PART_BUTTON_PRESSED part);


	void DeleteTextFieldSelectionButton(std::list<TextFieldSelectionButton>::iterator delete_button);


	HWND FatherhWnd;

	SupHDC RowButton_HDC;
	void CreateRowButton_HDC();

	void DrawActiveButton(std::list<TextFieldSelectionButton>::iterator ActiveButton, COLOUR top_colour);

	//void updateButtonPos();
	//void updateHDCsize();	
};






