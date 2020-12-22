//-----------------------------------------------------------------------------
//
// モデル描画の処理
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "player.h"
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
Player g_Player;
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxPlayer; //モデルの最小値 最大値
LPDIRECT3DTEXTURE9 g_aTexturePlayer = NULL;	//テクスチャ数
int nCntBullet;
bool g_Key;

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------

//ローカル変数
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//ファイル読み込み
	D3DXLoadMeshFromX("data/MODEL/00_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/MODEL/01_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/MODEL/02_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/MODEL/03_armR2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/MODEL/04_handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/MODEL/05_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);
	D3DXLoadMeshFromX("data/MODEL/06_armL2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].nNumMat, &g_Player.aModel[6].pMesh);
	D3DXLoadMeshFromX("data/MODEL/07_handL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].nNumMat, &g_Player.aModel[7].pMesh);
	D3DXLoadMeshFromX("data/MODEL/08_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].nNumMat, &g_Player.aModel[8].pMesh);
	D3DXLoadMeshFromX("data/MODEL/09_shinR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].nNumMat, &g_Player.aModel[9].pMesh);
	D3DXLoadMeshFromX("data/MODEL/10_footR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].nNumMat, &g_Player.aModel[10].pMesh);
	D3DXLoadMeshFromX("data/MODEL/11_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].nNumMat, &g_Player.aModel[11].pMesh);
	D3DXLoadMeshFromX("data/MODEL/12_shinL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].nNumMat, &g_Player.aModel[12].pMesh);
	D3DXLoadMeshFromX("data/MODEL/13_footL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].nNumMat, &g_Player.aModel[13].pMesh);

	//g_Player.nNumModel = 13;

	D3DXMATERIAL *pMat;	//マテリアルへのポインタ
	int nNumVtx;		//頂点数
	DWORD sizeFVF;		//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	g_vtxMinPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMaxPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//マテリアル情報に対するポインタ取得
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{

		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//頂点バッファをロック
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntMat = 0; nCntMat < g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());

			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//ファイル名を使用してテクスチャを読み込む
				D3DXCreateTextureFromFile(pDevice, NULL, &g_aTexturePlayer);
			}
		}

		//頂点バッファをアンロック
		g_Player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

	//												//頂点の最小値　最大値を抜き出す
	//	if (g_vtxMinPlayer.x > vtx.x)
	//	{
	//		g_vtxMinPlayer.x = vtx.x;
	//	}
	//	if (g_vtxMaxPlayer.x < vtx.x)
	//	{
	//		g_vtxMaxPlayer.x = vtx.x;
	//	}

	//	if (g_vtxMinPlayer.y > vtx.y)
	//	{
	//		g_vtxMinPlayer.y = vtx.y;
	//	}
	//	if (g_vtxMaxPlayer.y < vtx.y)
	//	{
	//		g_vtxMaxPlayer.y = vtx.y;
	//	}

	//	if (g_vtxMinPlayer.z > vtx.z)
	//	{
	//		g_vtxMinPlayer.z = vtx.z;
	//	}
	//	if (g_vtxMaxPlayer.z < vtx.z)
	//	{
	//		g_vtxMaxPlayer.z = vtx.z;
	//	}

	//	pVtxBuff += sizeFVF;	//頂点フォーマットのサイズ分ポインタサイズを進める
	//}

	//親モデルのインデックス設定

	//体
	g_Player.aModel[0].nIdxModelParent = -1;					//親(なし)
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 16.0f, 0.0f);	//オフセット
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//頭
	g_Player.aModel[1].nIdxModelParent = 0;						//親(体)
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);	//オフセット
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き


	//右腕
	g_Player.aModel[2].nIdxModelParent = 0;						//親(体)
	g_Player.aModel[2].pos = D3DXVECTOR3(-7.0f, 10.0f, 0.0f);	//オフセット
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//右腕２
	g_Player.aModel[3].nIdxModelParent = 2;						//親(右腕)
	g_Player.aModel[3].pos = D3DXVECTOR3(-6.6f, 0.0f, 0.0f);	//オフセット
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//右手
	g_Player.aModel[4].nIdxModelParent = 3;						//親(右腕２)
	g_Player.aModel[4].pos = D3DXVECTOR3(-7.0f, 0.0f, 0.0f);	//オフセット
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//左腕
	g_Player.aModel[5].nIdxModelParent = 0;						//親(体)
	g_Player.aModel[5].pos = D3DXVECTOR3(7.0f, 10.0f, 0.0f);	//オフセット
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//左腕２
	g_Player.aModel[6].nIdxModelParent = 5;						//親(左腕)
	g_Player.aModel[6].pos = D3DXVECTOR3(6.6f, 0.0f, 0.0f);		//オフセット
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//左手
	g_Player.aModel[7].nIdxModelParent = 6;						//親(左腕２)
	g_Player.aModel[7].pos = D3DXVECTOR3(7.0f, 0.0f, 0.0f);		//オフセット
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//右腿
	g_Player.aModel[8].nIdxModelParent = 0;						//親(体)
	g_Player.aModel[8].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);	//オフセット
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き



	//右脛
	g_Player.aModel[9].nIdxModelParent = 8;						//親(右腿)
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//オフセット
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き

	//右足
	g_Player.aModel[10].nIdxModelParent = 9;					//親(右脛)
	g_Player.aModel[10].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//オフセット
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	//左腿
	g_Player.aModel[11].nIdxModelParent = 0;					//親(体)
	g_Player.aModel[11].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);	//オフセット
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	//左脛
	g_Player.aModel[12].nIdxModelParent = 11;					//親(右腿)
	g_Player.aModel[12].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//オフセット
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	//左足
	g_Player.aModel[13].nIdxModelParent = 12;					//親(右脛)
	g_Player.aModel[13].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//オフセット	
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き

	//位置初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向き初期化
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	nCntBullet = 0;

	g_Key = false;

	return S_OK;
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//メッシュの破棄
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
	//テクスチャの開放
	if (g_aTexturePlayer != NULL)
	{
		g_aTexturePlayer->Release();
		g_aTexturePlayer = NULL;
	}
}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{

	Camera *pCamera;
	pCamera = GetCamera();

	//モデル移動右
	if (GetKeyboardPress(DIK_D) == true)
	{
		if (g_Key == false)
		{
			g_Player.rotDest.y = pCamera->rot.y - (D3DX_PI / 2);
			g_Player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}

	}

	//モデル移動左						 
	if (GetKeyboardPress(DIK_A) == true)
	{
		if (g_Key == false)
		{
			g_Player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
			g_Player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
	}

	//モデル移動奥						 
	if (GetKeyboardPress(DIK_W) == true)
	{
		//モデル移動右上
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y - ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//モデル移動左上						 
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y + ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
		g_Player.move.x += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Player.move.z += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;

		g_Key = true;
	}

	//モデル移動手前						
	if (GetKeyboardPress(DIK_S) == true)
	{

		//モデル移動右手前
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y - (D3DX_PI / 4);
			g_Player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//モデル移動左手前					 
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y + (D3DX_PI / 4);
			g_Player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Player.rotDest.y = pCamera->rot.y;
		}
		g_Player.move.x -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Player.move.z -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Key = true;
	}

	if (GetKeyboardRelease(DIK_S) == true || GetKeyboardRelease(DIK_W) == true)
	{
		g_Key = false;
	}

	//モデル右回転
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_Player.rotDest.y += D3DX_PI / 18;
	}

	//モデル左回転
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Player.rotDest.y -= D3DX_PI / 18;
	}

	/*if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
	g_Model.move.y = 24;
	}*/

	//弾の発射
	if (GetKeyboardPress(DIK_K) == true)
	{
		nCntBullet++;
		if ((nCntBullet % 1) == 0)
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 20, g_Player.pos.z), D3DXVECTOR3(-sinf(g_Player.rot.y), 0.0f, -cosf(g_Player.rot.y)), 100);
		}
	}

	if (g_Player.rotDest.y - g_Player.rot.y > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.rotDest.y - g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;
	g_Player.move.x += (0 - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0 - g_Player.move.z) * 0.2f;

	//g_Model.move.y -= 1.7f;

	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	//if (g_Model.pos.y <= 0)
	//{
	//	g_Model.move.y = 0;
	//	g_Model.pos.y = 0;
	//}

	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//位置初期化
		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//移動量初期化
		g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//目的の向き
		g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	SetPositionShadow(-1, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));

	//モーションの処理
	if (g_Player.MotionType == MOTIONTYPE_NUTRAL)
	{
		g_Player.bLoopMotion = true;

		g_Player.aMotionInfo[0].aKeyInfo[0].Frame = 40;

		if ((g_Player.nCounterMotion % g_Player.aMotionInfo[0].aKeyInfo[0].Frame) == 0)
		{
			g_Player.nKey++;
		}
		if (g_Player.nKey == 0)
		{
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosX = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosZ = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotX = -0.03;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotZ = 0.0;
		}

		if (g_Player.nKey == 1)
		{
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosX = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosZ = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotX = -0.03;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotZ = 0.0;
		}



	}

}

//-----------------------------------------------------------------------------
//描画処理
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルへのポインタ

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel; //パーツ用計算用マトリックス
		D3DXMATRIX mtxParent;
		//各パーツのワールドマトリックス
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		//向き反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);

		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);

		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//各パーツの親マトリックスの設定
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;
		}

		//算出した各パーツのワールドマトリックスと親のマトリックスを設定
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);


		//マテリアルへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_aTexturePlayer);
		
			//モデルの(パーツ)の描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
	
}

Player *GetPlayer(void)
{
	return &g_Player;
}