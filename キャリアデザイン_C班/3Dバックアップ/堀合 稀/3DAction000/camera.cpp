//==============================================================================
//
// カメラの設定〔camera.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "camera.h"
#include "model.h"
#include "input.h"

//==============================================================================
// マクロ定義
//==============================================================================
//#define CAMERA_POSV_X	(0.0f)
#define CAMERA_POSV_Y	(100.0f)
#define CAMERA_POSV_Z	(200.0f)
//#define CAMERA_ANGLE	(atan2f(600, 300))	// カメラの角度
#define CAMERA_MOVE		(2.0f)
#define CAMERA_TURN		(100.0f)
#define CAMERA_RANGE	(200.0f)

//==============================================================================
// グローバル変数
//==============================================================================
Camera g_camera;

//==============================================================================
// 初期化処理
//==============================================================================
void InitCamera(void)
{
	// ローカル変数宣言
	Model model = *GetModel();

	// 構造体の初期化
	g_camera.posV = D3DXVECTOR3(model.pos.x, model.pos.y + 100.0f, model.pos.z - 200.0f);		// 視点位置
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										// 注視点位置
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);										// 上方向ベクトル
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);										// 移動量

	//g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 視点の移動量
	//g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 注視点の移動量
	//g_camera.moveXVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 視点・注視点両方同時のX軸移動量
	//g_camera.moveZVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 視点・注視点両方同時のZ軸移動量

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// カメラの角度

	g_camera.fLength = CAMERA_RANGE;									// 視点・注視点間の距離

	//if (g_camera.fLength < 0.0f)
	//{
	//	g_camera.fLength *= -1;
	//}
}

//==============================================================================
// 終了処理
//==============================================================================
void UninitCamera(void)
{

}

//==============================================================================
// 更新処理
//==============================================================================
void UpdateCamera(void)
{
	// 注視点との距離
	//g_camera.fLength = sqrtf(
	//	(g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y) + 
	//	(g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));

	// ローカル変数宣言
	Model model = *GetModel();

	// リセット
	if (GetKeyboardTrigger(KEYINFO_SPACE) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, CAMERA_POSV_Y, -CAMERA_POSV_Z);	// 現在の視点位置
		g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 目的の視点位置
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 現在の注視点位置
		g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 目的の注視点位置
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// 上方向ベクトル
		g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 移動量
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// カメラの角度
	}

	 //視点・注視点の移動
	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_camera.move.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z += cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_camera.move.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_camera.move.x -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z += sinf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_camera.move.x += cosf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z -= sinf(g_camera.rot.y) * CAMERA_MOVE;
	//}

	 //注視点の移動(左右)
	//if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y += D3DX_PI * 2.0f;
	//	}
	//}
	//if (GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI * 2.0f;
	//	}
	//}

	// 注視点の移動(上下)
	if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	{
		g_camera.posR.y += CAMERA_MOVE;
	}
	if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	{
		g_camera.posR.y -= CAMERA_MOVE;
	}

	 //視点の移動(左右)ZCキー
	if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true)
	{
		g_camera.rot.y += D3DX_PI / CAMERA_TURN;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	}
	if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true)
	{
		g_camera.rot.y -= D3DX_PI / CAMERA_TURN;

		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	}


	// 視点の移動(上下)
	if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true)
	{
		g_camera.posV.y += CAMERA_MOVE;
	}
	if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true)
	{
		g_camera.posV.y -= CAMERA_MOVE;
	}

	// 注視点へのズーム処理
	if (GetKeyboardPress(KEYINFO_ZOOMIN) == true)
	{
		g_camera.fLength += 1.0f;
	}
	if (GetKeyboardPress(KEYINFO_ZOOMOUT) == true)
	{
		g_camera.fLength -= 1.0f;
	}

	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}
	else if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}

	// 移動量の減衰(慣性)
	//g_camera.move.x += (0.0f - g_camera.move.x) * 0.4f;
	//g_camera.move.z += (0.0f - g_camera.move.z) * 0.4f;

	// 移動量の加算
	//g_camera.posV.x += g_camera.move.x;
	//g_camera.posV.z += g_camera.move.z;
	//g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;

	// モデルの位置へ注視点を置く
	//g_camera.posR.x = model.pos.x;
	//g_camera.posR.z = model.pos.z;
	g_camera.posV.x = model.pos.x + sinf(g_camera.rot.y) * -g_camera.fLength;
	g_camera.posV.z = model.pos.z + cosf(g_camera.rot.y) * -g_camera.fLength;
	//g_camera.posV.y = model.pos.y + cosf(g_camera.rot.x) * 200.0f;

	// 目的の注視点
	g_camera.posRDest.x = model.pos.x - 15.0f * sinf(model.rotDest.y);
	g_camera.posRDest.z = model.pos.z - 15.0f * cosf(model.rotDest.y);
	g_camera.posRDest.y = model.pos.y;

	// 目的の視点
	g_camera.posVDest.x = model.pos.x - sinf(g_camera.rot.x) * g_camera.fLength;
	g_camera.posVDest.z = model.pos.z - cosf(g_camera.rot.z) * g_camera.fLength;
	g_camera.posVDest.y = model.pos.y + 100.0f;

	// 注視点の位置更新
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.1f;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.1f;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.1f;

	// 視点の位置更新
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.1f;

	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_camera.moveZVR.x = sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.moveZVR.z = cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_camera.moveZVR.x = sinf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//	g_camera.moveZVR.z = cosf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveZVR.x = 0.0f;
	//	g_camera.moveZVR.z = 0.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_camera.moveXVR.x = cosf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//	g_camera.moveXVR.z = sinf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_camera.moveXVR.x = cosf(-g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.moveXVR.z = sinf(-g_camera.rot.y) * CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveXVR.x = 0.0f;
	//	g_camera.moveXVR.z = 0.0f;
	//}

	//// 注視点の移動(左右)
	//if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}
	//else if(GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}

	//// 注視点の移動(上下)
	//if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	//{
	//	g_camera.moveR.y = CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	//{
	//	g_camera.moveR.y = -CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveR.y = 0.0f;
	//}

	//// 視点の移動(左右)
	//if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}
	//else if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}

	//// 視点の移動(上下)
	//if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true)
	//{
	//	g_camera.moveV.y = CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true)
	//{
	//	g_camera.moveV.y = -CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveV.y = 0.0f;
	//}

	//if (g_camera.rot.y < -D3DX_PI)
	//{
	//	g_camera.rot.y += D3DX_PI * 2;
	//}
	//else if (g_camera.rot.y > D3DX_PI)
	//{
	//	g_camera.rot.y -= D3DX_PI * 2;
	//}

	//// 移動量の加算
	//g_camera.posV += g_camera.moveV;
	//g_camera.posR += g_camera.moveR;
	//g_camera.posV += g_camera.moveXVR;
	//g_camera.posR += g_camera.moveXVR;
	//g_camera.posV += g_camera.moveZVR;
	//g_camera.posR += g_camera.moveZVR;
}

//==============================================================================
// カメラの設定処理
//==============================================================================
void SetCamera(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjection,
		D3DXToRadian(45.0f),							// 画角の設定
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// 画面比率の設定
		10.0f,											// 手前限界の描画距離
		1000.0f);										// 奥限界の描画距離

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

// カメラの取得
Camera GetCamera(void)
{
	return g_camera;
}