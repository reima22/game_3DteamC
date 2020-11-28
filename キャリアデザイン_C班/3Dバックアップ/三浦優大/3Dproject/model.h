#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//===============
//�\���̂̒�`
//===============
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 rotmove;//����
}MODEL;

//==========================
//�v���g�^�C�v�錾
//==========================
void InitModel(void);//����������
void UninitModel(void);//�I������
void UpdateModel(void);//�X�V����
void DrawModel(void);//�J�����̐ݒ�,Draw�̈�ԏ�Œ�`
MODEL *GetModel(void);
#endif
