//-----------------------------------------------------------------
//
// プレイヤーの処理 (player.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _MESHFILD_H_
#define _MESHFILD_H_

#include "main.h"

//---------------------------------------------------------------------------- -
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_MESHFILD (4)				//壁の上限

//-----------------------------------------------------------------------------
//構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	bool bUse;
}MESHFILD;

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MOVE_NUMBER (6)
#define MOVE_NUMBER2 (50)

//===============
//プロトタイプ宣言
//===============
HRESULT InitMeshfild(void);
void UninitMeshfild(void);
void UpdateMeshfild(void);
void DrawMeshfild(void);
#endif


