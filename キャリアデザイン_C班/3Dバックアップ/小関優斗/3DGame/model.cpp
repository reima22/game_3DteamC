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

//-----------------------------------------------------------------------------
//マクロ定義
//-----------------------------------------------------------------------------
#define MOVE_MODEL_SPEED (1.0f)
#define MODEL_ROT_SPEED (0.2f)
#define MODEL_ROT_SPEED2 (0.5f)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;			//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;	//マテリアル（材質情報）へのポインタ
DWORD g_NumMatModel = 0;				//マテリアルの数
Model g_Model;							//モデル情報
D3DXMATRIX g_mtxWorldModel;				//ワールドマトリックス
int nCntBullet;
bool g_Key;

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------

//ローカル変数
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXLoadMeshFromX("data/MODEL/car001.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_NumMatModel, &g_pMeshModel);

	//位置初期化
	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向き初期化
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	nCntBullet = 0;

	g_Key = false;
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitModel(void)
{

	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

	////テクスチャの開放
	//if (g_pTexturePolygon != NULL)
	//{
	//	g_pTexturePolygon->Release();
	//	g_pTexturePolygon = NULL;
	//}


}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void UpdateModel(void)
{
	
	Camera *pCamera;
	pCamera = GetCamera();

	//モデル移動右
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		if (g_Key == false)
		{
			g_Model.rotDest.y = pCamera->rot.y - (D3DX_PI / 2);
			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}

	}

	//モデル移動左						 
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		if (g_Key == false)
		{
			g_Model.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
	}

	//モデル移動奥						 
	if (GetKeyboardPress(DIK_UP) == true)
	{
		//モデル移動右上
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y - ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//モデル移動左上						 
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y + ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Model.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
		g_Model.move.x += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.move.z += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;

		g_Key = true;
	}

	//モデル移動手前						
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
	
		//モデル移動右手前
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y - (D3DX_PI / 4);
			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//モデル移動左手前					 
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y + (D3DX_PI / 4);
			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Model.rotDest.y = pCamera->rot.y;
		}
		g_Model.move.x -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.move.z -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Key = true;
	}

	if (GetKeyboardRelease(DIK_DOWN) == true || GetKeyboardRelease(DIK_UP) == true)
	{
		g_Key = false;
	}

	//モデル右回転
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_Model.rotDest.y += D3DX_PI / 18;
	}

	//モデル左回転
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Model.rotDest.y -= D3DX_PI / 18;
	}
	

	if (GetKeyboardPress(DIK_K) == true)
	{
		nCntBullet++;
		if ((nCntBullet % 1) == 0)
		{
			SetBullet(g_Model.pos, D3DXVECTOR3(-sinf(g_Model.rot.y), 0.0f, -cosf(g_Model.rot.y)), 100);
		}
	}

	if (g_Model.rotDest.y - g_Model.rot.y > D3DX_PI)
	{
		g_Model.rotDest.y -= D3DX_PI * 2.0f;
	}
	if (g_Model.rotDest.y - g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rotDest.y += D3DX_PI * 2.0f;
	}

	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.z += g_Model.move.z;
	g_Model.move.x += (0 - g_Model.move.x) * 0.2f;
	g_Model.move.z += (0 - g_Model.move.z) * 0.2f;

	g_Model.rot.y += (g_Model.rotDest.y - g_Model.rot.y) * 0.1f;

	if (g_Model.rot.y > D3DX_PI)
	{
		g_Model.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rot.y += D3DX_PI * 2.0f;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//位置初期化
		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//移動量初期化
		g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//目的の向き
		g_Model.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
}

//-----------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------
void DrawModel(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;		
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_NumMatModel; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		
		//テクスチャ設定
		pDevice->SetTexture(0, NULL);

		//モデルの(パーツ)の描画
		g_pMeshModel->DrawSubset(nCntMat);
	}
	
	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);

}

//モデルの情報取得
Model *GetModel(void)
{
	return &g_Model;
}