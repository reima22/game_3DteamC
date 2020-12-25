//-----------------------------------------------------------------------------
//
// タイトルの処理
//Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//==============================================================================
// 自動遷移の状態
//==============================================================================
typedef enum
{
	TITLE_NONE = 0,	// 何もしない
	TITLE_AUTO,		// 自動遷移
	TITLE_MAX
} TITLEAUTO;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 size;
	D3DXCOLOR col;
	int TexType;
	bool bDisp;

}TITLE;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetVertexTitle(int nIdx);
TITLEAUTO GetTitle(void);

#endif _TITLE_H_
