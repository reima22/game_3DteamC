//==============================================================================
//
// メッシュ壁の描画〔meshwall.h〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _MESHWALL_H_
#define _MESHWALL_H_
#include "main.h"

// 壁の構造体
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3	posMove;
	D3DXVECTOR3 rot;
	float fWidth;
	float fHeight;
	bool bUse;
} Meshwall;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
HRESULT InitMeshwall(void);		// 3Dポリゴンの初期化処理
void UninitMeshwall(void);		// 3Dポリゴンの終了処理
void UpdateMeshwall(void);		// 3Dポリゴンの更新処理
void DrawMeshwall(void);		// 3Dポリゴンの描画処理

#endif
