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
#define MAX_ITEM		(128)		// �A�C�e���̍ő吔

//==============================================================================
// �A�C�e���̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXCOLOR col;		// �F
	int nType;			// ���
	bool bUse;			// �g�p���Ă��邩�ǂ���
	D3DXVECTOR3 vtxMinObject, vtxMaxObject;	// ���f���̊e���W�̍ő�l�E�ŏ��l
	D3DXVECTOR3 posPoint[FOUR_POINT];	// 4���_�̈ʒu
	D3DXVECTOR3 vecPoint[FOUR_POINT];	// �l�ӂ̃x�N�g��
	int nIdx;
	//float fAnim;		// �e�N�X�`���A�j���[�V�����J�b�g��
	//bool bHiScore;		// ���X�R�A��Ԃ̃R�C��
} ITEM;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitItem(void);			// �A�C�e���̏���������
void UninitItem(void);			// �A�C�e���̏I������
void UpdateItem(void);			// �A�C�e���̍X�V����
void DrawItem(void);			// �A�C�e���̕`�揈��
void SetItem(D3DXVECTOR3 pos);	// �A�C�e���̔z�u
void TouchItem(
	D3DXVECTOR3 *pPos,
	float fInRadius,
	float fHeight,
	int nCntPlayer);			// �A�C�e���̎擾
ITEM *GetItem(void);			// �A�C�e���̏��
int RandItem(void);				// �����_���Ńn�C�X�R�A�A�C�e���̑I��

#endif
