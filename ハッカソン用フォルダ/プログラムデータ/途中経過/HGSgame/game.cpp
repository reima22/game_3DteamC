//==============================================================================
//
// ゲーム画面の描画〔game.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "game.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
//#include "enemy.h"
//#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "input.h"
//#include "ui.h"
#include "fade.h"
#include "item.h"
#include "pause.h"
//#include "counter.h"
//#include "life.h"
//#include "effect.h"
#include "particle.h"
//#include "bullet_ui.h"
//#include "line.h"
//#include "stock.h"
//#include "warning.h"
#include "block.h"
#include "gamepad.h"
#include "timer.h"
#include "time.h"
#include "stdlib.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define ENEMY_POSX			(50.0f)		// 敵の初期X座標
#define ENEMY_POSY			(-20.0f)	// 敵の初期Y座標

//==============================================================================
// グローバル変数
//==============================================================================
bool g_bPause;

//==============================================================================
// ゲーム画面の初期化処理
//==============================================================================
HRESULT InitGame(void)
{
	// 乱数処理から現時刻を除外
	srand((unsigned int)time(0));

	// 変数の初期化
	g_bPause = false;

	// 背景ポリゴンの初期化設定
	InitBg();

	// ユーザーインターフェースの初期化設定
	//InitStock();

	// プレイヤーの初期化処理
	InitPlayer();

	// 壁の初期化設定
	InitBlock();

	// アイテムの初期化処理
	InitItem();

	// 弾の初期化設定
	InitBullet();

	// エフェクトの初期化処理
	InitParticle();

	// タイマーの初期化処理
	InitTimer();

	// スコアの初期化処理
	InitScore();

	// ポーズメニューの初期化処理
	InitPause();

	// BGMの再生
	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//==============================================================================
// ゲーム画面の終了処理
//==============================================================================
void UninitGame(void)
{
	// サウンドの停止処理
	StopSound();

	// 背景ポリゴンの終了処理
	UninitBg();

	// ユーザーインターフェースの終了処理
	//UninitStock();

	// 弾の終了処理
	UninitBullet();

	// プレイヤーの終了処理
	UninitPlayer();

	// 敵の終了処理
	UninitBlock();

	// アイテムの終了処理
	UninitItem();

	// エフェクトの終了処理
	UninitParticle();

	// タイマーの終了処理
	UninitTimer();

	// スコアの終了処理
	UninitScore();

	// ポーズメニューの終了処理
	UninitPause();
}

//==============================================================================
// ゲーム画面の更新処理
//==============================================================================
void UpdateGame(void)
{
	// ローカル変数宣言
	PLAYER *Player;
	PAUSE_MENU pause;
	FADE fade;
	//ENEMYINFO info = GetInfo();		// 敵の全体情報の取得
	//PHASESTATE phase = GetPhase();	// 警戒状態の取得

	// プレイヤーの取得
	Player = GetPlayer();

	// ポーズの取得
	pause = GetPause();

	// フェードの取得
	fade = GetFade();

	// ポーズメニューへ移行
	//if (info.nStartCnt >= OPEN_CNT)
	{
		if (GetKeyboardTrigger(KEYINFO_PAUSE) == true || IsButtonDown(KEYINFO::KEYINFO_PAUSE) == true)
		{
			// 音の再生
			PlaySound(SOUND_LABEL_SE_START000);
			g_bPause = g_bPause ? false : true;	// ポーズの切り替え
		}
	}

	if (g_bPause == true)
	{ // ポーズ時の設定
		UpdatePause();	// ポーズの更新処理

		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{ // 選択時の処理
			if (fade != FADE_OUT)
			{ // 選択処理の重複防止
				// サウンドの再生
				PlaySound(SOUND_LABEL_SE_START000);
			}
			
			if (pause == PAUSE_MENU_CONTINUE)
			{ // CONTINUEの時
				g_bPause = false;				// ポーズの解除(ゲームの続行)
			}
			else if(pause == PAUSE_MENU_RETRY)
			{ // RETRYの時
				SetFade(FADE_OUT, MODE_GAME);	// ゲームのやり直し
			}
			else if (pause == PAUSE_MENU_QUIT)
			{ // QUITの時
				SetFade(FADE_OUT, MODE_TITLE);	// タイトルへ移行
			}
		}
	}
	else
	{ // 非ポーズ時の処理
		if (/*info.boss != BIGENEMY_DEATH && */Player->state != PLAYERSTATE_GAMEOVER)
		{ // ゲーム中の処理
		  // 背景ポリゴンの更新処理
			UpdateBg();

			// ユーザーインターフェースの更新処理
			//UpdateStock();

			// 弾の更新処理
			UpdateBullet();

			// 敵の更新処理
			UpdateBlock();

			// アイテムの更新処理
			UpdateItem();

			// プレイヤー更新時の条件
			//if (info.nStartCnt >= OPEN_CNT && phase == PHASESTATE_NORMAL)
			{
				// プレイヤーの更新処理
				UpdatePlayer();
			}

			// エフェクトの更新処理
			UpdateParticle();

			// タイマーの更新処理
			UpdateTimer();

			// スコアの更新処理
			UpdateScore();
		}

		// リザルト画面への遷移
		if (/*info.boss == BIGENEMY_DEATH ||*/ Player->state == PLAYERSTATE_GAMEOVER)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
}

//==============================================================================
// ゲーム画面の描画処理
//==============================================================================
void DrawGame(void)
{
	// 背景ポリゴンの描画処理
	DrawBg();

	// 敵の描画処理
	DrawBlock();

	// アイテムの描画処理
	DrawItem();

	// 弾の描画処理
	DrawBullet();

	// エフェクトの更新処理
	DrawParticle();

	// タイマーの描画処理
	DrawTimer();
	
	// ポリゴンの描画処理
	DrawPlayer();

	// ユーザーインターフェースの描画処理
	//DrawStock();

	// スコアの描画処理
	DrawScore();

	// ポーズの描画処理
	if (g_bPause == true)
	{
		DrawPause();
	}
}