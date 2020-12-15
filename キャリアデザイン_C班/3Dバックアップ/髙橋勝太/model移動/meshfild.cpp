//-----------------------------------------------------------------
//
// プレイヤーの処理 (player.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "meshfild.h"
#include"camera.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define MESHFILD_X		(2)		// 中心から端までまでの長さ(x)
#define MESHFILD_Y		(2)		// 中心から端までまでの長さ(y)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfild = NULL;	//頂点情報
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshFild = NULL;	//インデックスバッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfild = NULL;		//テクスチャ
D3DXVECTOR3 g_posMeshfild;							//位置
D3DXVECTOR3 g_rotMeshfild;							//向き
D3DXMATRIX g_mtxWorldMeshfild;						//ワールドマトリックス
MESHFILD g_Meshfild[MAX_MESHFILD];
int g_nMeshfildDate;

//-----------------------------------------------------------------------------
// ポリゴンの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitMeshfild(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureMeshfild);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/item_03.png", &g_pTextureMeshfild);

	//位置
	g_posMeshfild = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向き
	g_rotMeshfild = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//頂点バッファの生成
	//if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshfild, NULL)))
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESHFILD_X + 1) *(MESHFILD_Y + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshfild, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMeshfild->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
	{
		pVtx[nCntX].pos = D3DXVECTOR3(-50.0f + nCntX*50.0f, 0.0f, 50.0f);

		for (int nCntY = 0; nCntY < MESHFILD_Y; nCntY++)
		{
			//pVtx[nCntX + MESHFILD_X + 1].pos = D3DXVECTOR3(-50.0f + nCntX*50.0f, 0.0f, 0.0f - nCntY*50.0f);
			pVtx[nCntX + MESHFILD_X + 1 + (nCntY * 3)].pos = D3DXVECTOR3(-50.0f + nCntX*50.0f, 0.0f, 0.0f - nCntY*50.0f);
		}
	}

	////頂点座標の設定
	//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	//pVtx[2].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[4].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 50.0f);
	//pVtx[6].pos = D3DXVECTOR3(100.0f, 0.0f, 50.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[8].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[9].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[11].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[12].pos = D3DXVECTOR3(100.0f, 0.0f, -50.0f);
	//pVtx[13].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

	/*pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	pVtx[8].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);*/



	////頂点カラーの設定
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	for (int nCntMeshfild = 0; nCntMeshfild < (MESHFILD_X + 1) *(MESHFILD_Y + 1); nCntMeshfild++)
	{
		pVtx[nCntMeshfild].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}


	////頂点の情報の設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);

	for (int nCntMeshfild = 0; nCntMeshfild < (MESHFILD_X + 1) *(MESHFILD_Y + 1); nCntMeshfild++)
	{
		pVtx[nCntMeshfild].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	////頂点の情報の設定
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	////pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);

	////頂点の情報の設定
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);

	//ベクトルの法線
	/*pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);*/

	for (int nCntMeshfild = 0; nCntMeshfild < (MESHFILD_X + 1) *(MESHFILD_Y + 1); nCntMeshfild++)
	{
		pVtx[nCntMeshfild].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshfild->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pldxBuffMeshFild, NULL);

	WORD *pldx;			//インデックス情報への番号

	//インデックスバッファをロック
	g_pldxBuffMeshFild->Lock(0, 0, (void**)&pldx, 0);

	////番号データ
	//pldx[0] = 3;
	//pldx[1] = 0;
	//pldx[2] = 4;
	//pldx[3] = 1;
	//pldx[4] = 5;
	//pldx[5] = 2;
	//pldx[6] = 2;
	//pldx[7] = 6;
	//pldx[8] = 6;
	//pldx[9] = 3;
	//pldx[10] = 7;
	//pldx[11] = 4;
	//pldx[12] = 8;
	//pldx[13] = 5;

	/*for (int nCntY = 0; nCntY < MESHFILD_Y + 1; nCntY++)
	{
		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			pldx[0 + nCntX * 2] = 0 + nCntX + MESHFILD_X + 1;
		}
	}*/

	for (int nCntY = 0; nCntY < MESHFILD_Y + 1; nCntY++)
	{

		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			pldx[nCntY + 1 + nCntX * 2] = 0 + nCntX;
		}

		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			pldx[nCntY + nCntX * 2] = 0 + nCntX + MESHFILD_X + 1;
		}

		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			//pldx[nCntY + 3 + nCntX * 2] = 0 + nCntX + MESHFILD_X*2;
		}
	}

	//インデックスバッファをアンロック
	g_pldxBuffMeshFild->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitMeshfild(void)
{
	//バッファの開放
	if (g_pVtxBuffMeshfild != NULL)
	{
		g_pVtxBuffMeshfild->Release();
		g_pVtxBuffMeshfild = NULL;
	}

	//インデックスバッファの開放
	if (g_pldxBuffMeshFild != NULL)
	{
		g_pldxBuffMeshFild->Release();
		g_pldxBuffMeshFild = NULL;
	}

	//テクスチャの開放
	if (g_pTextureMeshfild != NULL)
	{
		g_pTextureMeshfild->Release();
		g_pTextureMeshfild = NULL;
	}
}

//-----------------------------------------------------------------------------
// ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdateMeshfild(void)
{

}

//-----------------------------------------------------------------------------
// ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawMeshfild(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfild);

	//向きの反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfild.y, g_rotMeshfild.x, g_rotMeshfild.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfild, &g_mtxWorldMeshfild, &mtxRot);

	//位置の反転
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfild, &g_mtxWorldMeshfild, &mtxTrans);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfild, 0, sizeof(VERTEX_3D));

	//頂点インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pldxBuffMeshFild);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfild);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfild);

	//ポリゴンの描画
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 30);
}