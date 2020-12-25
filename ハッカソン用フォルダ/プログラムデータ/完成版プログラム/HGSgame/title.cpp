//-----------------------------------------------------------------------------
//
// タイトル画面の処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "gamepad.h"
//#include "Effect.h"
#include "sound.h"

//マクロ定義
#define MAX_TITLE_TEX (3)				//タイトルの画像の数
#define MAX_TITLE (3)					//タイトルポリゴン数
#define TITLE_BG_SIZE_X (640)			//タイトル画面の横幅
#define TITLE_BG_SIZE_Y (360)			//タイトル画面の立幅
#define GAME_TITLE_SIZE_X (700)			//タイトルの横幅
#define GAME_TITLE_SIZE_Y (100)			//タイトルの立幅
#define ENTER_SIZE_X (400)				//プレスエンターの横幅
#define ENTER_SIZE_Y (75)				//プレスエンターの立幅
#define MOVE_SIZE_TITLE_X (7)			//タイトルの移動速度
#define MOVE_SIZE_TITLE_Y (1)			//タイトルの移動速度

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE_TEX] = {};	//テクスチャ
TITLE g_aTitle[MAX_TITLE];
int g_nCounterTitle = 30;
int g_FadeCounter;
int g_nCounterT;
bool g_bEnter;
int g_TitleFadeCounter;
TITLEAUTO titleauto;
int g_nShiftCnt;

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	//サウンドスタート
	//PlaySound(SOUND_LABEL_BGM001);

	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gametitle.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pressenter.png", &g_pTextureTitle[2]);

	titleauto = TITLE_NONE;
	g_TitleFadeCounter = 0;
	g_bEnter = false;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].bDisp = true;	
		
	}	

	g_aTitle[1].size.x = 0.0f;
	g_aTitle[1].size.y = 0.0f;

	//テクスチャ設定
	g_aTitle[0].TexType = 0;
	g_aTitle[1].TexType = 1;
	g_aTitle[2].TexType = 2;

	g_FadeCounter = 0;
	g_nCounterTitle = 30;
	g_nShiftCnt = 0;

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{

		SetVertexTitle(nCntTitle);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[0].col = g_aTitle[nCntTitle].col;
		pVtx[1].col = g_aTitle[nCntTitle].col;
		pVtx[2].col = g_aTitle[nCntTitle].col;
		pVtx[3].col = g_aTitle[nCntTitle].col;

		//頂点バッファをアンロックする
		g_pVtxBuffTitle->Unlock();
	}

	// BGMの再生
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	// サウンドの停止処理
	StopSound();

	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE_TEX; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	FADE fade;
	fade = GetFade();

	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	VERTEX_2D *pVtx;

	g_nCounterT++;		//表示カウンター
	g_nShiftCnt++;		// 自動遷移カウンター

	if (g_aTitle[1].size.y < 100 || g_aTitle[1].size.x < 700)
	{
		g_aTitle[1].size.x += MOVE_SIZE_TITLE_X;
		g_aTitle[1].size.y += MOVE_SIZE_TITLE_Y;

	}

	if (g_nShiftCnt >= 600)// 約10秒
	{ // 自動遷移実行
	  // フェードアウト
		SetFade(FADE_OUT, MODE_RANKING);
		titleauto = TITLE_AUTO;
	}

	if ((g_nCounterT % g_nCounterTitle) == 0)
	{
		g_aTitle[2].bDisp = g_aTitle[2].bDisp ? false : true;	//プレスエンターの点滅
	}

	if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_SHOT) == true && fade == FADE_NONE)
	{

		if (g_aTitle[1].size.y < 100 || g_aTitle[1].size.x < 700)
		{
			g_aTitle[1].size.x = GAME_TITLE_SIZE_X;
			g_aTitle[1].size.y = GAME_TITLE_SIZE_Y;
		}

		else if (g_aTitle[1].size.y >= 100 && g_aTitle[1].size.x >= 700 && g_bEnter == false)
		{
			g_nCounterTitle -= 25;

			PlaySound(SOUND_LABEL_SE_START000);

			g_bEnter = true;
		}
	}

	if (g_bEnter == true)
	{
		if ((g_nCounterT % 2) == 0)
		{

			g_FadeCounter++;
		}
	}
	if (g_FadeCounter == 30)
	{
		//SetFade(FADE_OUT, MODE_GAME);

		SetFade(FADE_OUT, MODE_TUTORIAL);
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//頂点の座標
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[1].pos.x - g_aTitle[1].size.x, g_aTitle[1].pos.y + g_aTitle[1].size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitle[1].pos.x - g_aTitle[1].size.x, g_aTitle[1].pos.y - g_aTitle[1].size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitle[1].pos.x + g_aTitle[1].size.x, g_aTitle[1].pos.y + g_aTitle[1].size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitle[1].pos.x + g_aTitle[1].size.x, g_aTitle[1].pos.y - g_aTitle[1].size.y, 0.0f);

	//頂点バッファアンロック
	g_pVtxBuffTitle->Unlock();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCntTitle].TexType]);

		if (g_aTitle[nCntTitle].bDisp == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// タイトルの頂点座標の設定
//-----------------------------------------------------------------------------

void SetVertexTitle(int nIdx)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	pVtx += nIdx * 4;

	
	if (nIdx == 0)
	{//背景
	

		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);

		//頂点のカラー設定
		g_aTitle[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}
	else if (nIdx == 1)
	{//タイトル
		g_aTitle[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 350, 0);
		
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - g_aTitle[1].size.x, g_aTitle[nIdx].pos.y + g_aTitle[1].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - g_aTitle[1].size.x, g_aTitle[nIdx].pos.y - g_aTitle[1].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + g_aTitle[1].size.x, g_aTitle[nIdx].pos.y + g_aTitle[1].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + g_aTitle[1].size.x, g_aTitle[nIdx].pos.y - g_aTitle[1].size.y, 0.0f);

		//頂点のカラー設定
		g_aTitle[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (nIdx == 2)
	{//プレスエンター
		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f);
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);

		//頂点のカラー設定
		g_aTitle[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

TITLEAUTO GetTitle(void)
{
	return titleauto;
}