#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//---------------------------------------------------------------------------- -
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_BULLET (256)				//�r���{�[�h�̏��
#define BULLET_SIZE (1)			//�r���{�[�h�̃T�C�Y

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
	bool bUse;
}BULLET;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitBullet(void);//����������
void UninitBullet(void);//�I������
void UpdateBullet(void);//�X�V����
void DrawBullet(void);//�`�揈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nSpeed, int nLife);
void SetVertexBullet(int nIdx);
BULLET * GetBullet(void);
#endif
