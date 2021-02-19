//==============================================================================
//
// ���͏����i�Q�[���p�b�h�j�kgamepad.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_
#include "main.h"

//==============================================================================
// �L�[����
//==============================================================================
// �f�o�C�X�̗�
typedef enum
{
	DIDEVTYPE_MOUSE = 0,	// �}�E�X
	DIDEVTYPE_KEYBOARD,		// �L�[�{�[�h
	DIDEVTYPE_JOYSTICK,		// �W���C�X�e�B�b�N
	DIDEVTYPE_DEVICE,		// ���̑�
	DIDEVTYPE_MAX
} DIDEVTYPE;

typedef enum
{
	ButtonStateNone = 0,
	ButtonStateDown,
	ButtonStatePush,
	ButtonStateUp,
	ButtonStateMax,
} ButtonState;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd);	// ���͂̏���������
void UninitGamepad(void);								// ���͂̏I������
void UpdateGamepad(void);								// ���͂̍X�V����
BOOL CALLBACK DeviceFindCallBack(
	LPCDIDEVICEINSTANCE ipddi,
	LPVOID pvRef);
bool IsButtonPush(KEYINFO button);
bool IsButtonUp(KEYINFO button);
bool IsButtonDown(KEYINFO button);

#endif
