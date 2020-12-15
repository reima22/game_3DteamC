//-----------------------------------------------------------------
//
// プレイヤーの処理 (camera.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------

//構造体
typedef struct
{
	//D3DXVECTOR3 rot;		
	D3DXVECTOR3 posV;			//カメラの向き
	D3DXVECTOR3 posVDest;		//カメラの向き
	D3DXVECTOR3 posR;			//カメラの視点
	D3DXVECTOR3 posRDest;		//カメラの視点
	D3DXVECTOR3 vecU;			//カメラの注視点
	D3DXMATRIX mtxprojection;
	D3DXMATRIX mtxView;
	float Camera;				//カメラの角度を変えるのに必要
}CAMERA;

//===============
//プロトタイプ宣言
//===============
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
#endif

