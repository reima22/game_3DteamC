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
#define SPLIT (2)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfild = NULL;	//頂点情報
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfild = NULL;	//
LPDIRECT3DTEXTURE9 g_pTextureMeshfild = NULL;		//テクスチャ
D3DXVECTOR3 g_posMeshfild;
D3DXVECTOR3 g_rotMeshfild;
D3DXMATRIX g_mtxWorldMeshfild;
int g_Maxpoint;		//頂点数
int g_nPolygon;		//必要なポリゴン数
int g_IndxPoint;	//必要な頂点数
int nColumn;		//横ポリゴン数
int nLine;			//奥行ポリゴン数
float fWidth;		//横幅
float fDepth;		//奥行幅

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitMeshifild(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;
	int nCount = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureMeshfild);

	g_posMeshfild = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_rotMeshfild = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	nLine = SPLIT;
	nColumn = SPLIT;
	g_Maxpoint = nLine * 2 * (nColumn + 2) - 2;
	g_nPolygon = nColumn * nLine * 2 + (4 * (nLine - 1));
	g_IndxPoint = (nColumn + 1) * (nLine + 1);
	fWidth = 100.0f;
	fDepth = 100.0f;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_IndxPoint, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED, &g_pVtxBuffMeshfild, NULL);

	//インデックスバッファ生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_Maxpoint, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIdxBuffMeshfild, NULL);

	WORD * pIdx;

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffMeshfild->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	/*pVtx[0].pos = D3DXVECTOR3(g_posMeshfild.x - FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z + FILD_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z + FILD_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshfild.x + FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z + FILD_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshfild.x - FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z);
	pVtx[4].pos = D3DXVECTOR3(g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshfild.x + FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshfild.x - FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z - FILD_SIZE);
	pVtx[7].pos = D3DXVECTOR3(g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z - FILD_SIZE);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshfild.x + FILD_SIZE, g_posMeshfild.y, g_posMeshfild.z - FILD_SIZE);*/

	for (int nCntLine = 0; nCntLine < (nLine + 1); nCntLine++)
	{//奥行
		for (int nCntColumn = 0; nCntColumn < (nColumn + 1); nCntColumn++, nCount++)
		{//横軸
		 //ポリゴンの各頂点座標
			pVtx[0].pos = D3DXVECTOR3(-fWidth + ((float)nCntColumn * fWidth), 0.0f, fDepth - ((float)nCntLine * fDepth));

			//法線ベクトルの設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
	
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntColumn, 1.0f * nCntLine);

			pVtx++;
		}
	}


	//インデックスバッファをロックし番号ポインタへのっポインタを取得
	g_pIdxBuffMeshfild->Lock(0, 0, (void**)&pIdx,0);

	//for文分割数+1
	int nCnt = 0;

	//番号データの設定
	for (int nCntIdx = 0; nCntIdx < g_Maxpoint / 2; nCntIdx++)
	{
		if (nCntIdx == (SPLIT * 2) + 1)
		{
			pIdx[nCntIdx] = nCnt + SPLIT + 1;
			pIdx[nCntIdx + 1] = nCnt;
			pIdx[nCntIdx + 2] = nCnt;
			nCnt++;
		}
		else if (nCntIdx == (SPLIT * 3) + 1)
		{
			pIdx[nCntIdx] = nCnt + SPLIT + 1;
			pIdx[nCntIdx + 1] = nCnt + SPLIT + 1;
			pIdx[nCntIdx + 2] = nCnt;
			nCnt++;
		}
		else
		{
			pIdx[nCntIdx] = nCnt + SPLIT + 1;
			pIdx[nCntIdx + 1] = nCnt;
		}
		nCnt++;
	}
		/*pIdx[0] = 3;
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
		pIdx[13] = 5;*/

	/*pIdx[0] = 4;
	pIdx[1] = 0;
	pIdx[2] = 5;
	pIdx[3] = 1;
	pIdx[4] = 6;
	pIdx[5] = 2;
	pIdx[6] = 7;
	pIdx[7] = 3;
	pIdx[8] = 3;
	pIdx[9] = 8;
	pIdx[10] = 8;
	pIdx[11] = 4;
	pIdx[12] = 9;
	pIdx[13] = 5;
	pIdx[14] = 10;
	pIdx[15] = 6;
	pIdx[16] = 11;
	pIdx[17] = 7;
	pIdx[18] = 7;
	pIdx[19] = 12;
	pIdx[20] = 12;
	pIdx[21] = 8;
	pIdx[22] = 13;
	pIdx[23] = 9;
	pIdx[24] = 14;
	pIdx[25] = 10;
	pIdx[26] = 15;
	pIdx[27] = 11;*/

	//頂点バッファをアンロックする
	g_pIdxBuffMeshfild->Unlock();

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
	if (g_pIdxBuffMeshfild != NULL)
	{
		g_pIdxBuffMeshfild->Release();
		g_pIdxBuffMeshfild = NULL;
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
	pDevice->SetIndices(g_pIdxBuffMeshfild);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshfild);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Maxpoint,0, g_nPolygon);
}
