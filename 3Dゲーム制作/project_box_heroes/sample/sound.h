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
	SOUND_LABEL_TITLE,			// BGM0
	SOUND_LABEL_SELECT,			// BGM1
	SOUND_LABEL_STAGE0,			// BGM3
	SOUND_LABEL_STAGE1,			// BGM4
	SOUND_LABEL_STAGE2,			// BGM5
	SOUND_LABEL_RESULT,			// BGM6
	SOUND_LABEL_SE_ITEM,			// �A�C�e���擾
	SOUND_LABEL_SE_JUMP,			// �W�����v
	SOUND_LABEL_SE_PAUSE_SELECT,	// �|�[�Y�J�[�\���ړ�
	SOUND_LABEL_SE_CANCEL,			// �L�����Z����
	SOUND_LABEL_SE_START,			// �Q�[���X�^�[�g
	SOUND_LABEL_SE_DECIDE,			// ����
	SOUND_LABEL_SE_CURSOR,			// �J�[�\���ړ�
	SOUND_LABEL_SE_SMASH,			// �Ō���
	SOUND_LABEL_SE_SLASH,			// �a����
	SOUND_LABEL_SE_SHOT,			// �ˌ���
	SOUND_LABEL_SE_EXPLOSION,		// ������
	SOUND_LABEL_SE_SMASH_HIT,		// �Ō��q�b�g��
	SOUND_LABEL_SE_SLASH_HIT,		// �a���q�b�g��
	SOUND_LABEL_SE_SHOT_HIT,		// �ˌ��q�b�g��
	SOUND_LABEL_SE_EXPLOSION_HIT,	// �����q�b�g��
	SOUND_LABEL_SE_SETITEM,
	SOUND_LABEL_SE_COUNTDOWN,		// �J�E���g�_�E��
	SOUND_LABEL_SE_GAMESTART,		// �J�E���g�_�E��
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
