//==============================================================================
//
// 3D���f���̕`��kobject.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

// ���f���̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 vtxMinObject, vtxMaxObject;	// ���f���̊e���W�̍ő�l�E�ŏ��l
	int nIdx;
} Object;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitObject(void);	// 3D�I�u�W�F�N�g�̏���������
void UninitObject(void);	// 3D�I�u�W�F�N�g�̏I������
void UpdateObject(void);	// 3D�I�u�W�F�N�g�̍X�V����
void DrawObject(void);		// 3D�I�u�W�F�N�g�̕`�揈��
Object *GetObject(void);	// 3D�I�u�W�F�N�g�̎擾
bool CollisionObject(		// �����蔻��
	D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove,
	float fWidthMax,
	float fWidthMin,
	float fDepthMax,
	float fDepthMin);

bool CollisionVec(
	D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove,
	float fWidthMax,
	float fWidthMin,
	float fDepthMax,
	float fDepthMin,
	float fHeightMax,
	float fheightMin);

#endif