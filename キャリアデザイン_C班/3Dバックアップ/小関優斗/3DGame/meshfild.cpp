//-----------------------------------------------------------------------------
//
// メッシュフィールドの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "meshfild.h"
#include "input.h"

//マクロ
#define FILD_SIZE (100)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfild = NULL;	//頂点情報
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshfild = NULL;	//
LPDIRECT3DTEXTURE9 g_pTextureMeshfild = NULL;		//テクスチャ
D3DXVECTOR3 g_posMeshfild;
D3DXVECTOR3 g_rotMeshfild;
D3DXMATRIX g_mtxWorldMeshfild;
int g_nSplit;											//分割数
int g_nVertex;											//頂点数
int IndxVertex;											//インデックスの頂点数
int g_nPrimitive;										//プリミティブの数

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitMeshifild(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureMeshfild);

	g_posMeshfild = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_rotMeshfild = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	g_nVertex = 9;
	g_nSplit = 2;
	g_nPrimitive = 12;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_nVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED, &g_pVtxBuffMeshfild, NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndxBuffMeshfild, NULL);

	WORD * pIndx;

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffMeshfild->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_posMeshfild.x - FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z + FILD_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z + FILD_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshfild.x + FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z + FILD_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshfild.x - FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z);
	pVtx[4].pos = D3DXVECTOR3(g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshfild.x + FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshfild.x - FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z - FILD_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z - FILD_SIZE);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshfild.x + FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z - FILD_SIZE);

	//インデックスバッファをロックし番号ポインタへのっポインタを取得
	g_pIndxBuffMeshfild->Lock(0, 0, (void**)&pIndx,0);

	//for文分割数+1

	//番号データの設定

		pIndx[0] = 3;
		pIndx[1] = 0;
		pIndx[2] = 4;
		pIndx[3] = 1;
		pIndx[4] = 5;
		pIndx[5] = 2;
		pIndx[6] = 2;
		pIndx[7] = 6;
		pIndx[8] = 6;
		pIndx[9] = 3;
		pIndx[10] = 7;
		pIndx[11] = 4;
		pIndx[12] = 8;
		pIndx[13] = 5;

	//頂点バッファをアンロックする
	g_pIndxBuffMeshfild->Unlock();

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[4].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[5].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[6].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[7].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[8].col = D3DXCOLOR(255, 255, 255, 255);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMeshfild->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitMeshifild(void)
{
	//バッファの開放
	if (g_pVtxBuffMeshfild != NULL)
	{
		g_pVtxBuffMeshfild->Release();
		g_pVtxBuffMeshfild = NULL;
	}

	//テクスチャの開放
	if (g_pTextureMeshfild != NULL)
	{
		g_pTextureMeshfild->Release();
		g_pTextureMeshfild = NULL;
	}

	//インデックスバッファの開放
	if (g_pIndxBuffMeshfild != NULL)
	{
		g_pIndxBuffMeshfild->Release();
		g_pIndxBuffMeshfild = NULL;
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdateMeshifild(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawMeshifild(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshfild);

	//向き反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfild.y, g_rotMeshfild.x, g_rotMeshfild.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshfild, &g_mtxWorldMeshfild, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshfild, &g_mtxWorldMeshfild, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfild);

	//頂点バッファデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfild, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIndxBuffMeshfild);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfild);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,14,0,12);
}
