//==============================================================================
//
// ブロックの描画〔block.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "block.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "gamepad.h"
#include "score.h"
#include "particle.h"
#include "time.h"
#include "stdlib.h"

//==============================================================================
// グローバル変数
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			// ブロックテクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// バッファへのポインタ
BLOCK g_aBlock[BLOCK_MAX];							// ブロックの情報
int g_nSetBlock;
int g_nCntBreak;

//==============================================================================
// ブロックの初期化処理
//==============================================================================
HRESULT InitBlock(void)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 乱数算出から現時刻を除外
	srand((unsigned int)time(0));

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/block000.jpg",
		&g_pTextureBlock);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * BLOCK_MAX,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL)))
	{
		return E_FAIL;
	}

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		g_aBlock[nCnt].bUse = false;
		g_aBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].nLife = 3;
	}

	g_nSetBlock = 0;
	g_nCntBreak = 0;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++, pVtx += 4)
	{
		// ブロックの中心座標
		g_aBlock[nCnt].pos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);

		// ブロックの各頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y + BLOCK_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + BLOCK_SIZEX, g_aBlock[nCnt].pos.y + BLOCK_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + BLOCK_SIZEX, g_aBlock[nCnt].pos.y, 0.0f);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 各頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//==============================================================================
// ブロックの終了処理
//==============================================================================
void UninitBlock(void)
{
	//// ローカル変数宣言
	//BLOCK *pBlock;
	//// ブロックの取得
	//pBlock = &g_aBlock[0];
	//// ブロックの移動
	//for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++, pBlock++)
	//{
	//	if (pBlock->bUse == true)
	//	{
	//		pBlock->bUse = false;
	//	}
	//}

	// 頂点バッファの開放
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	// テクスチャの開放
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
}

