//-----------------------------------------------------------------
//
// プレイヤーの処理 (model.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "model.h"
#include"camera.h"
#include "shadow.h"
#include "input.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define PLAYER_X		(50)									// 中心から端までまでの長さ(x)
#define PLAYER_Y		(50)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;	//頂点情報
LPD3DXBUFFER g_pBuffMetModel = NULL;
DWORD  g_nNumMatModel = 0;						//マテリアルの数
MODEL g_Model;
D3DXMATRIX g_mtxWorldModel;						//ワールドマトリックス
float g_modelrot;

//-----------------------------------------------------------------------------
// ポリゴンの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitModel(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//model読み込み
	D3DXLoadMeshFromX("data/MODEL/airplane000.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMetModel,NULL,&g_nNumMatModel,&g_pMeshModel);
	//D3DXLoadMeshFromX("data/MODEL/剣.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	//位置
	g_Model.pos = D3DXVECTOR3(0.0f, 15.0f, -30.0f);

	//影の初期位置
	SetShadow(D3DXVECTOR3(g_Model.pos.x, 0.0f, g_Model.pos.z));

	//向き
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//-----------------------------------------------------------------------------
// ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitModel(void)
{
	//マテリアルの開放
	if (g_pBuffMetModel != NULL)
	{
		g_pBuffMetModel->Release();
		g_pBuffMetModel = NULL;
	}

	//メッシュの開放
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
}

//-----------------------------------------------------------------------------
// ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdateModel(void)
{
	CAMERA  *pCamera;
	pCamera = GetCamera();

	//モデルの移動
	//左移動
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Model.move.x += 0.5*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5*sinf(D3DX_PI + pCamera->Camera);
	}
	//右移動
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Model.move.x -= 0.5*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5*sinf(D3DX_PI + pCamera->Camera);
	}

	//上移動
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Model.move.x += 0.5*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5*cosf(D3DX_PI + pCamera->Camera);
	}

	//下移動
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Model.move.x -= 0.5*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5*cosf(D3DX_PI + pCamera->Camera);
	}

	//モデル左回転
	if (GetKeyboardPress(DIK_M) == true)
	{
		g_modelrot -= 0.1;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}

	//モデル右回転
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_modelrot += 0.1;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}

	//位置更新
	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.y += g_Model.move.y;
	g_Model.pos.z += g_Model.move.z;
	
	//移動量の減衰
	g_Model.move.x -= (0 + g_Model.move.x) * 0.2f;
	g_Model.move.y -= (0 + g_Model.move.y) * 0.2f;
	g_Model.move.z -= (0 + g_Model.move.z) * 0.2f;

	//影の位置更新
	SetPositionShadow(0, D3DXVECTOR3(g_Model.pos.x, 0.0f, g_Model.pos.z));
}

//-----------------------------------------------------------------------------
// ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawModel(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きの反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置の反転
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)g_pBuffMetModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

MODEL *GetModel(void)
{
	return &g_Model;
}