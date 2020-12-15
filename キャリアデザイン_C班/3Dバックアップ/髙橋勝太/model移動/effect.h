#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//---------------------------------------------------------------------------- -
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_EFFECT (3056)				//�r���{�[�h�̏��
#define EFFECT_SIZE (4)			//�r���{�[�h�̃T�C�Y

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
	bool bUse;
}EFFECT;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitEffect(void);//����������
void UninitEffect(void);//�I������
void UpdateEffect(void);//�X�V����
void DrawEffect(void);//�`�揈��
void SetEffect(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType, float fWidth, float fHeigth);
void SetVertexEffect(int nIdx);
EFFECT * GetEffect(void);
#endif