//==============================================================================
// ブロックの更新処理
//==============================================================================
void UpdateBlock(void)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	BLOCK *pBlock;
	int nBreak = 0;

	// ブロックの取得
	pBlock = &g_aBlock[0];

	g_nSetBlock++;
	g_nCntBreak++;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// ブロックの移動
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++, pBlock++, pVtx += 4)
	{
		if (pBlock->bUse == true)
		{
			pBlock->pos += pBlock->move;

			// ブロックの頂点座標取得
			SetVertexBlock(nCnt);

			if (pBlock->pos.y >= SCREEN_HEIGHT)
			{
				pBlock->bUse = false;
			}

			if (pBlock->bBreak == true)
			{
				if (g_nCntBreak % 40 == 0)
				{
					// 各頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				else if (g_nCntBreak % 20 == 0 && g_nCntBreak % 40 != 0)
				{
					// 各頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(2, 255, 2, 255);
					pVtx[1].col = D3DCOLOR_RGBA(2, 255, 2, 255);
					pVtx[2].col = D3DCOLOR_RGBA(2, 255, 2, 255);
					pVtx[3].col = D3DCOLOR_RGBA(2, 255, 2, 255);
				}
			}

			// 敵の状態
			switch (g_aBlock[nCnt].state)
			{
			case BLOCKSTATE_DAMAGE:
				// カウント実行
				g_aBlock[nCnt].nCntState--;

				// カウント終了
				if (g_aBlock[nCnt].nCntState <= 0)
				{
					// 通常状態へ移行
					g_aBlock[nCnt].state = BLOCKSTATE_NORMAL;

					// 各頂点カラーの設定
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;

			default:
				break;
			}
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	nBreak = rand() % BLOCK_SET;

	if (g_nSetBlock == 10 || g_nSetBlock % 400 == 0)
	{
		for (int nCnt = 0; nCnt < BLOCK_SET; nCnt++)
		{
			if (nCnt == nBreak)
			{
				SetBlock(D3DXVECTOR3(40.0f + (nCnt * 80.0f), -20.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 40.0f, 40.0f, 3, true);
			}
			else
			{
				SetBlock(D3DXVECTOR3(40.0f + (nCnt * 80.0f), -20.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 40.0f, 40.0f, 0, false);
			}	
		}
	}
}

//==============================================================================
// ブロックの描画処理
//==============================================================================
void DrawBlock(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	BLOCK *pBlock;
	pBlock = GetBlock();

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffBlock,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBlock);

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++,pBlock++)
	{
		if (pBlock->bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				nCnt * 4,				// 描画を開始する頂点インデックス
				2);						// 描画するプリミティブ数
		}
	}
}

//==============================================================================
// ブロックの設定
//==============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight,int nLife,bool bBreak)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == false)
		{
			// 位置を設定
			g_aBlock[nCnt].pos = pos;

			// 移動力を設定
			g_aBlock[nCnt].move = move;

			// 幅の設定
			g_aBlock[nCnt].fWidth = fWidth;

			// 高さの設定
			g_aBlock[nCnt].fHeight = fHeight;

			// 耐久力の設定
			g_aBlock[nCnt].nLife = nLife;

			// 破壊の可否
			g_aBlock[nCnt].bBreak = bBreak;

			// 頂点座標を設定
			SetVertexBlock(nCnt);

			// 使用状態へ移行
			g_aBlock[nCnt].bUse = true;

			break;
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//==============================================================================
// ブロックの頂点座標取得処理
//==============================================================================
void SetVertexBlock(int nIdx)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	BLOCK *pBlock;

	// 敵の取得
	pBlock = &g_aBlock[0];

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点ポインタを4ずつ進める
	pVtx += nIdx * 4;

	pBlock += nIdx;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x - g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x - g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y - g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y - g_aBlock[nIdx].fHeight, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//==============================================================================
// ブロックの情報取得
//==============================================================================
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}

//==============================================================================
// ブロックの破壊判定
//==============================================================================
bool HitBlock(int nIdx, int nDamage)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	BLOCK *pBlock;
	int nScore = 0;

	// 敵の取得
	pBlock = &g_aBlock[0];

	g_aBlock[nIdx].nLife -= nDamage;
	
	// 残り体力による処理
	if (g_aBlock[nIdx].nLife <= 0)
	{
		// サウンドの再生
		PlaySound(SOUND_LABEL_SE_EXPLOSION000);

		// パーティクルの発生
		SetEffect(g_aBlock[nIdx].pos, 0.05f, D3DXCOLOR(0.9f, 0.4f, 0.1f, 1.0f), 15.0f, 0.015f);

		// スコアの設定
		nScore = 1000;

		//// 撃破した位置の高さによるスコアの倍率
		//if (pEnemy->pos.y >= LOW_SCORE && pEnemy->pos.y < MIDDLE_SCORE)
		//{
		//	nScore *= 2;
		//}
		//else if (pEnemy->pos.y >= MIDDLE_SCORE && pEnemy->pos.y < HIGH_SCORE)
		//{
		//	nScore *= 3;
		//}
		//else if (pEnemy->pos.y >= HIGH_SCORE && pEnemy->pos.y < WINDOW_LOWEST)
		//{
		//	nScore *= 4;
		//}

		// スコアの加算
		AddScore(nScore);

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		// 壁の破棄
		g_aBlock[nIdx].bBreak = false;
		// 各頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// 頂点バッファをアンロックする
		g_pVtxBuffBlock->Unlock();

		g_aBlock[nIdx].bUse = false;

		return true;
	}
	else
	{
		// 敵の状態の変化
		g_aBlock[nIdx].state = BLOCKSTATE_DAMAGE;
		g_aBlock[nIdx].nCntState = 5;

		// サウンドの再生
		PlaySound(SOUND_LABEL_SE_EXPLOSION000);

		// パーティクルの発生
		SetEffect(g_aBlock[nIdx].pos, 0.01f, D3DXCOLOR(0.9f, 0.1f, 0.1f, 1.0f), 3.0f, 0.015f);

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		// 各頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		// 頂点バッファをアンロックする
		g_pVtxBuffBlock->Unlock();

		return false;
	}
}