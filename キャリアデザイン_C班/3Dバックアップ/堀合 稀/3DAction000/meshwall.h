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
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �����ʒu
	D3DXVECTOR3	posMove;	// �����ʒu����̈ړ������ʒu
	D3DXVECTOR3 rot;		// ����
	float fWidth;			// ��
	float fHeight;			// ����
	int nCntX;				// ��ӓ�����̒��_��(��)
	int nCntY;				// ��ӓ�����̒��_��(�c)
	bool bUse;				// �g�p���
} Meshwall;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshwall(void);		// ���b�V���ǂ̏���������
void UninitMeshwall(void);		// ���b�V���ǂ̏I������
void UpdateMeshwall(void);		// ���b�V���ǂ̍X�V����
void DrawMeshwall(void);		// ���b�V���ǂ̕`�揈��
void SetMeshwall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);			// ���b�V���ǂ̕`�揈��

#endif
