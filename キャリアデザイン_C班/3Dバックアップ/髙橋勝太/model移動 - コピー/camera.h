//-----------------------------------------------------------------
//
// �v���C���[�̏��� (camera.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------

//�\����
typedef struct
{
	//D3DXVECTOR3 rot;		
	D3DXVECTOR3 posV;			//�J�����̌���
	D3DXVECTOR3 posVDest;		//�J�����̌���
	D3DXVECTOR3 posR;			//�J�����̎��_
	D3DXVECTOR3 posRDest;		//�J�����̎��_
	D3DXVECTOR3 vecU;			//�J�����̒����_
	D3DXMATRIX mtxprojection;
	D3DXMATRIX mtxView;
	float Camera;				//�J�����̊p�x��ς���̂ɕK�v
}CAMERA;

//===============
//�v���g�^�C�v�錾
//===============
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
CAMERA *GetCamera(void);
#endif

