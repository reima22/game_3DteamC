//-----------------------------------------------------------------------------
//
// ポリゴンの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "shadow.h"

//マクロ
#define SHADOW_SIZE (15)
#define MAX_SHADOW (50)

//構造体
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	bool bUse;
}Shadow;

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;		//テクスチャ
D3DXCOLOR Shadowcol;
D3DXVECTOR3 g_posShadow;
D3DXVECTOR3 g_rotShadow;
D3DXMATRIX g_mtxWorldShadow;
Shadow g_aShadow[MAX_SHADOW];

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitShadow(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	g_posShadow = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_rotShadow = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Shadowcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_posShadow.x - SHADOW_SIZE, g_posShadow.y, g_posShadow.z + SHADOW_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posShadow.x + SHADOW_SIZE, g_posShadow.y, g_posShadow.z + SHADOW_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posShadow.x - SHADOW_SIZE, g_posShadow.y, g_posShadow.z - SHADOW_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posShadow.x + SHADOW_SIZE, g_posShadow.y, g_posShadow.z - SHADOW_SIZE);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	Shadowcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.65f);
	pVtx[0].col = Shadowcol;
	pVtx[1].col = Shadowcol;
	pVtx[2].col = Shadowcol;
	pVtx[3].col = Shadowcol;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//終了処理
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
//
//-----------------------------------------------------------------------------
void UpdateShadow(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posShadow.x, g_posShadow.y, g_posShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	//頂点バッファデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
