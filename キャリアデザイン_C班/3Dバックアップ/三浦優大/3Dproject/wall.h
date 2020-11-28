#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//=============================
//カメラの構造体
//=============================
typedef struct
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR3 rot;//向き
	bool bUse;//使われているか
}Wall;

//===============
//プロトタイプ宣言
//===============
HRESULT InitWall(void);//初期化処理
void UninitWall(void);//終了処理
void UpdateWall(void);//更新処理
void DrawWall(void);//描画処理
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//壁処理
#endif
