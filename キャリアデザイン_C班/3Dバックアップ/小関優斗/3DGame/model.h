//-----------------------------------------------------------------------------
//
// ���f���`��̏���
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "main.h"

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 posDest;
	D3DXVECTOR3 rot;					//����
	D3DXVECTOR3 rotDest;				//�ړI�̌���
	D3DXVECTOR3 move;					//�ړ����x

}Model;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);