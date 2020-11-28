#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//================
//�\���̂̒�`
//================
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXMATRIX mtxworld;//���[���h�}�g���b�N�X
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	bool bUse;
}SHADOW;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitShadow(void);//����������
void UninitShadow(void);//�I������
void UpdateShadow(void);//�X�V����
void DrawShadow(void);//�`�揈��
void SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth);
#endif

