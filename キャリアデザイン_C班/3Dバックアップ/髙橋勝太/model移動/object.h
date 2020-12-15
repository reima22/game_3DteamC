//-----------------------------------------------------------------
//
// �v���C���[�̏��� (model.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"


typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����
}OBJECT;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
OBJECT*GetObject(void);
#endif

