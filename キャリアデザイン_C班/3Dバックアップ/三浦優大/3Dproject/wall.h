#ifndef _WALL_H_
#define _WALL_H_

#include "main.h"

//=============================
//�J�����̍\����
//=============================
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 rot;//����
	bool bUse;//�g���Ă��邩
}Wall;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitWall(void);//����������
void UninitWall(void);//�I������
void UpdateWall(void);//�X�V����
void DrawWall(void);//�`�揈��
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//�Ǐ���
#endif
