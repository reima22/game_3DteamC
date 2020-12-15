//-----------------------------------------------------------------
//
// �v���C���[�̏��� (camera.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "camera.h"
#include "input.h"
#include "model.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
CAMERA g_camera;									//�J�����̏��
float g_model;

//-----------------------------------------------------------------------------
// �J�����̏���������
//-----------------------------------------------------------------------------
void InitCamera(void)
{
	//�p�x�̏�����
	g_camera.Camera = 0;
	g_model = 0;

	//���_
	g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);

	//�����_
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�J�����̌���
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//-----------------------------------------------------------------------------
// �J�����̏I������
//-----------------------------------------------------------------------------
void UninitCamera(void)
{
}

//-----------------------------------------------------------------------------
// �J�����̍X�V����
//-----------------------------------------------------------------------------
void UpdateCamera(void)
{
	MODEL  *pModel;
	pModel = GetModel();

	////�J�����̈ړ�
	//if (GetKeyboardPress(DIK_A) == true)
	//{
	//	g_camera.posV.x += 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z += 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}

	//if (GetKeyboardPress(DIK_D) == true)
	//{
	//	g_camera.posV.x -= 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z -= 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}


	//if (GetKeyboardPress(DIK_S) == true)
	//{
	//	g_camera.posV.x -= 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z += 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}

	//if (GetKeyboardPress(DIK_W) == true)
	//{
	//	g_camera.posV.x += 1.5f*sinf(D3DX_PI + g_camera.Camera);
	//	g_camera.posV.z -= 1.5f*cosf(D3DX_PI + g_camera.Camera);
	//	g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 100;
	//	g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 100;
	//}

	//�J���������f���Ǐ]
	g_camera.posR = pModel->pos;
	g_camera.posV += pModel->move;
	/*g_camera.posV.x = pModel->move.x;
	g_camera.posV.z = pModel->move.z;
	g_camera.posV.y = pModel->pos.y;*/

	//���_�ړ�
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.Camera -= 0.1f;
		//g_camera.posV.x = g_camera.posR.x + sinf(g_fAnglecamera) * g_fLengthcamera;
		//g_camera.posV.z = g_camera.posR.z + cosf(g_fAnglecamera) * g_fLengthcamera;
		g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.Camera += 0.1f;
		//g_camera.posV.x = g_camera.posR.x + sinf(g_fAnglecamera) * g_fLengthcamera;
		//g_camera.posV.z = g_camera.posR.z + cosf(g_fAnglecamera) * g_fLengthcamera;
		g_camera.posR.x = g_camera.posV.x + sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posR.z = g_camera.posV.z - cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	//�����_�ړ�
	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.Camera -= 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.Camera += 0.1f;
		g_camera.posV.x = g_camera.posR.x - sinf(D3DX_PI + g_camera.Camera) * 200;
		g_camera.posV.z = g_camera.posR.z + cosf(D3DX_PI + g_camera.Camera) * 200;
	}

	//��]�p�x���Z�b�g
	if (g_camera.Camera >= D3DX_PI * 2)
	{
		g_camera.Camera = 0;
	}

	if (g_camera.Camera <= -D3DX_PI * 2)
	{
		g_camera.Camera = 0;
	}

	//�J�������Z�b�g
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		g_camera.Camera = 0;

		//���_
		g_camera.posV = D3DXVECTOR3(0.0f, 200.0f, -200.0f);

		//�����_
		//g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�J�����̌���
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���f���ʒu
		pModel->pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);

		//���f������
		pModel->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//-----------------------------------------------------------------------------
// �J�����̐ݒ�
//-----------------------------------------------------------------------------
void SetCamera(void)
{
	//�v���W�F�N�g�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxprojection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	//1000.0f ����͈̔�
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxprojection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 10.0f, 1000.0f);

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxprojection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView, &g_camera.posV, &g_camera.posR, &g_camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

CAMERA *GetCamera(void)
{
	return &g_camera;
}
