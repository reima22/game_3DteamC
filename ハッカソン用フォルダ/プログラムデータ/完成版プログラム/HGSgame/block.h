//==============================================================================
//
// �u���b�N�̕`��kblock.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define BLOCK_MAX	(256)	// �u���b�N�̍ő��
#define BLOCK_SIZEX	(40)	// �u���b�N�̕�
#define BLOCK_SIZEY	(40)	// �u���b�N�̍���
#define BLOCK_SET	(16)	// 1�x�̃u���b�N�̏o����

//==============================================================================
// �u���b�N�̏��
//==============================================================================
typedef enum
{
	BLOCKSTATE_NORMAL = 0,	// �ʏ���
	BLOCKSTATE_DAMAGE,		// �_���[�W���
	BLOCKSTATE_MAX
} BLOCKSTATE;

//==============================================================================
// �u���b�N�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	float fWidth;		// ��
	float fHeight;		// ����
	int nLife;			// �ϋv�l
	bool bUse;			// �g�p���Ă��邩�ǂ���
	bool bBreak;		// �j��ł��邩�ǂ���
	BLOCKSTATE state;	// �u���b�N�̏��
	int nCntState;		// �ω���ԃJ�E���g
} BLOCK;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitBlock(void);		// �u���b�N�̏���������
void UninitBlock(void);			// �u���b�N�̏I������
void UpdateBlock(void);			// �u���b�N�̍X�V����
void DrawBlock(void);			// �u���b�N�̕`�揈��
void SetBlock(					// �u���b�N�̐ݒ�
	D3DXVECTOR3 pos,			// �ʒu
	D3DXVECTOR3 move,			// �ړ���
	float fWidth,				// ��
	float fHeight,				// ����
	int nLife,					// �ϋv��
	bool bBreak);				// �j��ł��邩�ǂ���
void SetVertexBlock(int nIdx);	// �u���b�N�̒��_���W�擾
BLOCK *GetBlock(void);			// �u���b�N�̏��擾
bool HitBlock(int nIdx,int nDamage);	// �u���b�N�j�󏈗�

#endif