#pragma once
#include "Define.h"

enum COLOUR {
	ERASED,			// удалено
	ADDED,			// добавлено
	CHANGED,		// изменено
	NOT_CHANGED,	// не изменялось    
	EMPTY,			// на самом деле пустое

	SYMBOL,			// символы
	BACKGROUND,		// основной задний фон
	BORDERLINE,		// граница

	_size // всегда последнее для размера массива
};


enum PART_BUTTON_PRESSED {
	NONE,
	MAIN,
	CLOSE,
};