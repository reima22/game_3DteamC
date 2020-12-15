//-----------------------------------------------------------------
//
// �v���C���[�̏��� (model.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
	D3DXVECTOR3 rotmove;		//����
	D3DXVECTOR3 rotDest;		//����
	D3DXVECTOR3 MinModel;
	D3DXVECTOR3 MaxModel;
}MODEL;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL *GetModel(void);
#endif

