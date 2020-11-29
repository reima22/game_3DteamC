//-----------------------------------------------------------------------------
//
// ポリゴンの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//プロトタイプ宣言
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos,float fWidth,float fDepth);
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos);

#endif _SHADOW_H_
