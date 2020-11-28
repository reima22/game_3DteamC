#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//===============
//構造体の定義
//===============
typedef struct
{
	D3DXVECTOR3 Pos;//位置
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 rotmove;//向き
}MODEL;

//==========================
//プロトタイプ宣言
//==========================
void InitModel(void);//初期化処理
void UninitModel(void);//終了処理
void UpdateModel(void);//更新処理
void DrawModel(void);//カメラの設定,Drawの一番上で定義
MODEL *GetModel(void);
#endif
