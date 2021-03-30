//==============================================================================
//
// �Q�[���J�n�����̕`��kstart.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _START_H_
#define _START_H_
#include "main.h"

// �J�n�����̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
	bool bUse;
}Start;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitStart(void);	// �Q�[���J�n�����̏���������
void UninitStart(void);		// �Q�[���J�n�����̏I������
void UpdateStart(void);		// �Q�[���J�n�����̍X�V����
void DrawStart(void);		// �Q�[���J�n�����̕`�揈��
int GetCount(void);

#endif