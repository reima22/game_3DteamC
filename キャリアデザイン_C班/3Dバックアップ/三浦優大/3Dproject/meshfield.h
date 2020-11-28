#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//構造体の定義
typedef struct
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR3 oldPos;//位置
	D3DXVECTOR3 move;//移動量
	int g_nCounterAnim;//アニメーション
	int g_nPatternAnim;//アニメーション
	int g_nseetAnim;//アニメーション
	//PLAYERSTATE state;//状態
	int nCounterState;//状態カウンター
	int nCounterStateStar;
	int nType;//種類
	int nLife;//寿命
	bool bUse;//使用しているかどうか
	float g_fLengthPlayer;//対角線の長さ
	float g_fAnglePlayer;//対角線の角度
}MESHFIELD;

//===============
//プロトタイプ宣言
//===============
HRESULT InitMeshfield(void);//初期化処理
void UninitMeshfield(void);//終了処理
void UpdateMeshfield(void);//更新処理
void DrawMeshfield(void);//描画処理
#endif
