//-----------------------------------------------------------------
//
// �v���C���[�̏��� (player.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_SHADOW (4)				//�e�̏��
#define SHADOW_SIZE (10)			//�e�̃T�C�Y

//-----------------------------------------------------------------------------
//�\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	bool bUse;
}SHADOW;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
//int SetShadow(D3DXVECTOR3 pos, float  fWidth, float fDepth);
void SetShadow(D3DXVECTOR3 pos);
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos);
//void SetPositionShadow(int nIdx);
#endif

