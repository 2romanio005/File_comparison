#pragma once
#include "Main.h"



void RowTextFieldSelectionButton::LBUTTONDOWN(long pos_x, long pos_y) {
	std::pair<std::list<TextFieldSelectionButton>::iterator, PART_BUTTON_PRESSED> LeftPressed = this->getTextFieldButtonPressed(pos_x, pos_y);

	this->processLBUTTONDOWN(LeftPressed.first, LeftPressed.second);
}

void RowTextFieldSelectionButton::ActiveLeftLBUTTONDOWN(PART_BUTTON_PRESSED part)
{
	this->processLBUTTONDOWN(this->ActiveLeft, part);;
}

void RowTextFieldSelectionButton::ActiveRightLBUTTONDOWN(PART_BUTTON_PRESSED part)
{
	this->processLBUTTONDOWN(this->ActiveRight, part);;
}



void RowTextFieldSelectionButton::RBUTTONDOWN(long pos_x, long pos_y) {
	std::pair<std::list<TextFieldSelectionButton>::iterator, PART_BUTTON_PRESSED> RightPressed = this->getTextFieldButtonPressed(pos_x, pos_y);

	this->processRBUTTONDOWN(RightPressed.first, RightPressed.second);
}

void RowTextFieldSelectionButton::ActiveLeftRBUTTONDOWN(PART_BUTTON_PRESSED part)
{
	this->processRBUTTONDOWN(this->ActiveLeft, part);
}

void RowTextFieldSelectionButton::ActiveRightRBUTTONDOWN(PART_BUTTON_PRESSED part)
{
	this->processRBUTTONDOWN(this->ActiveRight, part);
}






std::pair<std::list<TextFieldSelectionButton>::iterator, PART_BUTTON_PRESSED> RowTextFieldSelectionButton::getTextFieldButtonPressed(long pos_x, long pos_y)
{
	if (pos_y < this->y || pos_y > this->y + this->height || pos_x < this->x || pos_x > this->x + this->width - this->arrow_buf) {
		return { this->RowButtons.end(), PART_BUTTON_PRESSED::NONE };
	}

	pos_x += this->SliderX - this->x;
	pos_y -= this->y;

	for (std::list<TextFieldSelectionButton>::iterator button = this->Start; button != this->RowButtons.end(); ++button) {
		PART_BUTTON_PRESSED ElPart = button->PartButtonPressed(pos_x, pos_y);
		if (ElPart != PART_BUTTON_PRESSED::NONE) {
			return { button, ElPart };
		}
	}

	return { this->RowButtons.end(), PART_BUTTON_PRESSED::NONE };
}


void RowTextFieldSelectionButton::processLBUTTONDOWN(std::list<TextFieldSelectionButton>::iterator button, PART_BUTTON_PRESSED part)
{
	switch (part)
	{
		case PART_BUTTON_PRESSED::MAIN: {
			if (button == this->ActiveRight) {
				VisualTextField::swapActiveTextField();
				std::swap(this->ActiveLeft, this->ActiveRight);
				this->DrawActiveButton(this->ActiveLeft, COLOUR::ERASED);
				this->DrawActiveButton(this->ActiveRight, COLOUR::ADDED);
			}
			else {
				this->DrawActiveButton(this->ActiveLeft, COLOUR::BACKGROUND);
				this->ActiveLeft = button;
				this->DrawActiveButton(this->ActiveLeft, COLOUR::ERASED);

				VisualTextFieldLeft.setActiveTextField(*this->ActiveLeft);
			}
			break;
		}
		case PART_BUTTON_PRESSED::CLOSE: {
			this->DeleteTextFieldSelectionButton(button);
			break;
		}
		case PART_BUTTON_PRESSED::NONE: {
			return;
		}
	}

	this->UpdateAll();
}

void RowTextFieldSelectionButton::processRBUTTONDOWN(std::list<TextFieldSelectionButton>::iterator button, PART_BUTTON_PRESSED part)
{
	switch (part)
	{
		case PART_BUTTON_PRESSED::MAIN: {
			if (button == this->ActiveLeft) {
				VisualTextField::swapActiveTextField();
				std::swap(this->ActiveLeft, this->ActiveRight);
				this->DrawActiveButton(this->ActiveLeft, COLOUR::ERASED);
				this->DrawActiveButton(this->ActiveRight, COLOUR::ADDED);
			}
			else {
				this->DrawActiveButton(this->ActiveRight, COLOUR::BACKGROUND);
				this->ActiveRight = button;
				this->DrawActiveButton(this->ActiveRight, COLOUR::ADDED);

				VisualTextFieldRight.setActiveTextField(*this->ActiveRight);
			}
			break;
		}
		case PART_BUTTON_PRESSED::CLOSE: {
			this->DeleteTextFieldSelectionButton(button);
			break;
		}
		case PART_BUTTON_PRESSED::NONE: {
			return;
		}
	}

	this->UpdateAll();
}

