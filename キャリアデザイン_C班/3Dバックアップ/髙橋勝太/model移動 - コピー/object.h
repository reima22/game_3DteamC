//-----------------------------------------------------------------
//
// プレイヤーの処理 (model.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
}OBJECT;

//===============
//プロトタイプ宣言
//===============
HRESULT InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
OBJECT*GetObject(void);
#endif

