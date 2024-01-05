#pragma once
#include "4Connection.h"
//typedef std::size_t HASH;

extern char LastOpenDirectory[266];

extern int size_screen_x;
extern int size_screen_y;

extern long letter_height;
extern long letter_width;



extern std::set<TextField> AllTextField;
extern std::set<TextField::PairTextFieldComparisonResult> AllPairTextFieldComparisonResult;

extern TextFieldSelectionButton VoidTextFieldSelectionButton;
extern RowTextFieldSelectionButton RowSelectionButtons;

extern VisualTextField VisualTextFieldLeft;
extern VisualTextField VisualTextFieldRight;




extern Slider SliderTextFieldY;
extern Slider SliderTextFieldLeftX;
extern Slider SliderTextFieldRightX;

extern HWND ButtonChooseFile;
//extern HWND ButtonChooseFileRight;


extern std::vector<HBRUSH> B_COLOUR;
extern HPEN P_Null;

extern HFONT F_Main;

extern HDC MainHdc;
extern PAINTSTRUCT MainPs;
