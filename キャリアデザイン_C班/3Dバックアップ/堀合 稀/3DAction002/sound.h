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
	SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_SE_HIT000,			// �q�b�g��
	SOUND_LABEL_SE_HIT001,			// �q�b�g��
	SOUND_LABEL_SE_START000,	// ����
	SOUND_LABEL_SE_COIN,			// �R�C���擾
	SOUND_LABEL_SE_JUMP,			// �W�����v
	SOUND_LABEL_SE_PAUSE_SELECT,		// �|�[�Y�J�[�\���ړ�
	SOUND_LABEL_SE_STOCK_LOST,		// �c�@����
	SOUND_LABEL_SE_SCORE_UP,		// �X�R�A�㏸
	SOUND_LABEL_SE_HIGHCOIN,		// �n�C�X�R�A�R�C���l��
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
