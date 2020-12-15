//==============================================================================
//
// 3Dモデルの描画〔model.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "math.h"

// マクロ定義
#define MODEL_MOVE	(1.0f)
#define MODEL_TURN	(0.1f)

//==============================================================================
// グローバル変数
//==============================================================================
LPD3DXMESH g_pMeshModel = NULL;			// メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;	// マテリアル(材質情報)へのポインタ
DWORD g_nNumMatModel = 0;				// マテリアルの数
Model model;
//D3DXVECTOR3 g_posModel;				// 位置
//D3DXVECTOR3 g_rotModel;				// 向き
//D3DXMATRIX g_mtxWorldModel;			// ワールドマトリックス
//D3DXVECTOR3 g_moveModelX;				// X軸の移動量
//D3DXVECTOR3 g_moveModelZ;				// Z軸の移動量
int g_nIdx;

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT InitModel(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data/MODEL/01_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	// 変数の初期化
	model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 影の設定
	model.nIdx = SetShadow(D3DXVECTOR3(model.pos.x,0.0f,model.pos.z), 10.0f, 10.0f);

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void UninitModel(void)
{
	// メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	// マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void UpdateModel(void)
{
	// カメラの取得
	Camera camera = GetCamera();
	double dSqrt = sqrt(2);		// 2の平方根

	// 位置のリセット
	if (GetKeyboardTrigger(KEYINFO_OK) == true)
	{
		model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		model.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 弾の発射
	if (GetKeyboardPress(KEYINFO_SHOT) == true)
	{
		SetBullet(
			D3DXVECTOR3(model.pos.x, model.pos.y + 7.0f, model.pos.z),
			D3DXVECTOR3(sinf(D3DX_PI - model.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - model.rot.y) * 5.0f),
			100);
	}

	// 移動量の加算
	model.pos += model.move;

	// 影の追従
	SetPositionShadow(model.nIdx,D3DXVECTOR3(model.pos.x,0.0f,model.pos.z));

	// モデルの移動
	if (GetKeyboardPress(KEYINFO_BACK_MODEL) == true)
	{
		if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
		{// 左上方向
			model.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * MODEL_MOVE;
			model.move.z += sinf(camera.rot.y + D3DX_PI / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
			//model.rotDest.y += (camera.rot.y + (D3DX_PI * 3 / 4) - model.rot.y) * MODEL_TURN;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
		{// 右上方向
			model.move.x += cosf(camera.rot.y - D3DX_PI / 4) * MODEL_MOVE;
			model.move.z -= sinf(camera.rot.y - D3DX_PI / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y - (D3DX_PI * 3 / 4);
			//model.rotDest.y += (camera.rot.y - (D3DX_PI * 3 / 4) - model.rot.y) * MODEL_TURN;
		}
		else
		{// 上方向
			model.move.x += sinf(camera.rot.y) * MODEL_MOVE;
			model.move.z += cosf(camera.rot.y) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + D3DX_PI;
			//if (model.rot.y <= D3DX_PI && model.rot.y >= 0.0f && model.rot.y != D3DX_PI &&model.rot.y != -D3DX_PI)
			//{
			//	model.rotDest.y += (camera.rot.y + D3DX_PI) * MODEL_TURN;
			//}
			//if (model.rot.y >= -D3DX_PI && model.rot.y < 0.0f && model.rot.y != D3DX_PI &&model.rot.y != -D3DX_PI)
			//{
			//	model.rotDest.y -= (camera.rot.y + D3DX_PI) * MODEL_TURN;
			//}
		}
	}
	else if (GetKeyboardPress(KEYINFO_FORE_MODEL) == true)
	{
		if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
		{// 左下方向
			model.move.x += cosf(D3DX_PI + camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.move.z -= sinf(D3DX_PI + camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + D3DX_PI / 4;
			//model.rotDest.y += (camera.rot.y + D3DX_PI / 4 - model.rot.y) * MODEL_TURN;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
		{// 右下方向
			model.move.x -= cosf(D3DX_PI - camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.move.z += sinf(D3DX_PI - camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + D3DX_PI / -4;
			//model.rotDest.y += (camera.rot.y + D3DX_PI / -4 - model.rot.y) * MODEL_TURN;
		}
		else
		{// 下方向
			model.move.x += sinf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
			model.move.z += cosf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y;
			//model.rotDest.y += (camera.rot.y - model.rot.y) * 0.1f;
		}
		//model.moveZ.x = sinf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//model.moveZ.z = cosf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//model.rot.y = camera.rot.y;
		//if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
		//{
		//	model.moveX.x = cosf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//	model.moveX.z = sinf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//	model.rot.y = camera.rot.y + D3DX_PI / 4;
		//	//model.moveX.x /= dSqrt;
		//	//model.moveX.z /= dSqrt;
		//	//model.moveZ.x /= dSqrt;
		//	//model.moveZ.z /= dSqrt;
		//}
		//else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
		//{
		//	model.moveX.x = cosf(-camera.rot.y) * MODEL_MOVE;
		//	model.moveX.z = sinf(-camera.rot.y) * MODEL_MOVE;
		//	model.rot.y = camera.rot.y + D3DX_PI / -4;
		//	//model.moveX.x /= dSqrt;
		//	//model.moveX.z /= dSqrt;
		//	//model.moveZ.x /= dSqrt;
		//	//model.moveZ.z /= dSqrt;
		//}
	}
	else if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
	{// 左方向
		model.move.x -= cosf(camera.rot.y) * MODEL_MOVE;
		model.move.z += sinf(camera.rot.y) * MODEL_MOVE;
		model.rotDest.y = camera.rot.y + (D3DX_PI / 2);
		//model.rotDest.y += (camera.rot.y + (D3DX_PI / 2) - model.rot.y) * MODEL_TURN;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
	{// 右方向
		model.move.x += cosf(camera.rot.y) * MODEL_MOVE;
		model.move.z -= sinf(camera.rot.y) * MODEL_MOVE;
		model.rotDest.y = camera.rot.y + (D3DX_PI / -2);
		//if (model.rot.y < D3DX_PI && model.rot.y > D3DX_PI / 2)
		//{
		//	model.rotDest.y -= (camera.rot.y + (D3DX_PI / -2) - model.rot.y) * MODEL_TURN;

		//}
		//else
		//{
		//	model.rotDest.y += (camera.rot.y + (D3DX_PI / -2) - model.rot.y) * MODEL_TURN;
		//}
		
	}

	// モデルの上昇・下降
	if (GetKeyboardPress(KEYINFO_UP_MODEL) == true)
	{
		model.move.y = 2;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_MODEL) == true)
	{
		model.move.y = -2;
	}
	else
	{
		model.move.y = 0;
	}

	// モデルの旋回
	if (GetKeyboardPress(KEYINFO_TURN_LEFT_MODEL) == true)
	{
		model.rotDest.y += D3DX_PI / 18;
	}
	if (GetKeyboardPress(KEYINFO_TURN_RIGHT_MODEL) == true)
	{
		model.rotDest.y -= D3DX_PI / 18;
	}

	// 目的の回転角の上限
	if (model.rotDest.y - model.rot.y < -D3DX_PI)
	{
		model.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (model.rotDest.y - model.rot.y > D3DX_PI)
	{
		model.rotDest.y -= D3DX_PI * 2.0f;
	}

	// 向きの更新
	model.rot.y += (model.rotDest.y - model.rot.y) * 0.1f;

	// 現在の回転角の上限
	if (model.rot.y < -D3DX_PI)
	{
		model.rot.y += D3DX_PI * 2.0f;
	}
	else if (model.rot.y > D3DX_PI)
	{
		model.rot.y -= D3DX_PI * 2.0f;
	}

	// 加速後の減速処理
	model.move.x += (0.0f - model.move.x) * SPEEDDOWN;
	model.move.z += (0.0f - model.move.z) * SPEEDDOWN;
}

//==============================================================================
// 描画処理
//==============================================================================
void DrawModel(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&model.mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, model.rot.y, model.rot.x, model.rot.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, model.pos.x, model.pos.y, model.pos.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &model.mtxWorld);

	//// ワールドマトリックスの初期化
	//D3DXMatrixIdentity(&g_mtxWorldModel);

	//// 向きの反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//// 位置を反映
	//D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//// ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, NULL);

		// モデル(パーツ)の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

// モデルの取得
Model *GetModel(void)
{
	return &model;
}