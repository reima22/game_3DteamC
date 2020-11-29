//-----------------------------------------------------------------------------
//
// 壁の処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;

}Wall;

//プロトタイプ宣言
HRESULT InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

#endif _WALL_H_
