//-----------------------------------------------------------------
//
// プレイヤーの処理 (player.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "player.h"
#include"camera.h"
#include "shadow.h"
#include "model.h"

//-------------------------------------------------------------------
// マクロ定義
//-------------------------------------------------------------------
#define PLAYER_X		(50)									// 中心から端までまでの長さ(x)
#define PLAYER_Y		(50)									// 中心から端までまでの長さ(y)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			//テクスチャ
//D3DXVECTOR3 g_posShadow;							//位置
//D3DXVECTOR3 g_Shadow.rot;							//向き
SHADOW g_Shadow[MAX_SHADOW];
D3DXMATRIX g_mtxWorldShadow;						//ワールドマトリックス

//-----------------------------------------------------------------------------
// ポリゴンの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitShadow(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//位置
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//向き
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//使われているか
		g_Shadow[nCntShadow].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 50);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 50);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 50);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 50);

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//ベクトルの法線
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// ポリゴンの終了処理
//-----------------------------------------------------------------------------
void UninitShadow(void)
{
	//バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	//テクスチャの開放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//-----------------------------------------------------------------------------
// ポリゴンの更新処理
//-----------------------------------------------------------------------------
void UpdateShadow(void)
{
}

//-----------------------------------------------------------------------------
// ポリゴンの描画処理
//-----------------------------------------------------------------------------
void DrawShadow(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;		//デバイスへのポインタ
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//使用されているとき
		if (g_Shadow[nCntShadow].bUse == true)
		{
			//減算合成の設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			//向きの反転
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

			//位置の反転
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureShadow);

				//ポリゴンの描画
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
		}

		//通常の合成に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
void SetShadow(D3DXVECTOR3 pos)
{
	SHADOW *pShadow;

	VERTEX_3D *pVtx;

	pShadow = &g_Shadow[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			//位置
			pShadow->pos = pos;

			//使用する
			pShadow->bUse = true;

			////頂点座標
			//pVtx[0].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
			//pVtx[1].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
			//pVtx[2].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);
			//pVtx[3].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);

			break;
		}

		pVtx += 4;//4頂点ごとずらす
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;
	SHADOW *pShadow;
	pShadow = &g_Shadow[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//pSpeed += nIdx;
	pVtx += nIdx * 4;

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
	pVtx[1].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
	pVtx[2].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);
	pVtx[3].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}
