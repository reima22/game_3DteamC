//-----------------------------------------------------------------
//
// タイトルの処理 (hp.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//インクルードファイル
//------------------------
#include "hp.h"
#include "input.h"
#include "fade.h"

//-----------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------
#define MAX_UI			(4)									// 最大数

#define PLAYER_X		(850.0f)							// ロゴ幅
#define PLAYER_Y		(100.0f)							// ロゴの高さ

#define PLAYER_BAR_X	(850.0f)							// ロゴの高さ
#define PLAYER_BAR_Y	(100.0f)							// ロゴの高さ

#define PLAYER2_X		(850.0f)							// ロゴ幅
#define PLAYER2_Y		(100.0f)							// ロゴの高さ

#define PLAYER2_BAR_X	(850.0f)							// ロゴの高さ
#define PLAYER2_BAR_Y	(100.0f)							// ロゴの高さ

//-----------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHp = NULL;
LPDIRECT3DTEXTURE9 g_pTextureHp[MAX_UI] = {};
D3DXVECTOR3 g_posPlayer;						// タイトルロゴの中心座標
D3DXVECTOR3 g_posPlayerBar;						// タイトルロゴの中心座標
D3DXVECTOR3 g_posPlayer2;						// タイトルロゴの中心座標
D3DXVECTOR3 g_posPlayer2Bar;					// タイトルロゴの中心座標
int g_PlayerBar = 0;
int g_Player2Bar = 0;


//-----------------------------------------------------------------
// タイトルの初期化処理
//-----------------------------------------------------------------
HRESULT InitHp(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	g_posPlayer = D3DXVECTOR3(450.0f, 100.0f, 0.0f);
	g_posPlayerBar = D3DXVECTOR3(450.0f, 100.0f, 0.0f);
	g_posPlayer2 = D3DXVECTOR3(SCREEN_WIDTH - 450.0f, 100.0f, 0.0f);
	g_posPlayer2Bar = D3DXVECTOR3(SCREEN_WIDTH - 450.0f, 100.0f, 0.0f);

	//テキスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP青.png", &g_pTextureHp[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP青 バー.png", &g_pTextureHp[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP赤.png", &g_pTextureHp[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP赤 バー.png", &g_pTextureHp[3]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_UI, // 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffHp,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHp = 0; nCntHp < MAX_UI; nCntHp++)
	{
		// 頂点座標の設定
		//SetVertexHp(nCntHp);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定			
		pVtx[0].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255,255, 255);

		// テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 情報の更新
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffHp->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// タイトルの終了処理
//-----------------------------------------------------------------
void UninitHp(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffHp != NULL)
	{
		g_pVtxBuffHp->Release();
		g_pVtxBuffHp = NULL;
	}

	// テクスチャの開放
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		if (g_pTextureHp[nCntTexture] != NULL)
		{
			g_pTextureHp[nCntTexture]->Release();
			g_pTextureHp[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// タイトルの更新処理
//-----------------------------------------------------------------
void UpdateHp(void)
{
	for (int nCntHp = 0; nCntHp < MAX_UI; nCntHp++)
	{
		// 頂点座標の設定
		SetVertexHp(nCntHp);
	}


	if (GetKeyboardPress(DIK_I) == true)
	{
		g_PlayerBar += 5;
	}

	if (GetKeyboardPress(DIK_K) == true)
	{
		g_Player2Bar+= 5;
	}
}

//-----------------------------------------------------------------
// タイトルの描画処理
//-----------------------------------------------------------------
void DrawHp(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// 変数の受け渡し
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHp, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureHp[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// タイトル画面に貼るテクスチャの指定
//-----------------------------------------------------------------
void SetVertexHp(int nCntHp)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	//青
	if (nCntHp == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(g_posPlayer.x - (PLAYER_X / 2), g_posPlayer.y + (PLAYER_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPlayer.x - (PLAYER_X / 2), g_posPlayer.y - (PLAYER_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPlayer.x + (PLAYER_X / 2), g_posPlayer.y + (PLAYER_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPlayer.x + (PLAYER_X / 2), g_posPlayer.y - (PLAYER_Y / 2), 0.0f);
	}

	//青バー
	if (nCntHp == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(g_posPlayerBar.x - (PLAYER_BAR_X / 2), g_posPlayerBar.y + (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posPlayerBar.x - (PLAYER_BAR_X / 2), g_posPlayerBar.y - (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posPlayerBar.x + (PLAYER_BAR_X / 2) - (g_PlayerBar), g_posPlayerBar.y + (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posPlayerBar.x + (PLAYER_BAR_X / 2) - (g_PlayerBar), g_posPlayerBar.y - (PLAYER_BAR_Y / 2), 0.0f);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f * ((850.0f - g_PlayerBar) / 850.0f), 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f * ((850.0f - g_PlayerBar) / 850.0f), 0.0f);
	}

	//赤
	if (nCntHp == 2)
	{
		pVtx[8].pos = D3DXVECTOR3(g_posPlayer2.x - (PLAYER2_X / 2), g_posPlayer2.y + (PLAYER2_Y / 2), 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posPlayer2.x - (PLAYER2_X / 2), g_posPlayer2.y - (PLAYER2_Y / 2), 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posPlayer2.x + (PLAYER2_X / 2), g_posPlayer2.y + (PLAYER2_Y / 2), 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posPlayer2.x + (PLAYER2_X / 2), g_posPlayer2.y - (PLAYER2_Y / 2), 0.0f);
	}

	//赤バー
	if (nCntHp == 3)
	{
		pVtx[12].pos = D3DXVECTOR3(g_posPlayer2Bar.x - (PLAYER2_BAR_X / 2) + (g_Player2Bar), g_posPlayer2Bar.y + (PLAYER2_BAR_Y / 2), 0.0f);
		pVtx[13].pos = D3DXVECTOR3(g_posPlayer2Bar.x - (PLAYER2_BAR_X / 2) + (g_Player2Bar), g_posPlayer2Bar.y - (PLAYER2_BAR_Y / 2), 0.0f);
		pVtx[14].pos = D3DXVECTOR3(g_posPlayer2Bar.x + (PLAYER2_BAR_X / 2), g_posPlayer2Bar.y + (PLAYER2_BAR_Y / 2), 0.0f);
		pVtx[15].pos = D3DXVECTOR3(g_posPlayer2Bar.x + (PLAYER2_BAR_X / 2), g_posPlayer2Bar.y - (PLAYER2_BAR_Y / 2), 0.0f);

		pVtx[12].tex = D3DXVECTOR2(1.0f * ((850.0f - g_Player2Bar) / 850.0f), 1.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f * ((850.0f - g_Player2Bar) / 850.0f), 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffHp->Unlock();
}