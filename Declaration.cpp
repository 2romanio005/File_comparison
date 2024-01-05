#pragma once
#include "Main.h"

char LastOpenDirectory[266];

int size_screen_x;
int size_screen_y;

long letter_height;
long letter_width;


std::set<TextField> AllTextField { TextField() };
std::set<TextField::PairTextFieldComparisonResult> AllPairTextFieldComparisonResult;

TextFieldSelectionButton VoidTextFieldSelectionButton(&(*AllTextField.begin()), "", 0, 0, 0, 0);
RowTextFieldSelectionButton RowSelectionButtons;

VisualTextField VisualTextFieldLeft(VoidTextFieldSelectionButton);
VisualTextField VisualTextFieldRight(VoidTextFieldSelectionButton);




Slider SliderTextFieldY([](long changes) {
	VisualTextFieldLeft.ScrollY(changes);
	VisualTextFieldLeft.UpdateText();

	VisualTextFieldRight.ScrollY(changes);
	VisualTextFieldRight.UpdateText();
	});
Slider SliderTextFieldLeftX([](long changes) {
	VisualTextFieldLeft.ScrollX(changes);
	VisualTextFieldLeft.UpdateText();
	});
Slider SliderTextFieldRightX([](long changes) {
	VisualTextFieldRight.ScrollX(changes);
	VisualTextFieldRight.UpdateText();
	});

HWND ButtonChooseFile;
//HWND ButtonChooseFileRight;


std::vector<HBRUSH> B_COLOUR(COLOUR::_size);
HPEN P_Null;

HFONT F_Main;

HDC MainHdc;
PAINTSTRUCT MainPs;



