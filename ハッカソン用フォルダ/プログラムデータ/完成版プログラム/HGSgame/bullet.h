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
// �G�����̒e�̏��
//==============================================================================
//typedef enum
//{
//	BULLETTYPE_PLAYER = 0,	// ���@�̒e
//	BULLETTYPE_ENEMY,		// �G�̒e
//	BULLETTYPE_MAX
//} BULLETTYPE;

//==============================================================================
// ���@�̒e�̑������
//==============================================================================
//typedef enum
//{
//	SETBULLET_NORMAL = 0,	// �ʏ�e
//	SETBULLET_WAVE,			// �g��U��
//	SETBULLET_MISSILE,		// �~�T�C��
//	SETBULLET_REVERSEWAVE,	// ����g��U��
//	SETBULLET_MAX
//} SETBULLET;

//==============================================================================
// �e�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	int nLife;			// ����
	bool bUse;			// �g�p���Ă��邩�ǂ���
	//int nType;			// �e�̎��
	//BULLETTYPE type;	// �G�����̎��
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
//SETBULLET GetState(void);		// �e�̏�ԏ��擾

#endif