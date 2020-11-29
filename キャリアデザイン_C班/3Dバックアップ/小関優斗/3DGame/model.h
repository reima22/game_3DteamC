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
	D3DXVECTOR3 rot;					//����
	D3DXVECTOR3 PurposeRot;				//�ړI�̌���

}Model;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);