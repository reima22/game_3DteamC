//-----------------------------------------------------------------------------
//
// �^�C�g���̏���
//Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//==============================================================================
// �����J�ڂ̏��
//==============================================================================
typedef enum
{
	TITLE_NONE = 0,	// �������Ȃ�
	TITLE_AUTO,		// �����J��
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
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetVertexTitle(int nIdx);
TITLEAUTO GetTitle(void);

#endif _TITLE_H_
