//==============================================================================
//
// 3D���f���̕`��kobject.h�l
// AUTHOR : TAKAHASHI SHOTA
//
//==============================================================================
#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"
#include "game.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_OBJECT		(400)						// �����蔻��̖ʂ̐�
#define COLLISION_PARTS	(4 * MAX_OBJECT)			// �����蔻��̖ʂ̐�
//#define COLLISION_PARTS	(80)					// �����蔻��̖ʂ̐�


//==============================================================================
// ���f���̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	D3DXVECTOR3 vtxMinObject, vtxMaxObject;				// ���f���̊e���W�̍ő�l�E�ŏ��l
	LPD3DXBUFFER g_pBuffMatObject = NULL;				// �}�e���A��(�ގ����)�ւ̃|�C���^
	D3DXVECTOR3 aPos[COLLISION_PARTS];					// �����蔻�蒸�_���
	D3DXVECTOR3 vec;
	D3DXVECTOR3 aVec[COLLISION_PARTS];					// �����蔻��x�N�g��
	D3DXVECTOR3 vtx;
	DWORD sizeFVF;										// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 posVec[2];
	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;
	float a;
	bool bUse;
	int nType;
	int nIdx;
	int nNumVtx;										// ���_��
	float RotY = 0.0f;									//setobject
} OBJECT;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitObject(void);	// 3D�I�u�W�F�N�g�̏���������
void UninitObject(void);	// 3D�I�u�W�F�N�g�̏I������
void UpdateObject(void);	// 3D�I�u�W�F�N�g�̍X�V����
void DrawObject(void);		// 3D�I�u�W�F�N�g�̕`�揈��
OBJECT *GetObject(void);	// 3D�I�u�W�F�N�g�̎擾

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

void SetOject(D3DXVECTOR3 Pos, D3DXVECTOR3 rot, int nType);
int GetobjectNumber(void);
int GetobjectDate(void);
int GetobjectType(void);

#endif