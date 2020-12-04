//==============================================================================
//
// �r���{�[�h�̕`��kbillboard.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_
#include "main.h"

// �}�N����`
//#define MAX_WALL	(4)	// �ǂ̍ő吔

typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	bool bUse;
} Billboard;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitBillboard(void);	// �r���{�[�h�̏���������
void UninitBillboard(void);		// �r���{�[�h�̏I������
void UpdateBillboard(void);		// �r���{�[�h�̍X�V����
void DrawBillboard(void);		// �r���{�[�h�̕`�揈��

#endif
