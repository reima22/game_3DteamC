//-----------------------------------------------------------------
//
// プレイヤーの処理 (model.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "object.h"
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
LPD3DXMESH g_pMeshObject = NULL;	//頂点情報
LPD3DXBUFFER g_pBuffMetObject = NULL;
DWORD  g_nNumMatObject = 0;						//マテリアルの数
OBJECT g_Object;
D3DXMATRIX g_mtxWorldObject;						//ワールドマトリックス
float g_objectrot;

//-----------------------------------------------------------------------------
// ポリゴンの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitObject(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//model読み込み
	//D3DXLoadMeshFromX("data/model/airplane000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetObject, NULL, &g_nNumMatObject, &g_pMeshObject);
	D3DXLoadMeshFromX("data/model/剣.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetObject, NULL, &g_nNumMatObject, &g_pMeshObject);

	//位置
	g_Object.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//影の初期位置
	//SetShadow(D3DXVECTOR3(g_Object.pos.x, 0.0f, g_Object.pos.z));
	//影の初期位置
	SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//向き
	g_Object.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//-----------------------------------------------------------------------------
// ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitObject(void)
{
	//マテリアルの開放
	if (g_pBuffMetObject != NULL)
	{
		g_pBuffMetObject->Release();
		g_pBuffMetObject = NULL;
	}

	//メッシュの開放
	if (g_pMeshObject != NULL)
	{
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}
}

//-----------------------------------------------------------------------------
// ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdateObject(void)
{
	SetPositionShadow(1,D3DXVECTOR3(g_Object.pos.x, 0.0f, g_Object.pos.z));
}

//-----------------------------------------------------------------------------
// ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawObject(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldObject);

	//向きの反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object.rot.y, g_Object.rot.x, g_Object.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxRot);

	//位置の反転
	D3DXMatrixTranslation(&mtxTrans, g_Object.pos.x, g_Object.pos.y, g_Object.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldObject);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)g_pBuffMetObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデルパーツの描画
		g_pMeshObject->DrawSubset(nCntMat);
	}

	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

OBJECT *GetObject(void)
{
	return &g_Object;
}