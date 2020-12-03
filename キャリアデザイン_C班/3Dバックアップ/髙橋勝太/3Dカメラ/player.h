//-----------------------------------------------------------------
//
// プレイヤーの処理 (player.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _PLYER_H_
#define _PLYER_H_

#include "main.h"

//---------------------------------------------------------------------------- -
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_PLAYER (6)				//壁の上限

//-----------------------------------------------------------------------------
//構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	bool bUse;
}PLAYER;

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MOVE_NUMBER (6)
#define MOVE_NUMBER2 (50)

//===============
//プロトタイプ宣言
//===============
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayer(D3DXVECTOR3 pos);
#endif

