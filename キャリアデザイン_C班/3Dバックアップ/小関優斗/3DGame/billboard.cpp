//-----------------------------------------------------------------------------
//
// ビルボードの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "billboard.h"

//マクロ
#define POLYGON_SIZE (100)

//構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
}board;

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbillboard = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTexturebillboard = NULL;		//テクスチャ
board Billboard;
D3DXMATRIX g_mtxWorldBillboard;

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitBillboard(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field001.jpg", &g_pTexturebillboard);

	Billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED, &g_pVtxBuffbillboard, NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffbillboard->Lock(0, 0, (void**)&pVtx, 0);

	Billboard.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(Billboard.pos.x - POLYGON_SIZE, Billboard.pos.y + POLYGON_SIZE, Billboard.pos.z);
	pVtx[1].pos = D3DXVECTOR3(Billboard.pos.x + POLYGON_SIZE, Billboard.pos.y + POLYGON_SIZE, Billboard.pos.z);
	pVtx[2].pos = D3DXVECTOR3(Billboard.pos.x - POLYGON_SIZE, Billboard.pos.y, Billboard.pos.z);
	pVtx[3].pos = D3DXVECTOR3(Billboard.pos.x + POLYGON_SIZE, Billboard.pos.y, Billboard.pos.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラー
	Billboard.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[0].col = Billboard.col;
	pVtx[1].col = Billboard.col;
	pVtx[2].col = Billboard.col;
	pVtx[3].col = Billboard.col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffbillboard->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitBillboard(void)
{
	//バッファの開放
	if (g_pVtxBuffbillboard != NULL)
	{
		g_pVtxBuffbillboard->Release();
		g_pVtxBuffbillboard = NULL;
	}

	//テクスチャの開放
	if (g_pTexturebillboard != NULL)
	{
		g_pTexturebillboard->Release();
		g_pTexturebillboard = NULL;
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdateBillboard(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxView;

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ポリゴンをカメラに対して正面にする
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);	//逆行列を求める

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, Billboard.pos.x, Billboard.pos.y, Billboard.pos.z);

	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//頂点バッファデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffbillboard, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturebillboard);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
