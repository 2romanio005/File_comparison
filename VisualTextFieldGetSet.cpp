#pragma once
#include "Main.h"


std::set<TextField::PairTextFieldComparisonResult>::iterator VisualTextField::setActiveTextField(const TextFieldSelectionButton &ActiveTextField)
{
	this->setSimplyActiveTextField(new TextFieldSelectionButton(ActiveTextField, 0, 0, this->width + 1, letter_height + 2 * letter_margin + RowTextFeildSelectionButtonTopSize));
	// @@@@@@@@@@@@@@@@@@@@@@  при изменении измернить swapActiveTextField()
	//SetWindowTextA(this->StaticFileName, LPCSTR(this->ActiveTextField->getFileName().c_str()));   // 



	//TextField::Compare::ComparisonResultRow tmp_for_found { basic.TextLenth };
	std::set<TextField::PairTextFieldComparisonResult>::iterator FoundComparisonResult = AllPairTextFieldComparisonResult.find(TextField::PairTextFieldComparisonResult { {VisualTextFieldLeft.ActiveTextField->getTextField()->getMyHASH()}, { VisualTextFieldRight.ActiveTextField->getTextField()->getMyHASH()} });

	if (FoundComparisonResult == AllPairTextFieldComparisonResult.end()) {
		FoundComparisonResult = TextField::PairTextFieldComparisonResult::CompareTextField(*VisualTextFieldLeft.ActiveTextField->getTextField(), *VisualTextFieldRight.ActiveTextField->getTextField());
	}

	VisualTextFieldLeft.ActiveTextField->setTopColour(COLOUR::ERASED);
	VisualTextFieldRight.ActiveTextField->setTopColour(COLOUR::ADDED);

	VisualTextFieldLeft.setActiveComparisonResult(&(FoundComparisonResult->basic.Result));
	VisualTextFieldRight.setActiveComparisonResult(&(FoundComparisonResult->secondary.Result));

	VisualTextFieldLeft.UpdateAll();
	VisualTextFieldRight.UpdateAll();

	SliderTextFieldY.setRange(0, VisualTextFieldLeft.getNumberRows() * letter_height);

	SliderTextFieldLeftX.setRange(0, VisualTextFieldLeft.getNumberColumns() * letter_width);
	SliderTextFieldLeftX.stepPage = VisualTextFieldLeft.getNumberVisibleColumns() * letter_width / 2;
	SliderTextFieldRightX.setRange(0, VisualTextFieldRight.getNumberColumns() * letter_width);
	SliderTextFieldRightX.stepPage = VisualTextFieldRight.getNumberVisibleColumns() * letter_width / 2;

	return FoundComparisonResult;
}

void VisualTextField::swapActiveTextField()
{
	TextFieldSelectionButton *const past_left = VisualTextFieldLeft.ActiveTextField;
	//SetWindowTextA(VisualTextFieldLeft.StaticFileName, LPCSTR(VisualTextFieldRight.ActiveTextField->getFileName().c_str()));
	VisualTextFieldLeft.ActiveTextField = VisualTextFieldRight.ActiveTextField;
	VisualTextFieldRight.ActiveTextField = past_left;
	VisualTextFieldRight.setActiveTextField(*past_left);
}


void VisualTextField::setActiveComparisonResult(std::vector<TextField::ComparisonResultRow> const *const ActiveComparisonResult)
{
	this->ActiveComparisonResult = ActiveComparisonResult;

	long NumberCharacters = 1;
	long tmp = this->getNumberRows();
	while ((tmp /= 10) > 0) {
		++NumberCharacters;
	}
	this->setMargin_left(NumberCharacters * letter_width + 8 + 1);

	this->Resize(this->width, this->height);
	//this->UpdateAll();
}

void VisualTextField::setSimplyActiveTextField(TextFieldSelectionButton *const ActiveTextField)
{
	delete this->ActiveTextField;
	this->ActiveTextField = ActiveTextField;
}




