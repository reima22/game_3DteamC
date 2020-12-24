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
	KEYINFO_UP,
	KEYINFO_DOWN,
	KEYINFO_LEFT,
	KEYINFO_RIGHT,
	KEYINFO_SHOT,
	KEYINFO_PAUSE,
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