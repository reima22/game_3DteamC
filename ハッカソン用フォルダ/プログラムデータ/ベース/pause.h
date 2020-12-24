//==============================================================================
//
// �|�[�Y���j���[�̕`��kpause.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _PAUSE_H_
#define _PAUSE_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define PAUSE_POLYGON	(7)			// �|�[�Y��ʂ̎g�p����|���S����
#define PAUSETEXT		(4)			// �|�[�Y��ʂ̑I������
#define PAUSE_WINDOWX	(160)		// �|�[�Y���j���[�̕�
#define PAUSE_WINDOWY	(200)		// �|�[�Y���j���[�̍���
#define PAUSE_SIZEX		(140)		// �|�[�Y�e�L�X�g�̕�
#define PAUSE_SIZEY		(40)		// �|�[�Y�e�L�X�g�̍���
#define PAUSETEXT_POSY	(230)		// �|�[�Y�e�L�X�g1�s�ڂ̍���

//==============================================================================
// �|�[�Y���j���[
//==============================================================================
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	// �R���e�B�j���[
	PAUSE_MENU_RETRY,			// ���g���C
	PAUSE_MENU_OPTION,			// �I�v�V����
	PAUSE_MENU_QUIT,			// �I��
	PAUSE_MENU_MAX
} PAUSE_MENU;

//==============================================================================
// �|�[�Y�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 posBackScreen;			// �|�[�Y�w�i�̈ʒu
	D3DXVECTOR3 posWindow;				// �|�[�Y�E�B���h�E�̈ʒu
	D3DXVECTOR3 posText[PAUSETEXT];		// �|�[�Y�e�L�X�g�̈ʒu
	float fContinue;					// �R���e�j���[�e�L�X�g�̃e�N�X�`���ʒu
	float fRetry;						// ���g���C�e�L�X�g�̃e�N�X�`���ʒu
	float fOption;						// �I�v�V�����e�L�X�g�̃e�N�X�`���ʒu
	float fQuit;						// �^�C�g���ւ̃e�L�X�g�̃e�N�X�`���ʒu
	D3DXCOLOR colOption;				// �u�����т����v�|���S���̓����x
	bool bOption;						// �u�����т����v�ւ̈ڍs���
	PAUSE_MENU PauseMenu;				// �|�[�Y���j���[
} PAUSE;


//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitPause(void);	// �|�[�Y���j���[�̏���������
void UninitPause(void);		// �|�[�Y���j���[�̏I������
void UpdatePause(void);		// �|�[�Y���j���[�̍X�V����
void DrawPause(void);		// �|�[�Y���j���[�̕`�揈��
PAUSE GetPause(void);		// �|�[�Y�̏��擾

#endif
