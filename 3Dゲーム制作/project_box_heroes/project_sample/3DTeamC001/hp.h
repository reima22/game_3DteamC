#ifndef _HP_H_
#define _HP_H_

#include "main.h"

//-----------------------------------------------------------------------------
//�\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	int nLife;
	int nType;
	float fWidth;
	float fHeigth;
	int nLifeBullet;
	bool bUse;
}HP;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitHp(void);//����������
void UninitHp(void);//�I������
void UpdateHp(void);//�X�V����
void DrawHp(void);//�`�揈��
void SetVertexHp(int nIdx);
#endif
