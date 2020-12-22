//-----------------------------------------------------------------------------
//
// カメラの処理
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 posV;			//現在の視点
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posR;			//現在の注視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 rot;			//カメラの向き
	D3DXVECTOR3 VecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
	float Distance;				//注視点との距離
	int Rpos;					//モデルの前

}Camera;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
Camera *GetCamera(void);

#endif _CAMERA_H_


