//==============================================================================
//
// �Q�[����ʂ̕`��kgame.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_STAGE		(3)		// �X�e�[�W��
#define START_NUM		(0)		// �J�n�X�e�[�W

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitGame(void);		// �Q�[����ʂ̏���������
void UninitGame(void);		// �Q�[����ʂ̏I������
void UpdateGame(void);		// �Q�[����ʂ̍X�V����
void DrawGame(void);		// �Q�[����ʂ̕`�揈��
HRESULT InitGameCnt(void);	// �X�e�[�W�J�E���g�̏�����
void PutEnemy(int nStage);	// �G�̔z�u
void PutItem(int nStage);	// �A�C�e���̔z�u
void PutBlock(int nStage);	// �u���b�N�̔z�u
int GetStage(void);			// �X�e�[�W�J�E���g�̎擾
void LoadBlock(int nStage);	// �u���b�N�z�u��csv�t�@�C���ǂݍ���

#endif