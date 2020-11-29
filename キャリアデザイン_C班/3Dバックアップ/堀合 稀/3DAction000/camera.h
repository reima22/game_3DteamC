//==============================================================================
//
// カメラの設定〔camera.h〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

//==============================================================================
// カメラの構造体
//==============================================================================
typedef struct
{
	D3DXVECTOR3 posV;			// 視点
	D3DXVECTOR3 posR;			// 注視点
	D3DXVECTOR3 vecU;			// 上方向ベクトル
	D3DXMATRIX mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX mtxView;			// ビューマトリックス
	D3DXVECTOR3 moveV;			// 視点の移動量
	D3DXVECTOR3 moveR;			// 注視点の移動量
	D3DXVECTOR3 moveXVR;		// 視点・注視点両方同時のX軸移動量
	D3DXVECTOR3 moveZVR;		// 視点・注視点両方同時のZ軸移動量
	D3DXVECTOR3 rot;			// カメラの角度
	float fLength;				// 注視点との距離
} Camera;

//==============================================================================
// プロトタイプ宣言
//==============================================================================
void InitCamera(void);		// カメラの初期化処理
void UninitCamera(void);	// カメラの終了処理
void UpdateCamera(void);	// カメラの更新処理
void SetCamera(void);		// カメラの設定
Camera GetCamera(void);		// カメラの取得

#endif
