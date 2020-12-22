//-----------------------------------------------------------------------------
//
// モデル描画の処理
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "model.h"
#include "input.h"
#include "camera.h"
#include "Bullet.h"
#include "shadow.h"

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------
#define MOVE_MODEL_SPEED (1.0f)
#define MODEL_ROT_SPEED (0.2f)
#define MODEL_ROT_SPEED2 (0.5f)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
//LPD3DXMESH g_pMeshModel = NULL;			//メッシュ（頂点情報）へのポインタ
//LPD3DXBUFFER g_pBuffMatModel = NULL;	//マテリアル（材質情報）へのポインタ
//DWORD g_nNumMatModel = 0;				//マテリアルの数
//Model g_Model;							//モデル情報
//D3DXMATRIX g_mtxWorldModel;				//ワールドマトリックス
//D3DXVECTOR3 g_vtxMinModel, g_vtxMaxModel; //モデルの最小値 最大値
//LPDIRECT3DTEXTURE9 g_aTextureModel[1];	//テクスチャ数
//int nCntBullet;
//bool g_Key;
//
////-----------------------------------------------------------------------------
////初期化処理
////-----------------------------------------------------------------------------
//
////ローカル変数
//HRESULT InitModel(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	D3DXLoadMeshFromX("data/MODEL/car000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_nNumMatModel, &g_pMeshModel);
//
//	D3DXMATERIAL *pMat;	//マテリアルへのポインタ
//	int nNumVtx;		//頂点数
//	DWORD sizeFVF;		//頂点フォーマットのサイズ
//	BYTE *pVtxBuff;		//頂点バッファへのポインタ
//
//	g_vtxMinModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	g_vtxMaxModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	nNumVtx = g_pMeshModel->GetNumVertices();
//
//	//頂点フォーマットのサイズを取得
//	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());
//
//	//マテリアル情報に対するポインタ取得
//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//
//	//頂点バッファをロック
//	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
//
//	for (int nCntMat = 0; nCntMat < g_nNumMatModel; nCntMat++)
//	{
//		if (pMat[nCntMat].pTextureFilename != NULL)
//		{
//			//ファイル名を使用してテクスチャを読み込む
//			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_aTextureModel[0]);
//		}
//	}
//	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
//	{
//		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入
//
//		//頂点の最小値　最大値を抜き出す
//		if (g_vtxMinModel.x > vtx.x)
//		{
//			g_vtxMinModel.x = vtx.x;
//		}
//		if (g_vtxMaxModel.x < vtx.x)
//		{
//			g_vtxMaxModel.x = vtx.x;
//		}
//
//		if (g_vtxMinModel.y > vtx.y)
//		{
//			g_vtxMinModel.y = vtx.y;
//		}
//		if (g_vtxMaxModel.y < vtx.y)
//		{
//			g_vtxMaxModel.y = vtx.y;
//		}
//
//		if (g_vtxMinModel.z > vtx.z)
//		{
//			g_vtxMinModel.z = vtx.z;
//		}
//		if (g_vtxMaxModel.z < vtx.z)
//		{
//			g_vtxMaxModel.z = vtx.z;
//		}
//
//		pVtxBuff += sizeFVF;	//頂点フォーマットのサイズ分ポインタサイズを進める
//	}
//
//	//頂点バッファをアンロック
//	g_pMeshModel->UnlockVertexBuffer();
//
//	//位置初期化
//	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	//向き初期化
//	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//	nCntBullet = 0;
//
//	g_Key = false;
//
//	g_Model.nIdx = SetShadow(D3DXVECTOR3(g_Model.pos.x, 0.0f, g_Model.pos.z), 10.0f ,10.0f);
//
//	return S_OK;
//}
//
////-----------------------------------------------------------------------------
////終了処理
////-----------------------------------------------------------------------------
//void UninitModel(void)
//{
//
//	//メッシュの破棄
//	if (g_pMeshModel != NULL)
//	{
//		g_pMeshModel->Release();
//		g_pMeshModel = NULL;
//	}
//
//	//マテリアルの破棄
//	if (g_pBuffMatModel != NULL)
//	{
//		g_pBuffMatModel->Release();
//		g_pBuffMatModel = NULL;
//	}
//
//	//テクスチャの開放
//	if (g_aTextureModel[0] != NULL)
//	{
//		g_aTextureModel[0]->Release();
//		g_aTextureModel[0] = NULL;
//	}
//
//
//}
//
////-----------------------------------------------------------------------------
////更新処理
////-----------------------------------------------------------------------------
//void UpdateModel(void)
//{
//	
//	Camera *pCamera;
//	pCamera = GetCamera();
//
//	//モデル移動右
//	if (GetKeyboardPress(DIK_RIGHT) == true)
//	{
//		if (g_Key == false)
//		{
//			g_Model.rotDest.y = pCamera->rot.y - (D3DX_PI / 2);
//			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		}
//
//	}
//
//	//モデル移動左						 
//	if (GetKeyboardPress(DIK_LEFT) == true)
//	{
//		if (g_Key == false)
//		{
//			g_Model.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
//			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		}
//	}
//
//	//モデル移動奥						 
//	if (GetKeyboardPress(DIK_UP) == true)
//	{
//		//モデル移動右上
//		if (GetKeyboardPress(DIK_RIGHT) == true)
//		{
//			g_Model.rotDest.y = pCamera->rot.y - ((D3DX_PI / 4) + (D3DX_PI / 2));
//			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		}
//		//モデル移動左上						 
//		else if (GetKeyboardPress(DIK_LEFT) == true)
//		{
//			g_Model.rotDest.y = pCamera->rot.y + ((D3DX_PI / 4) + (D3DX_PI / 2));
//			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		}
//		else
//		{
//			g_Model.rotDest.y = pCamera->rot.y + D3DX_PI;
//		}
//		g_Model.move.x += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		g_Model.move.z += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//
//		g_Key = true;
//	}
//
//	//モデル移動手前						
//	if (GetKeyboardPress(DIK_DOWN) == true)
//	{
//	
//		//モデル移動右手前
//		if (GetKeyboardPress(DIK_RIGHT) == true)
//		{
//			g_Model.rotDest.y = pCamera->rot.y - (D3DX_PI / 4);
//			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		}
//		//モデル移動左手前					 
//		else if (GetKeyboardPress(DIK_LEFT) == true)
//		{
//			g_Model.rotDest.y = pCamera->rot.y + (D3DX_PI / 4);
//			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		}
//		else
//		{
//			g_Model.rotDest.y = pCamera->rot.y;
//		}
//		g_Model.move.x -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		g_Model.move.z -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
//		g_Key = true;
//	}
//
//	if (GetKeyboardRelease(DIK_DOWN) == true || GetKeyboardRelease(DIK_UP) == true)
//	{
//		g_Key = false;
//	}
//
//	//モデル右回転
//	if (GetKeyboardPress(DIK_RSHIFT) == true)
//	{
//		g_Model.rotDest.y += D3DX_PI / 18;
//	}
//
//	//モデル左回転
//	if (GetKeyboardPress(DIK_LSHIFT) == true)
//	{
//		g_Model.rotDest.y -= D3DX_PI / 18;
//	}
//	
//	/*if (GetKeyboardTrigger(DIK_SPACE) == true)
//	{
//		g_Model.move.y = 24;
//	}*/
//
//
//	if (GetKeyboardPress(DIK_K) == true)
//	{
//		nCntBullet++;
//		if ((nCntBullet % 1) == 0)
//		{
//			SetBullet(g_Model.pos, D3DXVECTOR3(-sinf(g_Model.rot.y), 0.0f, -cosf(g_Model.rot.y)), 100);
//		}
//	}
//
//	if (g_Model.rotDest.y - g_Model.rot.y > D3DX_PI)
//	{
//		g_Model.rotDest.y -= D3DX_PI * 2.0f;
//	}
//	if (g_Model.rotDest.y - g_Model.rot.y < -D3DX_PI)
//	{
//		g_Model.rotDest.y += D3DX_PI * 2.0f;
//	}
//
//	g_Model.pos.x += g_Model.move.x;
//	g_Model.pos.y += g_Model.move.y;
//	g_Model.pos.z += g_Model.move.z;
//	g_Model.move.x += (0 - g_Model.move.x) * 0.2f;
//	g_Model.move.z += (0 - g_Model.move.z) * 0.2f;
//
//	//g_Model.move.y -= 1.7f;
//
//	g_Model.rot.y += (g_Model.rotDest.y - g_Model.rot.y) * 0.1f;
//
//	//if (g_Model.pos.y <= 0)
//	//{
//	//	g_Model.move.y = 0;
//	//	g_Model.pos.y = 0;
//	//}
//
//	if (g_Model.rot.y > D3DX_PI)
//	{
//		g_Model.rot.y -= D3DX_PI * 2.0f;
//	}
//	if (g_Model.rot.y < -D3DX_PI)
//	{
//		g_Model.rot.y += D3DX_PI * 2.0f;
//	}
//
//	if (GetKeyboardTrigger(DIK_RETURN) == true)
//	{
//		//位置初期化
//		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//移動量初期化
//		g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//
//		//目的の向き
//		g_Model.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//
//	SetPositionShadow(g_Model.nIdx, D3DXVECTOR3(g_Model.pos.x,0.0f,g_Model.pos.z));
//}
//
////-----------------------------------------------------------------------------
////描画処理
////-----------------------------------------------------------------------------
//void DrawModel(void)
//{
//	//デバイスの取得
//	LPDIRECT3DDEVICE9 pDevice;		
//	pDevice = GetDevice();
//
//	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
//	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
//	D3DXMATERIAL *pMat;				//マテリアルへのポインタ
//
//	//ワールドマトリックスの初期化
//	D3DXMatrixIdentity(&g_mtxWorldModel);
//
//	//向き反映
//	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
//
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);
//
//	//位置を反映
//	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
//
//	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);
//
//	//ワールドマトリックスの設定
//	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);
//
//	//現在のマテリアル取得
//	pDevice->GetMaterial(&matDef);
//
//	//マテリアルへのポインタを取得
//	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
//
//	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
//	{
//		//マテリアル設定
//		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
//		
//		//テクスチャ設定
//		pDevice->SetTexture(0, g_aTextureModel[0]);
//
//		//モデルの(パーツ)の描画
//		g_pMeshModel->DrawSubset(nCntMat);
//	}
//	
//	//保存したマテリアルを戻す
//	pDevice->SetMaterial(&matDef);
//
//}
//
////モデルの情報取得
//Model *GetModel(void)
//{
//	return &g_Model;
//}