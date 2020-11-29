//-----------------------------------------------------------------------------
//
// ビルボードの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//プロトタイプ宣言
HRESULT InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
void SetBillboard(D3DXVECTOR3 pos);

#endif _BILLBOARD_H_

