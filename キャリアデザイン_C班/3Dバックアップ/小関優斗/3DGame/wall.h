//-----------------------------------------------------------------------------
//
// �ǂ̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;

}Wall;

//�v���g�^�C�v�錾
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

#endif _WALL_H_
