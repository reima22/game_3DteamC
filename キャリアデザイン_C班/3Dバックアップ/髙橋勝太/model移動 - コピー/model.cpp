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
#include "bullet.h"
#include "effect.h"

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
LPDIRECT3DTEXTURE9 g_pTextureModel[5] = {};			//テクスチャ
DWORD  g_nNumMatModel = 0;							//マテリアルの数
MODEL g_Model;
D3DXMATRIX g_mtxWorldModel;							//ワールドマトリックス
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

	g_Model.MinModel = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	g_Model.MaxModel = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	//model読み込み
	//D3DXLoadMeshFromX("data/MODEL/airplane000.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMetModel,NULL,&g_nNumMatModel,&g_pMeshModel);
	//D3DXLoadMeshFromX("data/model/剣.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetModel, NULL, &g_nNumMatModel, &g_pMeshModel);
	D3DXLoadMeshFromX("data/model/標識.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	int nNumVtx;			//頂点数
	DWORD sizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;			//頂点バッファへのポインタ 

	D3DXMATERIAL *pMat;		//マテリアルへのポインタ

	//頂点数を取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)g_pBuffMetModel->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャ読み込み
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/50.png", &g_pTextureModel[0]);
		}
	}

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//頂点バッファをロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (g_Model.MinModel.x > vtx.x)
		{	
			g_Model.MinModel.x = vtx.x;
		}	
			
		if (g_Model.MaxModel.x < vtx.x)
		{	
			g_Model.MaxModel.x = vtx.x;
		}

		if (g_Model.MinModel.y > vtx.y)
		{	
			g_Model.MinModel.y = vtx.y;
		}	

		if (g_Model.MaxModel.y < vtx.y)
		{	
			g_Model.MaxModel.y = vtx.y;
		}	

		if (g_Model.MinModel.z > vtx.z)
		{	
			g_Model.MinModel.z = vtx.z;
		}	

		if (g_Model.MaxModel.z < vtx.z)
		{	
			g_Model.MaxModel.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	//頂点フォーマットのサイズ分を進める
	}
	//頂点バッファをアンロック
	g_pMeshModel->UnlockVertexBuffer();

	//位置
	g_Model.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);

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
	//if (GetKeyboardPress(DIK_LEFT) == true)
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_Model.move.x += 0.5f*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5f*sinf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI * 2 / 4);

		//上移動
		//if (GetKeyboardPress(DIK_UP) == true)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_Model.move.x += 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z -= 0.5f*cosf(D3DX_PI + pCamera->Camera);

			
			g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI * 3 / 4);
		}

		//下移動
		//if (GetKeyboardPress(DIK_DOWN) == true)
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_Model.move.x -= 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z += 0.5f*cosf(D3DX_PI + pCamera->Camera);

			g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI * 1 / 4);
		}
	}

	//右移動
	//else if (GetKeyboardPress(DIK_RIGHT) == true)
	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_Model.move.x -= 0.5f*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5f*sinf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera - (D3DX_PI * 2 / 4);

		//上移動
		//if (GetKeyboardPress(DIK_UP) == true)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_Model.move.x += 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z -= 0.5f*cosf(D3DX_PI + pCamera->Camera);

			g_Model.rotDest.y = -pCamera->Camera - (D3DX_PI * 3 / 4);
		}

		//下移動
		//if (GetKeyboardPress(DIK_DOWN) == true)
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_Model.move.x -= 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z += 0.5f*cosf(D3DX_PI + pCamera->Camera);

			g_Model.rotDest.y = -pCamera->Camera - (D3DX_PI * 1 / 4);
		}
	}

	//上移動
	//else if (GetKeyboardPress(DIK_UP) == true)
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_Model.move.x += 0.5f*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5f*cosf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI);
	}

	//下移動
	//else if (GetKeyboardPress(DIK_DOWN) == true)
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_Model.move.x -= 0.5f*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5f*cosf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera;
	}

	//モデル左回転
	if (GetKeyboardPress(DIK_M) == true)
	{
		g_modelrot -= 0.1f;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}

	//モデル右回転
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_modelrot += 0.1f;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}
	
	int nEffct;
	nEffct = rand() % 4;

	if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true|| GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true)
	{
		if (nEffct == 1)
		{
			SetEffect(g_Model.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 1);
		}
	}

	//弾の発射
	if (GetKeyboardTrigger(DIK_B) == true)
	{
		SetBullet(D3DXVECTOR3(g_Model.pos.x, g_Model.pos.y + 10, g_Model.pos.z), D3DXVECTOR3(sinf(g_Model.rot.y), 0.0f, cosf(g_Model.rot.y)), 5, 500);
		
	}

	//回転リセット
	if (g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rot.y += D3DX_PI * 2.0f;
	}

	if (g_Model.rot.y > D3DX_PI)
	{
		g_Model.rot.y -= D3DX_PI * 2.0f;
	}
	
	// 目的の回転角の上限
	if (g_Model.rotDest.y - g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_Model.rotDest.y - g_Model.rot.y > D3DX_PI)
	{
		g_Model.rotDest.y -= D3DX_PI * 2.0f;
	}

	// 向きの更新
	g_Model.rot.y += (g_Model.rotDest.y - g_Model.rot.y) * 0.1f;

	

	//移動量の減衰
	g_Model.move.x -= (0 + g_Model.move.x) * 0.2f;
	g_Model.move.y -= (0 + g_Model.move.y) * 0.2f;
	g_Model.move.z -= (0 + g_Model.move.z) * 0.2f;

	//移動量の減衰
	g_Model.rotmove.x -= (0 + g_Model.rotmove.x) * 0.2f;
	g_Model.rotmove.y -= (0 + g_Model.rotmove.y) * 0.2f;
	g_Model.rotmove.z -= (0 + g_Model.rotmove.z) * 0.2f;

	//位置更新
	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.y += g_Model.move.y;
	g_Model.pos.z += g_Model.move.z;

	//位置更新
	g_Model.rot.x += g_Model.rotmove.x;
	g_Model.rot.y += g_Model.rotmove.y;
	g_Model.rot.z += g_Model.rotmove.z;

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
		pDevice->SetTexture(0, g_pTextureModel[nCntMat]);

		//モデルパーツの描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//---------------------------------------------
//データの受け渡し
//---------------------------------------------
MODEL *GetModel(void)
{
	return &g_Model;
}