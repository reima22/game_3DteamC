//================================================
//
//�J��������[Camera.h]
// Author; miura yuudai
//
//================================================
#include "camera.h"
#include "input.h"

//==================
//�O���[�o���ϐ�
//==================
Camera g_camera;//�J�����̏��
float g_Camera;

//=====================================
//����������
//=====================================
void InitCamera(void)
{
	g_camera.PosV = D3DXVECTOR3(0.0f, 150.0f, -200.0f);
	g_camera.PosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot.y = 0.0f;
}
//=====================================
//�I������
//=====================================
void UninitCamera(void)
{

}
//=====================================
//�X�V����
//=====================================
void UpdateCamera(void)
{
	//if (GetKeyboardPress(DIK_E) == true)//�v���C���[�̉�]
	//{
	//	g_camera.rot.y -= 0.01f;
	//	g_camera.moveV.x = g_camera.moveR.x + cosf(g_camera.rot.y) * 2.0f;
	//	g_camera.moveV.z = g_camera.moveR.z - sinf(g_camera.rot.y) * 2.0f;
	//}
	//if (GetKeyboardPress(DIK_Q) == true)//�v���C���[�̉�]
	//{
	//	g_camera.rot.y += 0.01f;
	//	g_camera.moveV.x = g_camera.moveR.x - cosf(g_camera.rot.y) * 2.0f;
	//	g_camera.moveV.z = g_camera.moveR.z + sinf(g_camera.rot.y) * 2.0f;
	//}
	//if (GetKeyboardPress(DIK_Z) == true)//�v���C���[�̉�]
	//{
	//	g_camera.rot.y += (D3DX_PI / 18);
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI*2.0f;
	//	}
	//	//g_camera.rot.y -= 0.01f;
	//	g_camera.moveR.x = g_camera.moveV.x - cosf(g_camera.rot.y) * 2.0f;
	//	g_camera.moveR.z = g_camera.moveV.z + sinf(g_camera.rot.y) * 2.0f;
	//}
	//if (GetKeyboardPress(DIK_C) == true)//�v���C���[�̉�]
	//{
	//	g_camera.rot.y += 0.01f;
	//	g_camera.moveR.x = g_camera.moveV.x + cosf(g_camera.rot.y) * 2.0f;
	//	g_camera.moveR.z = g_camera.moveV.z - sinf(g_camera.rot.y) * 2.0f;
	//}
	//if (GetKeyboardPress(DIK_W) == true)//�v���C���[�̉�]
	//{
	//	g_camera.moveV.x += sinf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveV.z += cosf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveR.x = g_camera.moveV.x + sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//	g_camera.moveR.z = g_camera.moveV.z + sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//}

	//if (GetKeyboardPress(DIK_S) == true)//�v���C���[�̉�]
	//{
	//	g_camera.moveV.x -= sinf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveV.z -= cosf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveR.x = g_camera.moveV.x - sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//	g_camera.moveR.z = g_camera.moveV.z - sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//}

	//if (GetKeyboardPress(DIK_A) == true)//�v���C���[�̉�]
	//{
	//	g_camera.moveV.x -= cosf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveV.z += sinf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveR.x = g_camera.moveV.x - sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//	g_camera.moveR.z = g_camera.moveV.z + sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//}

	//if (GetKeyboardPress(DIK_D) == true)//�v���C���[�̉�]
	//{
	//	g_camera.moveV.x += cosf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveV.z -= sinf(D3DX_PI + g_camera.rot.y)*2.0f;
	//	g_camera.moveR.x = g_camera.moveV.x + sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//	g_camera.moveR.z = g_camera.moveV.z - sinf(D3DX_PI + g_camera.rot.y) * 2.0f;
	//}

	//�J�����̈ړ�
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_camera.PosV.x += 1.5f*cosf(D3DX_PI + g_camera.rot.y);
		g_camera.PosV.z += 1.5f*sinf(D3DX_PI + g_camera.rot.y);
		g_camera.PosR.x = g_camera.PosV.x + sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosR.z = g_camera.PosV.z - cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	if (GetKeyboardPress(DIK_D) == true)
	{
		g_camera.PosV.x -= 1.5f*cosf(D3DX_PI + g_camera.rot.y);
		g_camera.PosV.z -= 1.5f*sinf(D3DX_PI + g_camera.rot.y);
		g_camera.PosR.x = g_camera.PosV.x + sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosR.z = g_camera.PosV.z - cosf(D3DX_PI + g_camera.rot.y) * 200;
	}


	if (GetKeyboardPress(DIK_S) == true)
	{
		g_camera.PosV.x -= 1.5f*sinf(D3DX_PI + g_camera.rot.y);
		g_camera.PosV.z += 1.5f*cosf(D3DX_PI + g_camera.rot.y);
		g_camera.PosR.x = g_camera.PosV.x + sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosR.z = g_camera.PosV.z - cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	if (GetKeyboardPress(DIK_W) == true)
	{
		g_camera.PosV.x += 1.5f*sinf(D3DX_PI + g_camera.rot.y);
		g_camera.PosV.z -= 1.5f*cosf(D3DX_PI + g_camera.rot.y);
		g_camera.PosR.x = g_camera.PosV.x + sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosR.z = g_camera.PosV.z - cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	//���_�ړ�
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.y -= 0.1f;
		//g_camera.posV.x = g_camera.posR.x + sinf(g_fAnglecamera) * g_fLengthcamera;
		//g_camera.posV.z = g_camera.posR.z + cosf(g_fAnglecamera) * g_fLengthcamera;
		g_camera.PosR.x = g_camera.PosV.x + sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosR.z = g_camera.PosV.z - cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.y += 0.1f;
		//g_camera.posV.x = g_camera.posR.x + sinf(g_fAnglecamera) * g_fLengthcamera;
		//g_camera.posV.z = g_camera.posR.z + cosf(g_fAnglecamera) * g_fLengthcamera;
		g_camera.PosR.x = g_camera.PosV.x + sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosR.z = g_camera.PosV.z - cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	//�����_�ړ�
	if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.rot.y -= 0.1f;
		g_camera.PosV.x = g_camera.PosR.x - sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosV.z = g_camera.PosR.z + cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.rot.y += 0.1f;
		g_camera.PosV.x = g_camera.PosR.x - sinf(D3DX_PI + g_camera.rot.y) * 200;
		g_camera.PosV.z = g_camera.PosR.z + cosf(D3DX_PI + g_camera.rot.y) * 200;
	}

	if (GetKeyboardPress(DIK_T) == true)
	{
		g_camera.PosR.y += 1.5f*cosf(D3DX_PI + g_camera.rot.y);
	}

	if (GetKeyboardPress(DIK_B) == true)
	{
		g_camera.PosR.y -= 1.5f*cosf(D3DX_PI + g_camera.rot.y);
	}
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_camera.PosV.y += 1.5f*cosf(D3DX_PI + g_camera.rot.y);
	}

	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_camera.PosV.y -= 1.5f*cosf(D3DX_PI + g_camera.rot.y);
	}

	//��]�p�x���Z�b�g
	if (g_camera.rot.y >= D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI;
	}

	else if (g_camera.rot.y <= -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI;
	}

	/*if (g_camera.rot.y <= -D3DX_PI * 2)
	{
		g_camera.rot.y = 0;
	}*/
	if (GetKeyboardPress(DIK_SPACE) == true)//�v���C���[�̉�]
	{
		InitCamera();
	}


	//�ʒu�X�V
	g_camera.PosV.x += g_camera.moveV.x;
	g_camera.PosV.z += g_camera.moveV.z;

	//�ʒu�X�V
	g_camera.PosR.x += g_camera.moveR.x;
	g_camera.PosR.z += g_camera.moveR.z;

	// �ړ��ʂ̌���
	g_camera.moveR.x += (0.0f - g_camera.moveR.x) *0.5f;
	g_camera.moveR.z += (0.0f - g_camera.moveR.z) *0.5f;
	
	// �ړ��ʂ̌���
	g_camera.moveV.x += (0.0f - g_camera.moveV.x) *0.5f;
	g_camera.moveV.z += (0.0f - g_camera.moveV.z) *0.5f;

}
//=====================================
//�ݒ菈��
//=====================================
void SetCamera(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,//��O
		1000.0f);//����

	//�v���W�F�N�V�����}�b�s���O�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.PosV,
		&g_camera.PosR,
		&g_camera.VecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
Camera *GetCamera(void)
{
	return &g_camera;
}