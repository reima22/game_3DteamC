#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//---------------------------------------------------------------------------- -
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_BILLBOARD (2)				//�r���{�[�h�̏��
#define BILLBOARD_SIZE (10)			//�r���{�[�h�̃T�C�Y

//-----------------------------------------------------------------------------
//�\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXVECTOR3 move;						//�ړ���
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	bool bUse;
}BILLBOARD;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitBillboard(void);//����������
void UninitBillboard(void);//�I������
void UpdateBillboard(void);//�X�V����
void DrawBillboard(void);//�`�揈��
void SetBillboard(D3DXVECTOR3 pos);
void SetVertexBillboard(int nIdx);
#endif
