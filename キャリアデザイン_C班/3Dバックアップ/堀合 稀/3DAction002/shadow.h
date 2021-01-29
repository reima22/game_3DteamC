//==============================================================================
//
// �e�̕`��kshadow.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_SHADOW	(128)	// �e�̍ő吔

//==============================================================================
// �e�̍\����
//==============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// �p�x
	float fWidth;			// ����
	float fDepth;			// ���s��
	bool bUse;				// �g�p���Ă��邩
} Shadow;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitShadow(void);		// �e�̏���������
void UninitShadow(void);		// �e�̏I������
void UpdateShadow(void);		// �e�̍X�V����
void DrawShadow(void);			// �e�̕`�揈��
int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth);
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos);

#endif