//==============================================================================
//
// �A�C�e���̕`��kitem.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _ITEM_H_
#define _ITEM_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_ITEM		(8)		// �A�C�e���̍ő吔


typedef enum
{
	ITEMTYPE_KNIFE= 0,		// �i�C�t
	ITEMTYPE_HANDGUN,		// �n���h�K��
	ITEMTYPE_MACHINEGUN,	// �}�V���K��
	ITEMTYPE_RANCHER,		// ���P�b�g�����`���[
	ITEMTYPE_MAX
}ItemType;

typedef struct
{
	LPD3DXMESH pMeshItem;
	LPD3DXBUFFER pBuffMatItem;
	DWORD nNumMatItem;
	char aFileName[64];
	D3DXVECTOR3 vtxMinItem, vtxMaxItem;
}ItemTypeInfo;

//==============================================================================
// �A�C�e���̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 rot;						// �p�x
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXCOLOR col;							// �F
	ItemType type;
	bool bUse;								// �g�p���Ă��邩�ǂ���
	D3DXVECTOR3 vtxMinItem, vtxMaxItem;		// ���f���̊e���W�̍ő�l�E�ŏ��l
	D3DXVECTOR3 posPoint[FOUR_POINT];		// 4���_�̈ʒu
	D3DXVECTOR3 vecPoint[FOUR_POINT];		// �l�ӂ̃x�N�g��
	bool bSet;
	int nIdx;
} ItemInfo;

typedef struct
{
	ItemInfo iteminfo[MAX_ITEM];
	ItemTypeInfo typeinfo[ITEMTYPE_MAX];
	int nNumType;
	int nSetItem;
	int nSetCnt;
}Item;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitItem(void);			// �A�C�e���̏���������
void UninitItem(void);			// �A�C�e���̏I������
void UpdateItem(void);			// �A�C�e���̍X�V����
void DrawItem(void);			// �A�C�e���̕`�揈��
void SetItem(D3DXVECTOR3 pos,int nType);	// �A�C�e���̔z�u
void TouchItem(
	D3DXVECTOR3 *pPos,
	float fInRadius,
	float fHeight,
	int nCntPlayer);			// �A�C�e���̎擾
Item *GetItem(void);			// �A�C�e���̏��
void RandItem(int nStage);				// �����_���A�C�e���̑I��
void LoadItem(void);

#endif
