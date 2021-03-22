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
	float fWidthMax;
	float fHeightMax;
	int nWidth;				// ��
	int nHeight;			// �s��
	int nWidthPoint;		// ���̒��_��
	int nHeightPoint;		// �����̒��_��
	int nAllPoint;
	int nPolygon;
	int nIdxPoint;
	bool bUse;				// �g�p���
	D3DXVECTOR3 posPoint[FOUR_POINT];	// 4���_�̈ʒu
	D3DXVECTOR3 vecPoint[FOUR_POINT];	// �l�ӂ̃x�N�g��
} Meshwall;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshwall(void);		// ���b�V���ǂ̏���������
void UninitMeshwall(void);		// ���b�V���ǂ̏I������
void UpdateMeshwall(void);		// ���b�V���ǂ̍X�V����
void DrawMeshwall(void);		// ���b�V���ǂ̕`�揈��
void SetMeshwall(				// ���b�V���ǂ̐ݒ菈��
	D3DXVECTOR3 pos, 
	D3DXVECTOR3 rot, 
	float fWidth, 
	float fHeight,
	int nWidth,
	int nHeight);	

void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 move, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);

#endif
