//-----------------------------------------------------------------
//
// プレイヤーの処理 (camera.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "camera.h"
#include "input.h"
#include "model.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
CAMERA g_camera;									//カメラの情報
float g_model;

//-----------------------------------------------------------------------------
// カメラの初期化処理
//-----------------------------------------------------------------------------
void InitCamera(void)
{
	//角度の初期化
	g_camera.Camera = 0;
	g_model = 0;

	//視点
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);

	//注視点
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//カメラの向き
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// カメラの終了処理
//-----------------------------------------------------------------------------
void UninitCamera(void)
{
}

//-----------------------------------------------------------------------------
// カメラの更新処理
//-----------------------------------------------------------------------------
void UpdateCamera(void)
{
	MODEL  *pModel;
	pModel = GetModel();

	////カメラの移動
	//if (GetKeyboardPress(DIK_A) == true)
	//{
	//	g_camera.posV.x += 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z += 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}

	//if (GetKeyboardPress(DIK_D) == true)
	//{
	//	g_camera.posV.x -= 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z -= 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}


	//if (GetKeyboardPress(DIK_S) == true)
	//{
	//	g_camera.posV.x -= 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z += 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}

	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	g_camera.posV.x += 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z -= 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}

	//カメラがモデル追従
	g_camera.posR = pModel->pos;
	g_camera.posV += pModel->move;
	/*g_camera.posV.x = pModel->move.x;
	g_camera.posV.z = pModel->move.z;
	g_camera.posV.y = pModel->pos.y;*/

	//視点移動
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.Camera -= 0.1f;
		//g_camera.posV.x = g_camera.posR.x + sinf(g_fAnglecamera) * g_fLengthcamera;
		//g_camera.posV.z = g_camera.posR.z + cosf(g_fAnglecamera) * g_fLengthcamera;
		g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.Camera += 0.1f;
		//g_camera.posV.x = g_camera.posR.x + sinf(g_fAnglecamera) * g_fLengthcamera;
		//g_camera.posV.z = g_camera.posR.z + cosf(g_fAnglecamera) * g_fLengthcamera;
		g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	//注視点移動
	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.Camera -= 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.Camera += 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	//回転角度リセット
	if (g_camera.Camera >= D3DX_PI * 2)
	{
		g_camera.Camera = 0;
	}

	if (g_camera.Camera <= -D3DX_PI * 2)
	{
		g_camera.Camera = 0;
	}

	//カメラリセット
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		g_camera.Camera = 0;

		//視点
		g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);

		//注視点
		//g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//カメラの向き
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//モデル位置
		pModel->pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);

		//モデル向き
		pModel->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//-----------------------------------------------------------------------------
// カメラの設定
//-----------------------------------------------------------------------------
void SetCamera(void)
{
	//プロジェクトマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxprojection);

	//プロジェクションマトリックスを作成
	//1000.0f 視野の範囲
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxprojection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 10.0f, 1000.0f);

	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxprojection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

CAMERA *GetCamera(void)
{
	return &g_camera;
}
