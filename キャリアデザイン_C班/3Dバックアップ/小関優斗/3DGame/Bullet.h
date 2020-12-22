//-----------------------------------------------------------------------------
//
// �e�̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _BULLET_H_
#define _BULLET_H_

#pragma once
#include "main.h"


//-----------------------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------------------
#define MOVE_BULLET (5)				//�e�̑��x
#define BULLET_SIZE (10)			//�e�̑傫��
#define MAX_BULLET (256)			//�e�̏��
#define MAX_BULLET_TYPE (2)			//�e�̎��
#define PLAYER_BULLET (1)
#define ENEMY_BULLET (0)
//�e�̏��
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MACHINE,
	BULLETTYPE_MAX,
}BULLETTYPE;

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXMATRIX mtxWorldBullet;
	int nLife;			//�e�̎���
	bool bUse;			//�e�̎g�p��
}Bullet;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void SetVertexBullet(int nIdx);
Bullet *GetBullet(void);

#endif _BULLET_H_