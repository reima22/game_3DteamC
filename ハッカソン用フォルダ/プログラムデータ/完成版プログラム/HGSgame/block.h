//==============================================================================
//
// ブロックの描画〔block.h〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _BLOCK_H_
#define _BLOCK_H_
#include "main.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define BLOCK_MAX	(256)	// ブロックの最大個数
#define BLOCK_SIZEX	(40)	// ブロックの幅
#define BLOCK_SIZEY	(40)	// ブロックの高さ
#define BLOCK_SET	(16)	// 1度のブロックの出現数

//==============================================================================
// ブロックの状態
//==============================================================================
typedef enum
{
	BLOCKSTATE_NORMAL = 0,	// 通常状態
	BLOCKSTATE_DAMAGE,		// ダメージ状態
	BLOCKSTATE_MAX
} BLOCKSTATE;

//==============================================================================
// ブロックの構造体
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動力
	float fWidth;		// 幅
	float fHeight;		// 高さ
	int nLife;			// 耐久値
	bool bUse;			// 使用しているかどうか
	bool bBreak;		// 破壊できるかどうか
	BLOCKSTATE state;	// ブロックの状態
	int nCntState;		// 変化状態カウント
} BLOCK;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
HRESULT InitBlock(void);		// ブロックの初期化処理
void UninitBlock(void);			// ブロックの終了処理
void UpdateBlock(void);			// ブロックの更新処理
void DrawBlock(void);			// ブロックの描画処理
void SetBlock(					// ブロックの設定
	D3DXVECTOR3 pos,			// 位置
	D3DXVECTOR3 move,			// 移動量
	float fWidth,				// 幅
	float fHeight,				// 高さ
	int nLife,					// 耐久力
	bool bBreak);				// 破壊できるかどうか
void SetVertexBlock(int nIdx);	// ブロックの頂点座標取得
BLOCK *GetBlock(void);			// ブロックの情報取得
bool HitBlock(int nIdx,int nDamage);	// ブロック破壊処理

#endif