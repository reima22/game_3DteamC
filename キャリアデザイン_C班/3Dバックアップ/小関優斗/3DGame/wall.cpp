//-----------------------------------------------------------------------------
//
// 壁の処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "wall.h"

//マクロ
#define POLYGON_SIZE (100)
#define MAX_WALL (3)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//テクスチャ
Wall g_aWall[MAX_WALL];
D3DXMATRIX g_mtxWorldWall;

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitWall(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field001.jpg", &g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aWall[nCntWall].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
								D3DPOOL_MANAGED, &g_pVtxBuffWall, NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{

		g_aWall[0].pos = (D3DXVECTOR3(0.0f, 0.0f, 50.0f));

		g_aWall[1].pos = (D3DXVECTOR3(0.0f, 0.0f, 50.0f));

		g_aWall[2].pos = (D3DXVECTOR3(0.0f, 0.0f, 50.0f));

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - POLYGON_SIZE, g_aWall[nCntWall].pos.y + POLYGON_SIZE, g_aWall[nCntWall].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + POLYGON_SIZE, g_aWall[nCntWall].pos.y + POLYGON_SIZE, g_aWall[nCntWall].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - POLYGON_SIZE, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + POLYGON_SIZE, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラー
		g_aWall[nCntWall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[0].col = g_aWall[nCntWall].col;
		pVtx[1].col = g_aWall[nCntWall].col;
		pVtx[2].col = g_aWall[nCntWall].col;
		pVtx[3].col = g_aWall[nCntWall].col;

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitWall(void)
{
	//バッファの開放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//テクスチャの開放
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdateWall(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_mtxWorldWall);

		//向き反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);

		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

		//頂点バッファデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureWall);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}
