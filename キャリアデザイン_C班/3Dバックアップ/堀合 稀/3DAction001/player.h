//==============================================================================
//
// 3Dモデルの描画〔player.h〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

// マクロ定義
#define MODEL_PARTS		(14)

// モデルの構造体
typedef struct
{
	LPD3DXMESH pMeshModel;		// メッシュへのポインタ
	LPD3DXBUFFER pBuffMatModel;	// マテリアルへのポインタ
	DWORD nNumMatModel;			// マテリアルの数
	D3DXVECTOR3 pos;			// 位置(オフセット)
	D3DXVECTOR3 rot;			// 向き
	D3DXMATRIX mtxWorld;		// ワールドマトリックス
	int nIdxModelParent;		// 親モデルのインデックス
}Model;

// プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	int nIdx;
	Model aModel[MODEL_PARTS];		// モデル(パーツ)
	int nNumModel;			// モデル(パーツ)数
} Player;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
HRESULT InitPlayer(void);	// 3Dモデルの初期化処理
void UninitPlayer(void);		// 3Dモデルの終了処理
void UpdatePlayer(void);		// 3Dモデルの更新処理
void DrawPlayer(void);		// 3Dモデルの描画処理
Player *GetPlayer(void);		// 3Dモデルの取得

#endif