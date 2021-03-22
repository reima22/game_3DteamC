//==============================================================================
//
// リザルト画面の描画〔result.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "result.h"
#include "input.h"
#include "player.h"
//#include "score.h"
#include "sound.h"
#include "fade.h"
#include "gamepad.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define RESULT_POLYGON		(11)		// 最大ポリゴン数
#define TEXTURE_RESULT		(4)			// テクスチャの数
#define RESULTLOGO_POSX		(640.0f)	// リザルトロゴの中心X座標
#define RESULTLOGO_POSY		(200.0f)	// リザルトロゴの中心Y座標
#define RESULTLOGO_SIZEX	(240.0f)	// リザルトロゴの中心からの幅
#define RESULTLOGO_SIZEY	(40.0f)		// リザルトロゴの中心からの高さ
#define RESULT_PLATE_SIZEX	(240.0f)	// リザルトスコアプレートの幅
#define RESULT_PLATE_SIZEY	(40.0f)		// リザルトスコアプレートの高さ
#define RESULT_SCOREX		(500)		// リザルトスコアの上一桁目のX座標
#define RESULT_SCOREY		(360)		// リザルトスコアの上一桁目のY座標
#define RESULT_SCORE_SIZEX	(20.0f)		// リザルトスコアの一桁の幅
#define RESULT_SCORE_SIZEY	(30.0f)		// リザルトスコアの一桁の高さ

//==============================================================================
// グローバル変数
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[TEXTURE_RESULT] = {};	// リザルト画面テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			// バッファへのポインタ
D3DXVECTOR3 g_posResult;									// リザルト画面の位置
D3DXVECTOR3 g_posResultlogo;								// リザルトロゴの位置
D3DXVECTOR3 g_posResultPlate;								// スコアのプレート
//D3DXVECTOR3 g_posResultScore[MAX_SCORE];					// リザルトスコアの位置

//==============================================================================
// リザルト画面の初期化処理
//==============================================================================
HRESULT InitResult(void)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * RESULT_POLYGON,	// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,								// 頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	bool bResultbgm = RESULT_BGM;
	if (bResultbgm == true)
	{
		//if (Player->state == PLAYERSTATE_GAMEOVER)
		//{
		//	// BGMの再生
		//	PlaySound(SOUND_LABEL_BGM003);
		//}
		//else
		//{
			// BGMの再生
			PlaySound(SOUND_LABEL_BGM002);
		//}
	}

	return S_OK;
}

//==============================================================================
// リザルト画面の終了処理
//==============================================================================
void UninitResult(void)
{
	// サウンドの停止処理
	StopSound();

	// 頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	// テクスチャの開放
	for (int nCnt = 0; nCnt < TEXTURE_RESULT; nCnt++)
	{
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}
}

//==============================================================================
// リザルト画面の更新処理
//==============================================================================
void UpdateResult(void)
{
	// ローカル変数宣言
	VERTEX_2D *pVtx;
	FADE fade = GetFade();
	
	// ランキング画面への切り替え
	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}

//==============================================================================
// リザルト画面の描画処理
//==============================================================================
void DrawResult(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffResult,
		0,
		sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < RESULT_POLYGON; nCnt++)
	{
		if (nCnt == 0)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResult[0]);
		}
		else if (nCnt == 1)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResult[1]);
		}
		else if(nCnt == 2)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResult[2]);
		}
		else
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureResult[3]);
		}

		// ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// プリミティブの種類
			nCnt * 4,				// 描画を開始する頂点インデックス
			2);						// 描画するプリミティブ数
	}			
}