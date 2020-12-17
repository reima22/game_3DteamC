//==============================================================================
//
// �e�̕`��kbullet.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"

//==============================================================================
// �e�̍\����
//==============================================================================
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ�����
	float fmove;		// �ړ���
	//D3DXVECTOR3 rot;	// ����
	int nLife;			// ����
	bool bUse;			// �g�p���Ă��邩�ǂ���
} BULLET;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitBullet(void);		// �e�̏���������
void UninitBullet(void);		// �e�̏I������
void UpdateBullet(void);		// �e�̍X�V����
void DrawBullet(void);			// �e�̕`�揈��
void SetBullet(
	D3DXVECTOR3 pos, 
	D3DXVECTOR3 move,
	int nLife);					// �e�̐ݒ�
void HitBullet(void);			// �e�̖���
void SetVertexBullet(int nIdx);	// �e�̒��_���W�擾

#endif