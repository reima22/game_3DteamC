//-----------------------------------------------------------------------------
//
// 弾の処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _BULLET_H_
#define _BULLET_H_

#pragma once
#include "main.h"


//-----------------------------------------------------------------------------
// マクロ定義
//---------------------------------------------------------------------------
#define MOVE_BULLET (5)				//弾の速度
#define BULLET_SIZE (10)			//弾の大きさ
#define MAX_BULLET (256)			//弾の上限
#define MAX_BULLET_TYPE (2)			//弾の種類
#define PLAYER_BULLET (1)
#define ENEMY_BULLET (0)
//弾の状態
typedef enum
{
	BULLETTYPE_PLAYER = 0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MACHINE,
	BULLETTYPE_MAX,
}BULLETTYPE;

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 move;	//移動量
	D3DXMATRIX mtxWorldBullet;
	int nLife;			//弾の寿命
	bool bUse;			//弾の使用状況
}Bullet;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType);
void SetVertexBullet(int nIdx);
Bullet *GetBullet(void);

#endif _BULLET_H_