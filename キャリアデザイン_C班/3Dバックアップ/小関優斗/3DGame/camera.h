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
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 rot;			//カメラの向き
	D3DXVECTOR3 VecU;			//上方向ベクトル
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス

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


