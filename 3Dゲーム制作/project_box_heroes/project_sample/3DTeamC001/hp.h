#ifndef _HP_H_
#define _HP_H_

#include "main.h"

//-----------------------------------------------------------------------------
//構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 move;						//移動量
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	int nLife;
	int nType;
	float fWidth;
	float fHeigth;
	int nLifeBullet;
	bool bUse;
}HP;

//===============
//プロトタイプ宣言
//===============
HRESULT InitHp(void);//初期化処理
void UninitHp(void);//終了処理
void UpdateHp(void);//更新処理
void DrawHp(void);//描画処理
void SetVertexHp(int nIdx);
#endif
