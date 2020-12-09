//-----------------------------------------------------------------------------
//
// �J�����̏���
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "camera.h"
#include "model.h"
#include "input.h"

//�}�N��
#define MOVE_CAMERA_SPEED (3.0f)
#define DISTANCE (500)
#define MOVE_ROT (0.0425f)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
Camera g_Camera;	//�J�������

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
void InitCamera(void)
{
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f,0.0f);		//�J�����̊p�x
	g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f,-DISTANCE);//���_
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����_
	g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		//�@���x�N�g��
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitCamera(void)
{

}

//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void UpdateCamera(void)
{

	Model *pModel;
	pModel = GetModel();
	
	g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_Camera.posVDest.x = pModel->pos.x - 20 * sin(pModel->rotDest.y);
	g_Camera.posVDest.z = pModel->pos.z - 20 * cosf(pModel->rotDest.y);
	g_Camera.posVDest.y = pModel->pos.y + 200;

	g_Camera.posV += (g_Camera.posVDest - g_Camera.posV) * 0.2f;
	g_Camera.posR += (g_Camera.posRDest - g_Camera.posR) * 0.2f;

	//�J�����ړ��E
	if (GetKeyboardPress(DIK_D) == true)
	{	
		g_Camera.posV.x += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
	}									 
	//�J�����ړ���						 
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_Camera.posV.x -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
	}

	//�J�����ړ���						 
	if (GetKeyboardPress(DIK_W) == true) 
	{									 
		g_Camera.posV.x += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x += sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z += cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
	}									  
	//�J�����ړ���O						
	if (GetKeyboardPress(DIK_S) == true)  
	{									  
		g_Camera.posV.x -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.x -= sinf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posV.z -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;
		g_Camera.posR.z -= cosf(g_Camera.rot.y) * MOVE_CAMERA_SPEED;

	}

	//�J�����ړ����_��
	if (GetKeyboardPress(DIK_T) == true)
	{
		g_Camera.posV.y += MOVE_CAMERA_SPEED;
	}

	//�J�����ړ����_��
	if (GetKeyboardPress(DIK_B) == true)
	{
		g_Camera.posV.y -= MOVE_CAMERA_SPEED;
	}

	//�J�����ړ������_��
	if (GetKeyboardPress(DIK_Y) == true)
	{
		g_Camera.posR.y += MOVE_CAMERA_SPEED;
	}
	//�J�����ړ������_��
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_Camera.posR.y -= MOVE_CAMERA_SPEED;
	}

	if (g_Camera.rot.y >= D3DX_PI)
	{
		g_Camera.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Camera.rot.y <= -D3DX_PI)
	{
		g_Camera.rot.y += D3DX_PI * 2.0f;
	}

	//�J�����ړ����_����]
	if (GetKeyboardPress(DIK_Z) == true)
	{		
		
		g_Camera.rot.y += MOVE_ROT;
		
		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * DISTANCE;
	}
	
	//�J�����ړ����_�E��]
	if (GetKeyboardPress(DIK_C) == true)
	{
		
		g_Camera.rot.y -= MOVE_ROT;
		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * DISTANCE;
	}

	//�J�����ړ������_����]
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_Camera.rot.y -= MOVE_ROT;
		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * DISTANCE;
	}

	//�J�����ړ������_�E��]
	if (GetKeyboardPress(DIK_E) == true)
	{
		g_Camera.rot.y += MOVE_ROT;
		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * DISTANCE;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * DISTANCE;

	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		g_Camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ�
		g_Camera.posV = D3DXVECTOR3(0.0f, 400.0f, -DISTANCE);	//���_
		g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�����_
		g_Camera.VecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//�@���x�N�g��
	}

}

//-----------------------------------------------------------------------------
//�ݒ菈��
//-----------------------------------------------------------------------------
void SetCamera(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
								D3DXToRadian(45.0f),
								(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
								10.0f, 10000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

	//�r���[�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_Camera.mtxView, &g_Camera.posV, &g_Camera.posR, &g_Camera.VecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

}

//
Camera *GetCamera(void)
{
	return &g_Camera;
}
