//==============================================================================
//
// �����L���O��ʂ̕`��kranking.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitRanking(void);		// �����L���O��ʂ̏���������
void UninitRanking(void);		// �����L���O��ʂ̏I������
void UpdateRanking(void);		// �����L���O��ʂ̍X�V����
void DrawRanking(void);			// �����L���O��ʂ̕`�揈��
void SetRanking(int nScore);	// �X�R�A�̕��ёւ�
void LoadData(void);			// �f�[�^�̓ǂݍ���
void SaveData(void);			// �f�[�^�̕ۑ�
void SetInitRanking(void);		// �������ɂ�����|���S���z�u

#endif
