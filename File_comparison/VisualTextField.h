#pragma once
#include "3Connection.h"

class VisualTextField
{
public:
	VisualTextField(const TextFieldSelectionButton &ActiveTextField);
	~VisualTextField();
	void Create(long x, long y, long width, long height, HWND hWnd);

	void UpdateText();
	void UpdateAll();
	void Draw(HDC hdc);

	void Resize(long width, long height);
	void ScrollY(long changes);
	void ScrollX(long changes);


	std::set<TextField::PairTextFieldComparisonResult>::iterator setActiveTextField(const TextFieldSelectionButton &ActiveTextField);
	static void swapActiveTextField();

	long getNumberRows() const;
	long getNumberVisibleRows() const;
	long getNumberVisiblePixelRows() const;
	
	long getNumberColumns() const;
	long getNumberVisibleColumns() const;
	long getNumberPixelColumns() const;
	long getNumberVisiblePixelColumns() const;

	PART_BUTTON_PRESSED getPART_BUTTON_PRESSED(long pos_x, long pos_y) const;

private:
	HWND FatherhWnd;

	std::vector<TextField::ComparisonResultRow> const *ActiveComparisonResult;
	void setActiveComparisonResult(std::vector<TextField::ComparisonResultRow> const *const ActiveComparisonResult);

	TextFieldSelectionButton *ActiveTextField;
	void setSimplyActiveTextField(TextFieldSelectionButton *const ActiveTextField);

	SupHDC FileName_HDC;
	SupHDC ColourText_HDC;
	SupHDC Number_HDC;
	void CreateColourText_HDC();
	void CreateRowColourText_HDC(std::size_t row_index/*, int x*/, long y);

	long ScrollPosY, ScrollPosX;
	long LastUpdateScrollPosY;

	long x, y;
	long width, height;
	void setWidth(long width);
	void setHeight(long height);

	long margin_top, margin_bottom, margin_left, margin_right;
	void setMargin_top(long margin_top);
	void setMargin_bottom(long margin_bottom);
	void setMargin_left(long margin_left);
	void setMargin_right(long margin_right);

	long NumberVisibleRows;
	long NumberVisiblePixelRows;
	void updateNumberVisibleRows();
	void updateNumberVisiblePixelRows();

	long NumberVisibleColumns;
	long NumberPixelColumns;
	long NumberVisiblePixelColumns;
	void updateNumberVisibleColumns();
	void updateNumberPixelColumns();
	void updateNumberVisiblePixelColumns();

};

