#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//=============================
//�J�����̍\����
//=============================
typedef struct
{
	D3DXVECTOR3 PosV;//���_
	D3DXVECTOR3 PosR;//�����_
	D3DXVECTOR3 VecU;//������x�N�g��
	D3DXVECTOR3 moveV;//���_
	D3DXVECTOR3 moveR;//�����_
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;//�J�����̌���
}Camera;

//==========================
//�v���g�^�C�v�錾
//==========================
void InitCamera(void);//����������
void UninitCamera(void);//�I������
void UpdateCamera(void);//�X�V����
void SetCamera(void);//�J�����̐ݒ�,Draw�̈�ԏ�Œ�`
Camera *GetCamera(void);
#endif