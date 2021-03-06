//================================================
//
//影の処理[Syadow.h]
// Author; miura yuudai
//
//================================================
#include "Shadow.h"
#include "model.h"


//==============
//グローバル変数
//==============
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//頂点情報
SHADOW g_posbaseShadow[256];//位置
D3DXVECTOR3 g_rotShadow;//向き
D3DXMATRIX g_mtxWorldShadow;//ワールドマトリックス


//====================
//影の初期化処理
//====================
HRESULT InitShadow(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		//変数初期化
		g_posbaseShadow[nCntShadow].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z + 20);
		pVtx[1].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z + 20);
		pVtx[2].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z - 20);
		pVtx[3].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z - 20);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 95);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 95);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 95);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 95);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//4頂点ごとずらす
	}

	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//==================
//影の終了処理
//==================
void UninitShadow(void)
{
	//テクスチャの開放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}
//==================
//影の更新処理
//==================
void UpdateShadow(void)
{
	MODEL *pModel;
	pModel = GetModel();
	SetShadow(pModel->Pos, 20, 20);
}

//====================
//影の描画処理
//====================
void DrawShadow(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	SHADOW *pShadow;
	pShadow = &g_posbaseShadow[0];

	//デバイスの取得
	pDevice = GetDevice();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_posbaseShadow[nCntShadow].Pos.x, g_posbaseShadow[nCntShadow].Pos.y, g_posbaseShadow[nCntShadow].Pos.z);
	}

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
void SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	VERTEX_3D *pVtx;

	SHADOW *pShadow;
	pShadow = &g_posbaseShadow[0];

	// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++,pShadow++)
	{
		if (g_posbaseShadow[nCntShadow].bUse == false)//弾を使用しているかどうか
		{
			g_posbaseShadow[nCntShadow].Pos = pos;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z + fDepth);//2Dは0.0固定
			pVtx[1].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z + fDepth);
			pVtx[2].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z - fDepth);
			pVtx[3].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z - fDepth);

			//弾の使用
			g_posbaseShadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;//4頂点ごとずらす
	}

	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();
}
