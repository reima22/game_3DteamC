//================================================
//
//プレイヤー処理[Meshfeild.h]
// Author; miura yuudai
//
//================================================
#include "meshfield.h"


//==============
//グローバル変数
//==============
LPDIRECT3DTEXTURE9 g_pTexturemeshfield = NULL;//テクスチャ情報
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;//インデックスへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffmeshfield = NULL;//頂点情報
MESHFIELD g_posmeshfield;//位置
D3DXVECTOR3 g_rotmeshfield;//向き
D3DXMATRIX g_mtxWorldmeshfield;//ワールドマトリックス
float g_field;


//====================
//ポリゴンの初期化処理
//====================
HRESULT InitMeshfield(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field004.jpg", &g_pTexturemeshfield);

	//変数初期化
	g_posmeshfield.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotmeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffmeshfield,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffmeshfield->Lock(0, 0, (void**)&pVtx, 0);


	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-50, 0, 50);
	pVtx[1].pos = D3DXVECTOR3(50, 0, 50);
	pVtx[2].pos = D3DXVECTOR3(150, 0, 50);
	pVtx[3].pos = D3DXVECTOR3(-50, 0, -50);
	pVtx[4].pos = D3DXVECTOR3(50, 0, -50);
	pVtx[5].pos = D3DXVECTOR3(150, 0, -50);
	pVtx[6].pos = D3DXVECTOR3(-50, 0, -150);
	pVtx[7].pos = D3DXVECTOR3(50, 0, -150);
	pVtx[8].pos = D3DXVECTOR3(150, 0, -150);

	for (int nCntfield = 0; nCntfield < 9; nCntfield++)
	{
		//法線ベクトルの設定
		pVtx[nCntfield].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntfield].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(3.0f, 2.0f);
	pVtx[1].tex = D3DXVECTOR2(3.0f, 3.0f);
	pVtx[2].tex = D3DXVECTOR2(3.0f, 2.0f);
	pVtx[3].tex = D3DXVECTOR2(2.0f, 2.0f);
	pVtx[4].tex = D3DXVECTOR2(2.0f, 3.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 2.0f);
	pVtx[6].tex = D3DXVECTOR2(2.0f, 3.0f);
	pVtx[7].tex = D3DXVECTOR2(3.0f, 3.0f);
	pVtx[8].tex = D3DXVECTOR2(3.0f, 2.0f);


	//頂点バッファをアンロック
	g_pVtxBuffmeshfield->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
	D3DUSAGE_WRITEONLY,
	D3DFMT_INDEX16,
	D3DPOOL_MANAGED,
	&g_pIdxBuffMeshField,
	NULL);

	WORD *pIdx;

	//インデックスバッファをロックし、頂点情報のポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();
	return S_OK;
}

//==================
//プレイヤーの終了処理
//==================
void UninitMeshfield(void)
{
	//テクスチャの開放
	if (g_pTexturemeshfield != NULL)
	{
		g_pTexturemeshfield->Release();
		g_pTexturemeshfield = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffmeshfield != NULL)
	{
		g_pVtxBuffmeshfield->Release();
		g_pVtxBuffmeshfield = NULL;
	}

	//インデックスバッファの開放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}
//==================
//プレイヤーの更新処理
//==================
void UpdateMeshfield(void)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点情報のポインタを取得
	g_pVtxBuffmeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[2].pos.y += 0.1f;
	//pVtx[11].pos.y += 0.1f;

	D3DXVECTOR3 vec;
	float fAngle;
	D3DXVECTOR3 move;

	vec = pVtx[2].pos - pVtx[1].pos;//現在地から目的地へのベクトル
	fAngle = atan2f(vec.x, vec.y);//ベクトルの角度を求める
	move.x = cosf(fAngle) * 1.0f;//移動量を求める
	move.y = cosf(fAngle) * 1.0f;//移動量を求める

	//頂点バッファをアンロック
	g_pVtxBuffmeshfield->Unlock();
}

//====================
//プレイヤーの描画処理
//====================
void DrawMeshfield(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//デバイスの取得
	pDevice = GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldmeshfield);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotmeshfield.y, g_rotmeshfield.x, g_rotmeshfield.z);

	D3DXMatrixMultiply(&g_mtxWorldmeshfield, &g_mtxWorldmeshfield, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posmeshfield.Pos.x, g_posmeshfield.Pos.y, g_posmeshfield.Pos.z);

	D3DXMatrixMultiply(&g_mtxWorldmeshfield, &g_mtxWorldmeshfield, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldmeshfield);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffmeshfield, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturemeshfield);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);

}