//==============================================================================
//
// ���b�V���ǂ̕`��kmeshwall.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _MESHWALL_H_
#define _MESHWALL_H_
#include "main.h"

// �ǂ̍\����
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3	posMove;
	D3DXVECTOR3 rot;
	float fWidth;
	float fHeight;
	bool bUse;
} Meshwall;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshwall(void);		// 3D�|���S���̏���������
void UninitMeshwall(void);		// 3D�|���S���̏I������
void UpdateMeshwall(void);		// 3D�|���S���̍X�V����
void DrawMeshwall(void);		// 3D�|���S���̕`�揈��

#endif
