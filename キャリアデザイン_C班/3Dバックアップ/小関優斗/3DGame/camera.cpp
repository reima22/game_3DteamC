//-----------------------------------------------------------------------------
//
// カメラの処理
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "camera.h"
#include "model.h"
#include "input.h"

//マクロ
#define MOVE_CAMERA_SPEED (3.0f)
#define DISTANCE (500)
#define MOVE_ROT (0.0425f)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
Camera g_Camera;	//カメラ情報

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
void InitCamera(void)
{
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f,0.0f);		//カメラの角度
	g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f,-DISTANCE);//視点
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//注視点
	g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//法線ベクトル
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitCamera(void)
{

}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void UpdateCamera(void)
{

	Model *pModel;
	pModel = GetModel();
	
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Camera.posVDest.x = pModel->pos.x - 20 * sin(pModel->rotDest.y);
	g_Camera.posVDest.z = pModel->pos.z - 20 * cosf(pModel->rotDest.y);
	g_Camera.posVDest.y = pModel->pos.y + 200;

	g_Camera.posV += (g_Camera.posVDest - g_Camera.posV) * 0.2f;
	g_Camera.posR += (g_Camera.posRDest - g_Camera.posR) * 0.2f;

	//カメラ移動右
	if (GetKeyboardPress(DIK_D) == true)
	{	
		g_Camera.posV.x += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
	}									 
	//カメラ移動左						 
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_Camera.posV.x -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
	}

	//カメラ移動奥						 
	if (GetKeyboardPress(DIK_W) == true) 
	{									 
		g_Camera.posV.x += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
	}									  
	//カメラ移動手前						
	if (GetKeyboardPress(DIK_S) == true)  
	{									  
		g_Camera.posV.x -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;

	}

	//カメラ移動視点上
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_Camera.posV.y += MOVE_CAMERA_SPEED;
	}

	//カメラ移動視点下
	if (GetKeyboardPress(DIK_B) == true)
	{
		g_Camera.posV.y -= MOVE_CAMERA_SPEED;
	}

	//カメラ移動注視点上
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_Camera.posR.y += MOVE_CAMERA_SPEED;
	}
	//カメラ移動注視点下
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_Camera.posR.y -= MOVE_CAMERA_SPEED;
	}

	if (g_Camera.rot.y >= D3DX_PI)
	{
		g_Camera.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Camera.rot.y <= -D3DX_PI)
	{
		g_Camera.rot.y += D3DX_PI * 2.0f;
	}

	//カメラ移動視点左回転
	if (GetKeyboardPress(DIK_Z) == true)
	{		
		
		g_Camera.rot.y += MOVE_ROT;
		
		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * DISTANCE;
	}
	
	//カメラ移動視点右回転
	if (GetKeyboardPress(DIK_C) == true)
	{
		
		g_Camera.rot.y -= MOVE_ROT;
		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * DISTANCE;
	}

	//カメラ移動注視点左回転
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_Camera.rot.y -= MOVE_ROT;
		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * DISTANCE;
	}

	//カメラ移動注視点右回転
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_Camera.rot.y += MOVE_ROT;
		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * DISTANCE;

	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動
		g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f, -DISTANCE);	//視点
		g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//注視点
		g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//法線ベクトル
	}

}

//-----------------------------------------------------------------------------
//設定処理
//-----------------------------------------------------------------------------
void SetCamera(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f, 10000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	//ビューの初期化
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.VecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

}

//
Camera *GetCamera(void)
{
	return &g_Camera;
}
