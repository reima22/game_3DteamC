//================================================
//
//壁の処理[Effect.h]
// Author; takahashi shouta
//
//================================================
#include "Effect.h"

//==============
//グローバル変数
//==============
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//テクスチャ情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//頂点情報
D3DXMATRIX g_mtxWorldEffect;//ワールドマトリックス
EFFECT g_Effect[MAX_EFFECT];

//====================
//ビルボードの初期化処理
//====================
HRESULT InitEffect(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureEffect);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//位置
		g_Effect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//寿命
		g_Effect[nCntEffect].nLife = 0;

		//使われているか
		g_Effect[nCntEffect].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-5, 5, 0);
	pVtx[1].pos = D3DXVECTOR3(5, 5, 0);
	pVtx[2].pos = D3DXVECTOR3(-5, -5, 0);
	pVtx[3].pos = D3DXVECTOR3(5, -5, 0);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();

	return S_OK;
}

//==================
//ビルボードの終了処理
//==================
void UninitEffect(void)
{
	//テクスチャの開放
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//==================
//ビルボードの更新処理
//==================
void UpdateEffect(void)
{
	EFFECT *pEffect;
	pEffect = &g_Effect[0];
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		//寿命を減らす
		pEffect->nLife--;
		
		////寿命チェック
		//if (pEffect->nLife == 400)
		//{
		//	//頂点カラーの設定
		//	pVtx[0].col = D3DCOLOR_RGBA(55, 55, 0, 255);
		//	pVtx[1].col = D3DCOLOR_RGBA(55, 55, 0, 255);
		//	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		//	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		//}

		//寿命チェック
		if (pEffect->nLife == 0)
		{
			pEffect->bUse = false;
		}

		pEffect->move.y -= 0.02;

		if (pEffect->pos.y <= 0)
		{
			pEffect->move.y *= -1.0;
		}
		
		//位置の更新
		pEffect->pos.x += pEffect->move.x;
		pEffect->pos.y += pEffect->move.y;
		pEffect->pos.z += pEffect->move.z;
	}

	//頂点バッファをアンロック
	g_pVtxBuffEffect->Unlock();

}

//====================
//ビルボードの描画処理
//====================
void DrawEffect(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//ビューマトリックス取得用
	D3DXMATRIX mtxView;

	//計算用マトリックス
	D3DXMATRIX mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//Zバッファ
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//ライティングを無効する
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	//加算合成の設定
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//使用されているとき
		if (g_Effect[nCntEffect].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_mtxWorldEffect);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldEffect, NULL, &mtxView);//逆行列を求める
			g_mtxWorldEffect._41 = 0.0f;
			g_mtxWorldEffect._42 = 0.0f;
			g_mtxWorldEffect._43 = 0.0f;

			//位置の反転
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCntEffect].pos.x, g_Effect[nCntEffect].pos.y, g_Effect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldEffect, &g_mtxWorldEffect, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldEffect);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	//ライティングを有効する
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zバッファ
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move ,int nLife)
{
	EFFECT *pEffect;

	VERTEX_3D *pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	pEffect = &g_Effect[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
	
	
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++, pEffect++)
	{
		if (g_Effect[nCntEffect].bUse == false)
		{
			//位置
			pEffect->pos = pos;

			//移動量
			pEffect->move = move;

			pEffect->nLife = nLife;

			//使用する
			pEffect->bUse = true;

			break;
		}
		pVtx += 4;//4頂点ごとずらす
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEffect->Unlock();
}

//-----------------------------------------------------------------------------
// 弾の頂点座標の設定
//-----------------------------------------------------------------------------
void SetVertexEffect(int nIdx)
{
	//VERTEX_3D *pVtx;

	////頂点バッファをロックし、頂点情報へのポインタを取得
	//g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	////頂点バッファをアンロックする
	//g_pVtxBuffEffect->Unlock();
}

//-------------------------------
//弾の情報取得
//-------------------------------
EFFECT * GetEffect(void)
{
	return &g_Effect[0];
}