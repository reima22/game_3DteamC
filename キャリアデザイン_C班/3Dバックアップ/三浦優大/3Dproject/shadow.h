#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//================
//構造体の定義
//================
typedef struct
{
	D3DXVECTOR3 Pos;//位置
	D3DXMATRIX mtxworld;//ワールドマトリックス
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 rot;//向き
	bool bUse;
}SHADOW;

//===============
//プロトタイプ宣言
//===============
HRESULT InitShadow(void);//初期化処理
void UninitShadow(void);//終了処理
void UpdateShadow(void);//更新処理
void DrawShadow(void);//描画処理
void SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth);
#endif

