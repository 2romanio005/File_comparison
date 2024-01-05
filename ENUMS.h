#pragma once
#include "Define.h"

enum COLOUR {
	ERASED,			// �������
	ADDED,			// ���������
	CHANGED,		// ��������
	NOT_CHANGED,	// �� ����������    
	EMPTY,			// �� ����� ���� ������

	SYMBOL,			// �������
	BACKGROUND,		// �������� ������ ���
	BORDERLINE,		// �������

	_size // ������ ��������� ��� ������� �������
};


enum PART_BUTTON_PRESSED {
	NONE,
	MAIN,
	CLOSE,
};