void VisualTextField::setWidth(long width)
{
	this->width = width;
	this->updateNumberPixelColumns();
	this->updateNumberVisiblePixelColumns();
	this->updateNumberVisibleColumns();
}

void VisualTextField::setHeight(long height)
{
	this->height = height;
	this->updateNumberVisiblePixelRows();
	this->updateNumberVisibleRows();
}


void VisualTextField::setMargin_top(long margin_top)
{
	this->margin_top = margin_top;
	this->updateNumberVisiblePixelRows();
	this->updateNumberVisibleRows();
}

void VisualTextField::setMargin_bottom(long margin_bottom)
{
	this->margin_bottom = margin_bottom;
	this->updateNumberVisiblePixelRows();
	this->updateNumberVisibleRows();
}

void VisualTextField::setMargin_left(long margin_left)
{
	this->margin_left = margin_left;
	this->updateNumberPixelColumns();
	this->updateNumberVisiblePixelColumns();
	this->updateNumberVisibleColumns();
}

void VisualTextField::setMargin_right(long margin_right)
{
	this->margin_right = margin_right;
	this->updateNumberPixelColumns();
	this->updateNumberVisiblePixelColumns();
	this->updateNumberVisibleColumns();
}



long VisualTextField::getNumberRows() const
{
	//if (this->ActiveComparisonResult == nullptr) {
	//	return 0;
	//}
	return this->ActiveComparisonResult->size();
}

long VisualTextField::getNumberVisibleRows() const
{
	return this->NumberVisibleRows;
}

long VisualTextField::getNumberVisiblePixelRows() const
{
	return NumberVisiblePixelRows;
}




long VisualTextField::getNumberColumns() const
{
	return this->ActiveTextField->getTextField()->getNumberColumns();
}

long VisualTextField::getNumberVisibleColumns() const
{
	return this->NumberVisibleColumns;
}

long VisualTextField::getNumberPixelColumns() const
{
	return this->NumberPixelColumns;
}

long VisualTextField::getNumberVisiblePixelColumns() const
{
	return this->NumberVisiblePixelColumns;
}



PART_BUTTON_PRESSED VisualTextField::getPART_BUTTON_PRESSED(long pos_x, long pos_y) const
{
	PART_BUTTON_PRESSED part = this->ActiveTextField->PartButtonPressed(pos_x - this->x, pos_y - this->y);
	if (this->ActiveTextField->getFileName().size() == 0 && part == PART_BUTTON_PRESSED::CLOSE) {
		return PART_BUTTON_PRESSED::MAIN;
	}
	return part;
}



void VisualTextField::updateNumberVisibleRows()
{
	this->NumberVisibleRows = (this->getNumberVisiblePixelRows() + letter_height - 1) / letter_height;
}

void VisualTextField::updateNumberVisiblePixelRows()
{
	this->NumberVisiblePixelRows = this->height - this->margin_top - this->margin_bottom;
}




void VisualTextField::updateNumberVisibleColumns()
{
	this->NumberVisibleColumns = (this->getNumberVisiblePixelColumns() + letter_width - 1) / letter_width;
}

void VisualTextField::updateNumberPixelColumns()
{
	this->NumberPixelColumns = this->ActiveTextField->getTextField()->getNumberColumns() * letter_width + this->width - this->margin_left - this->margin_right;
}

void VisualTextField::updateNumberVisiblePixelColumns()
{
	this->NumberVisiblePixelColumns = this->width - this->margin_left - this->margin_right;
}


//void VisualTextField::Clear()
//{
//	this->MyHASH = { "" };
//	this->TextLenth.clear();
//	this->Hash.clear();
//	//this->SortedHash.clear();
//	//this->HashWord.clear();
//
//	this->ActiveComparisonResult = nullptr;
//
//	this->NumberColumns = 0;
//	SetWindowTextA(this->StaticFileName, LPCSTR(""));
//}


