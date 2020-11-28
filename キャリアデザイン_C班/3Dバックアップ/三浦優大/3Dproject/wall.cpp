//================================================
//
//壁の処理[wall.h]
// Author; miura yuudai
//
//================================================
#include "wall.h"


//==============
//グローバル変数
//==============
LPDIRECT3DTEXTURE9 g_pTexturewall = NULL;//テクスチャ情報
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffwall = NULL;//インデックスへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffwall = NULL;//頂点情報
Wall g_poswall[256];//位置
D3DXMATRIX g_mtxWorldwall;//ワールドマトリックス


//====================
//ポリゴンの初期化処理
//====================
HRESULT InitWall(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field003.jpg", &g_pTexturewall);

	for (int nCntwall = 0; nCntwall < 256; nCntwall++)
	{
		//変数初期化
		g_poswall[nCntwall].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_poswall[nCntwall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_poswall[nCntwall].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffwall,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntwall = 0; nCntwall < 256; nCntwall++)
	{
		for (int nCntwall = 0; nCntwall < 9; nCntwall++)
		{
			//法線ベクトルの設定
			pVtx[nCntwall].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//頂点カラーの設定
			pVtx[nCntwall].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;//4頂点ごとずらす
	}

	//頂点バッファをアンロック
	g_pVtxBuffwall->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * 256,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffwall,
		NULL);

	WORD *pIdx;

	//インデックスバッファをロックし、頂点情報のポインタを取得
	g_pIdxBuffwall->Lock(0, 0, (void**)&pIdx, 0);

	//番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファをアンロック
	g_pIdxBuffwall->Unlock();

	return S_OK;
}

//==================
//プレイヤーの終了処理
//==================
void UninitWall(void)
{
	//テクスチャの開放
	if (g_pTexturewall != NULL)
	{
		g_pTexturewall->Release();
		g_pTexturewall = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffwall != NULL)
	{
		g_pVtxBuffwall->Release();
		g_pVtxBuffwall = NULL;
	}
	
	//インデックスバッファの開放
	if (g_pIdxBuffwall != NULL)
	{
		g_pIdxBuffwall->Release();
		g_pIdxBuffwall = NULL;
	}
}
//==================
//プレイヤーの更新処理
//==================
void UpdateWall(void)
{

}

//====================
//プレイヤーの描画処理
//====================
void DrawWall(void)
{
	Wall *pWall;
	pWall = &g_poswall[0];

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntwall = 0; nCntwall < 256; nCntwall++, pWall++)
	{
		if (pWall->bUse == true)//弾を使用しているかどうか
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldwall);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_poswall[nCntwall].rot.y, g_poswall[nCntwall].rot.x, g_poswall[nCntwall].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldwall, &g_mtxWorldwall, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_poswall[nCntwall].Pos.x, g_poswall[nCntwall].Pos.y, g_poswall[nCntwall].Pos.z);

			D3DXMatrixMultiply(&g_mtxWorldwall, &g_mtxWorldwall, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldwall);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffwall, 0, sizeof(VERTEX_3D));

			//インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffwall);

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTexturewall);

			//ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);
		}
	}
}
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Wall *pWall;
	pWall = &g_poswall[0];

	VERTEX_3D *pVtx;

	// 頂点バッファをロック
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntwall = 0; nCntwall < 256; nCntwall++, pWall++)
	{
		if (g_poswall[nCntwall].bUse == false)//弾を使用しているかどうか
		{
			//位置設定
			g_poswall[nCntwall].Pos = pos;

			g_poswall[nCntwall].rot = rot;

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x - 50, g_poswall[nCntwall].Pos.y + 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[1].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 50, g_poswall[nCntwall].Pos.y + 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[2].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 150, g_poswall[nCntwall].Pos.y + 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[3].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x - 50, g_poswall[nCntwall].Pos.y - 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[4].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 50, g_poswall[nCntwall].Pos.y - 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[5].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 150, g_poswall[nCntwall].Pos.y - 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[6].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x - 50, g_poswall[nCntwall].Pos.y - 150, g_poswall[nCntwall].Pos.z + 0);
			pVtx[7].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 50, g_poswall[nCntwall].Pos.y - 150, g_poswall[nCntwall].Pos.z + 0);
			pVtx[8].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 150, g_poswall[nCntwall].Pos.y - 150, g_poswall[nCntwall].Pos.z + 0);

			//弾の使用
			g_poswall[nCntwall].bUse = true;
			break;
		}
		pVtx += 4;//4頂点ごとずらす
	}
	//頂点バッファをアンロック
	g_pVtxBuffwall->Unlock();
}