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

// �}�N����`
#define MAX_OBJECT		(128)	// �I�u�W�F�N�g�̍ő吔
#define MAX_TYPE_OBJECT	(32)	// �e�N�X�`�����̍ő�
#define MAX_TEX_OBJECT	(16)
#define COLLISION_PARTS	(4)		// �����蔻��̖ʂ̐�

// �I�u�W�F�N�g��ނ̗�
//typedef enum
//{
//	OBJECTTYPE_BALOON = 0,
//	OBJECTTYPE_BLOCK,
//	OBJECTTYPE_MAX
//}OBJECTTYPE;

// �I�u�W�F�N�g�̎�ނ��Ƃ̍\����
typedef struct
{
	LPD3DXMESH pMeshObject;
	LPD3DXBUFFER pBuffMatObject;	// �}�e���A��(�ގ����)�ւ̃|�C���^
	DWORD nNumMatObject;
	LPDIRECT3DTEXTURE9 pTextureObject[MAX_TEX_OBJECT];
	char aFileName[64];
	D3DXVECTOR3 vtxMinObject, vtxMaxObject;	// ���f���̊e���W�̍ő�l�E�ŏ��l
} ObjectType;

// �I�u�W�F�N�g�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	int nIdx;
	D3DXVECTOR3 aPos[COLLISION_PARTS];			// �I�u�W�F�N�g4���_
	D3DXVECTOR3 aVec[COLLISION_PARTS];			// �I�u�W�F�N�g4�ӂ̃x�N�g��
	D3DXVECTOR3 vtxMinObject, vtxMaxObject;		// ���f���̊e���W�̍ő�l�E�ŏ��l
	float fPlayerVec[COLLISION_PARTS];			// �����蔻��p�ϐ�
	bool bBreak;
	int nType;									// �I�u�W�F�N�g�̎��
	bool bUse;
} ObjectInfo;

typedef struct
{
	ObjectInfo objectInfo[MAX_OBJECT];
	ObjectType type[MAX_TYPE_OBJECT];
	int nNumType;
} Object;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitObject(void);	// 3D�I�u�W�F�N�g�̏���������
void UninitObject(void);	// 3D�I�u�W�F�N�g�̏I������
void UpdateObject(void);	// 3D�I�u�W�F�N�g�̍X�V����
void DrawObject(void);		// 3D�I�u�W�F�N�g�̕`�揈��
Object *GetObject(void);	// 3D�I�u�W�F�N�g�̎擾
void StageObject(int nStage);	// �X�e�[�W���Ƃ̃I�u�W�F�N�g�z�u

void SetObject(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nType,bool bBreak);

bool CollisionVec(
	D3DXVECTOR3 *pPos,
	D3DXVECTOR3 *pPosOld,
	D3DXVECTOR3 *pMove,
	float fInRadius,
	float fHeight,
	int nCntPlayer);

void LoadObject(void);

#endif