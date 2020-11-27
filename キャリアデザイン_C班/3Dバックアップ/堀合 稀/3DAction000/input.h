//==============================================================================
//
// ���͏����i�L�[�{�[�h�j�kinput.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//==============================================================================
// �L�[����
//==============================================================================
typedef enum
{
	KEYINFO_OK = 0,
	KEYINFO_SPACE,
	KEYINFO_UP,
	KEYINFO_DOWN,
	KEYINFO_LEFT,
	KEYINFO_RIGHT,
	KEYINFO_LEFT_CENTER,
	KEYINFO_RIGHT_CENTER,
	KEYINFO_UP_CENTER,
	KEYINFO_DOWN_CENTER,
	KEYINFO_LEFT_TURN,
	KEYINFO_RIGHT_TURN,
	KEYINFO_UP_SIGHT,
	KEYINFO_DOWN_SIGHT,
	KEYINFO_BACK_MODEL,
	KEYINFO_FORE_MODEL,
	KEYINFO_LEFT_MODEL,
	KEYINFO_RIGHT_MODEL,
	KEYINFO_UP_MODEL,
	KEYINFO_DOWN_MODEL,
	KEYINFO_TURN_LEFT_MODEL,
	KEYINFO_TURN_RIGHT_MODEL,
	KEYINFO_MAX
} KEYINFO;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	// ���͂̏���������
void UninitKeyboard(void);								// ���͂̏I������
void UpdateKeyboard(void);								// ���͂̍X�V����
bool GetKeyboardPress(int nKey);						// �L�[�{�[�h���̎擾
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

#endif