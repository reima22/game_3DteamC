//================================================
//
//モデル処理[model.h]
// Author; miura yuudai
//
//================================================

#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"

//=====================
//グローバル変数
//=====================
//メッシュ（頂点情報）へのポインタ
LPD3DXMESH g_pMeshModel = NULL;

//マテリアル（材質情報）へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;

DWORD g_nNumMatModel = 0;//マテリアルの数
MODEL g_PosModel;//位置
D3DXMATRIX g_mtxWolrdModel;//ワールドマトリックス
float g_model;

//====================
//モデルの初期化処理
//====================
void InitModel(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/car002.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	//変数初期化
	g_PosModel.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosModel.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosModel.rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model = 0.0f;
}
//=======================
//モデルの終了処理
//=======================
void UninitModel(void)
{
	//頂点の開放
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//材質の開放
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}
//=======================
//モデルの更新処理
//=======================
void UpdateModel(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	//SetShadow(g_PosModel.Pos, 20, 20);

	if (GetKeyboardPress(DIK_RIGHT) == true)//プレイヤーの回転
	{
		g_PosModel.rot.y = -1.57f;
		g_PosModel.move.x -= cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z -= sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)//プレイヤーの回転
	{
		g_PosModel.rot.y = 1.57f;
		g_PosModel.move.x += cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z += sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)//プレイヤーの回転
	{
		g_PosModel.move.x -= sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z += cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}
	if (GetKeyboardPress(DIK_UP) == true)//プレイヤーの回転
	{
		g_PosModel.move.x += sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z -= cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}

	if (GetKeyboardPress(DIK_K) == true)//プレイヤーの回転
	{
		g_model += 0.1f;
		g_PosModel.rot.y = g_model;
	}

	//回転角度リセット
	if (g_PosModel.rot.y >= D3DX_PI)
	{
		g_PosModel.rot.y = -D3DX_PI;
	}

	/*else if (g_PosModel.rot.y <= -D3DX_PI)
	{
		g_PosModel.rot.y = D3DX_PI;
	}*/
	
	//位置更新
	g_PosModel.Pos.x += g_PosModel.move.x;
	g_PosModel.Pos.z += g_PosModel.move.z;
	g_PosModel.rot.y += g_PosModel.rotmove.y;

	// 移動量の減衰
	g_PosModel.move.x += (0.0f - g_PosModel.move.x) *0.3f;
	g_PosModel.move.z += (0.0f - g_PosModel.move.z) *0.3f;
	g_PosModel.rotmove.y  += (0.0f - g_PosModel.rotmove.y) *0.3f;
}
//=======================
//モデルの描画処理
//=======================
void DrawModel(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//マテリアルへのポインタ
	D3DXMATERIAL *pMat;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWolrdModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PosModel.rot.y, g_PosModel.rot.x, g_PosModel.rot.z);

	D3DXMatrixMultiply(&g_mtxWolrdModel, &g_mtxWolrdModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_PosModel.Pos.x, g_PosModel.Pos.y, g_PosModel.Pos.z);

	D3DXMatrixMultiply(&g_mtxWolrdModel, &g_mtxWolrdModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWolrdModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
MODEL *GetModel(void)
{
	return &g_PosModel;
}
