//==============================================================================
//
// 弾の描画〔bullet.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "bullet.h"
#include "player.h"
//#include "enemy.h"
//#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "particle.h"
#include "gamepad.h"
#include "block.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define ATK_BULLETA		(3)		// 弾Aの攻撃力
#define BULLETA_SIZEX	(5)		// 弾Aの幅
#define BULLETA_SIZEY	(10)	// 弾Aの高さ

//==============================================================================
// グローバル変数
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;	// 弾テクスチャーへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// 弾バッファへのポインタ
BULLET g_aBullet[BULLETNUM];							// 弾の情報
//SETBULLET State;										// 弾の状態
//int g_nCntType;											// 弾の装填状態カウント
//D3DXVECTOR3 g_rotMissile;								// ミサイルの回転角
//float g_fLengthMissile;									// ミサイルの対角線の長さ
//float g_fAngleMissile;									// ミサイルの対角線の角度

//==============================================================================
// 弾の初期化処理
//==============================================================================
HRESULT InitBullet(void)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/bullet000.png",
		&g_pTextureBullet);

	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet001.png",
	//	&g_pTextureBullet[1]);
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet002.png",
	//	&g_pTextureBullet[2]);
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet003.png",
	//	&g_pTextureBullet[3]);
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet_enemy000.png",
	//	&g_pTextureBullet[4]);

	// 変数の初期化処理
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// 頂点情報の設定
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * BULLETNUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++)
	{
		// 弾の中心座標の設定
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f ,0.0f);

		// 弾の頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y + BULLETA_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y - BULLETA_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y + BULLETA_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y - BULLETA_SIZEY, 0.0f);

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

		pVtx += 4;	// 頂点ポインタを4ずつ進める
	}
	
	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//==============================================================================
// 弾の終了処理
//==============================================================================
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//==============================================================================
// 弾の更新処理
//==============================================================================
void UpdateBullet(void)
{
	// ローカル変数宣言
	//PLAYER *Player;

	// プレイヤーの取得
	//Player = GetPlayer();

	// 弾の命中判定
	HitBullet();
}

//==============================================================================
// 弾の描画処理
//==============================================================================
void DrawBullet(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	BULLET *pBullet;

	// 弾の取得
	pBullet = &g_aBullet[0];

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffBullet,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++,pBullet++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBullet);

		// ポリゴンの生成
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// プリミティブの種類
				nCntBullet * 4,			// 描画を開始する頂点インデックス
				2);						// 描画するプリミティブ数
		}	
	}					
}

//==============================================================================
// 弾の設定
//==============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	BULLET *pBullet;

	// 弾の取得
	pBullet = &g_aBullet[0];

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	// 弾の設定
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			// 位置を設定
			pBullet->pos = pos;

			// 移動量を設定
			pBullet->move = move;

			// 寿命を設定
			pBullet->nLife = nLife;

			// 頂点座標を設定
			SetVertexBullet(nCntBullet);

			// 弾を使用する
			pBullet->bUse = true;
			break;
		}
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//==============================================================================
// 弾の命中
//==============================================================================
void HitBullet(void)
{
	// ローカル変数宣言
	BULLET *pBullet;
	BLOCK *pBlock;
	PLAYER *Player;
	int nScore = 0;

	// 弾の取得
	pBullet = &g_aBullet[0];

	// 敵の取得
	pBlock = GetBlock();

	// プレイヤーの取得
	Player = GetPlayer();

	// 弾の当たり判定と敵味方の判定
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{ // 弾が使用されていた場合
			// パーティクルの設定
			SetEffect(pBullet->pos, 0.0f, D3DXCOLOR(0.9f, 0.01f, 0.01f, 1.0f), 7.0f, 0.15f);

			// 位置の更新
			pBullet->pos += pBullet->move;

			// 壁との当たり判定
			for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++, pBlock++)
			{
				if (pBlock->bUse == true)
				{ // 壁が有効の場合
					if (pBullet->pos.y - BULLETA_SIZEY <= pBlock->pos.y + BLOCK_SIZEY &&
						pBullet->pos.x + BULLETA_SIZEX >= pBlock->pos.x - BLOCK_SIZEX &&
						pBullet->pos.x - BULLETA_SIZEX <= pBlock->pos.x + BLOCK_SIZEX &&
						pBullet->pos.y + BULLETA_SIZEY >= pBlock->pos.y - BLOCK_SIZEY)
					{ // 通常敵の命中範囲
						if (pBlock->bBreak == true)
						{
							// 破壊処理
							HitBlock(nCntBlock, 1);
						}

						// 弾の破棄
						pBullet->bUse = false;
					}
				}
			}

			// 敵情報の更新
			//pEnemy = GetEnemy();

			// 頂点座標の更新
			SetVertexBullet(nCntBullet);

			// 寿命チェック
			pBullet->nLife -= 2;
			if (pBullet->nLife <= 0)
			{
				pBullet->bUse = false;
			}

			// 画面外チェック
			if (pBullet->pos.y <= 0.0f || pBullet->pos.y >= SCREEN_HEIGHT || pBullet->pos.x <= 0.0f || pBullet->pos.x >= SCREEN_WIDTH)
			{
				pBullet->bUse = false;
			}
		}
	}
}

//==============================================================================
// 弾の頂点座標の設定
//==============================================================================
void SetVertexBullet(int nIdx)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	BULLET *pBullet;

	// 弾の取得
	pBullet = &g_aBullet[0];

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0,0,(void**)&pVtx,0);

	// 頂点ポインタを4ずつ進める
	pVtx += 4 * nIdx;

	// バレットポインタを進める
	pBullet += nIdx;

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETA_SIZEX, g_aBullet[nIdx].pos.y + BULLETA_SIZEY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETA_SIZEX, g_aBullet[nIdx].pos.y - BULLETA_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETA_SIZEX, g_aBullet[nIdx].pos.y + BULLETA_SIZEY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETA_SIZEX, g_aBullet[nIdx].pos.y - BULLETA_SIZEY, 0.0f);
	
	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}