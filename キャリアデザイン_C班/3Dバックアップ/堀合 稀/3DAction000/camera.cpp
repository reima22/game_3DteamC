//==============================================================================
//
// カメラの設定〔camera.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "camera.h"
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
	// 構造体の初期化
	g_camera.posV = D3DXVECTOR3(0.0f, CAMERA_POSV_Y, -CAMERA_POSV_Z);	// 視点位置
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 注視点位置
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// 上方向ベクトル
	g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 視点の移動量
	g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 注視点の移動量
	g_camera.moveXVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 視点・注視点両方同時のX軸移動量
	g_camera.moveZVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 視点・注視点両方同時のZ軸移動量

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// カメラの角度

	g_camera.fLength = sqrtf((g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y) + (g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));

	if (g_camera.fLength < 0.0f)
	{
		g_camera.fLength *= -1;
	}
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

	// リセット
	if (GetKeyboardTrigger(KEYINFO_SPACE) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, CAMERA_POSV_Y, -CAMERA_POSV_Z);	// 視点位置
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 注視点位置
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// 上方向ベクトル
		g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 視点の移動量
		g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// 注視点の移動量
		g_camera.moveXVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 視点・注視点両方同時のX軸移動量
		g_camera.moveZVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// 視点・注視点両方同時のZ軸移動量
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// カメラの角度
	}

	// 視点・注視点の移動
	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		g_camera.moveZVR.x = sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.moveZVR.z = cosf(g_camera.rot.y) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		g_camera.moveZVR.x = sinf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
		g_camera.moveZVR.z = cosf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	}
	else
	{
		g_camera.moveZVR.x = 0.0f;
		g_camera.moveZVR.z = 0.0f;
	}

	if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{
		g_camera.moveXVR.x = cosf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
		g_camera.moveXVR.z = sinf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{
		g_camera.moveXVR.x = cosf(-g_camera.rot.y) * CAMERA_MOVE;
		g_camera.moveXVR.z = sinf(-g_camera.rot.y) * CAMERA_MOVE;
	}
	else
	{
		g_camera.moveXVR.x = 0.0f;
		g_camera.moveXVR.z = 0.0f;
	}


	// 注視点の移動(左右)
	if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	{
		g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	}
	else if(GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	{
		g_camera.rot.y += D3DX_PI / CAMERA_TURN;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	}

	// 注視点の移動(上下)
	if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	{
		g_camera.moveR.y = CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	{
		g_camera.moveR.y = -CAMERA_MOVE;
	}
	else
	{
		g_camera.moveR.y = 0.0f;
	}

	// 視点の移動(左右)
	if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true)
	{
		g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true)
	{
		g_camera.rot.y += D3DX_PI / CAMERA_TURN;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	}

	// 視点の移動(上下)
	if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true)
	{
		g_camera.moveV.y = CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true)
	{
		g_camera.moveV.y = -CAMERA_MOVE;
	}
	else
	{
		g_camera.moveV.y = 0.0f;
	}

	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}
	else if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}

	// 移動量の加算
	g_camera.posV += g_camera.moveV;
	g_camera.posR += g_camera.moveR;
	g_camera.posV += g_camera.moveXVR;
	g_camera.posR += g_camera.moveXVR;
	g_camera.posV += g_camera.moveZVR;
	g_camera.posR += g_camera.moveZVR;
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