//-----------------------------------------------------------------------------
//
// ポリゴンの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "polygon.h"
#include "input.h"

//マクロ
#define POLYGON_SIZE (100)
#define MOVE_PLYGON_SPEED (0.5f)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;		//テクスチャ
D3DXVECTOR3 g_posPolygon;
D3DXVECTOR3 g_rotPolygon;
D3DXMATRIX g_mtxWorldPolygon;

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitPolygon(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,"data/TEXTURE/field000.jpg", &g_pTexturePolygon);

	g_posPolygon = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_rotPolygon = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, 
								D3DPOOL_MANAGED, &g_pVtxBuffPolygon, NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_SIZE, g_posPolygon.y, g_posPolygon.z + POLYGON_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_SIZE, g_posPolygon.y, g_posPolygon.z + POLYGON_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x - POLYGON_SIZE, g_posPolygon.y, g_posPolygon.z - POLYGON_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + POLYGON_SIZE, g_posPolygon.y, g_posPolygon.z - POLYGON_SIZE);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(255,255,255,255);
	pVtx[1].col = D3DXCOLOR(255,255,255,255);
	pVtx[2].col = D3DXCOLOR(255,255,255,255);
	pVtx[3].col = D3DXCOLOR(255,255,255,255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitPolygon(void)
{
	//バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	//テクスチャの開放
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdatePolygon(void)
{
	
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);

	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x,g_posPolygon.y, g_posPolygon.z);

	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//頂点バッファデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
