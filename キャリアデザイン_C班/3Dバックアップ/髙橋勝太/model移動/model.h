//-----------------------------------------------------------------
//
// プレイヤーの処理 (model.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 rotmove;		//向き
	D3DXVECTOR3 rotDest;		//向き
	D3DXVECTOR3 MinModel;
	D3DXVECTOR3 MaxModel;
}MODEL;

//===============
//プロトタイプ宣言
//===============
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);
#endif

