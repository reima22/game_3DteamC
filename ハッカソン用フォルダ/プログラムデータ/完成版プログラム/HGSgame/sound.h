//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM000,			// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_SE_SHOT000,		// �e���ˉ�(�G�@)
	SOUND_LABEL_SE_SHOT001,		// �e���ˉ�(�e)
	SOUND_LABEL_SE_SHOT002,		// �e���ˉ�(�E�F�[�u)
	SOUND_LABEL_SE_SHOT003,		// �e���ˉ�(�~�T�C��)
	SOUND_LABEL_SE_HIT000,			// �q�b�g��
	SOUND_LABEL_SE_HIT001,			// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION000,	// ������0
	SOUND_LABEL_SE_EXPLOSION001,	// ������1
	SOUND_LABEL_SE_EXPLOSION002,	// ������2
	SOUND_LABEL_SE_EXPLOSION003,	// ������3
	SOUND_LABEL_SE_START000,	// ����
	SOUND_LABEL_SE_SELECT,		// �J�[�\���ړ�
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
