//==============================================================================
//
// �J�����̐ݒ�kcamera.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "camera.h"
#include "input.h"

//==============================================================================
// �}�N����`
//==============================================================================
//#define CAMERA_POSV_X	(0.0f)
#define CAMERA_POSV_Y	(100.0f)
#define CAMERA_POSV_Z	(200.0f)
//#define CAMERA_ANGLE	(atan2f(600, 300))	// �J�����̊p�x
#define CAMERA_MOVE		(2.0f)
#define CAMERA_TURN		(100.0f)
#define CAMERA_RANGE	(200.0f)

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
Camera g_camera;

//==============================================================================
// ����������
//==============================================================================
void InitCamera(void)
{
	// �\���̂̏�����
	g_camera.posV = D3DXVECTOR3(0.0f, CAMERA_POSV_Y, -CAMERA_POSV_Z);	// ���_�ʒu
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �����_�ʒu
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// ������x�N�g��
	g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���_�̈ړ���
	g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �����_�̈ړ���
	g_camera.moveXVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���_�E�����_����������X���ړ���
	g_camera.moveZVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���_�E�����_����������Z���ړ���

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �J�����̊p�x

	g_camera.fLength = sqrtf((g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y) + (g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));

	if (g_camera.fLength < 0.0f)
	{
		g_camera.fLength *= -1;
	}
}

//==============================================================================
// �I������
//==============================================================================
void UninitCamera(void)
{

}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateCamera(void)
{
	// �����_�Ƃ̋���
	//g_camera.fLength = sqrtf(
	//	(g_camera.posV.y - g_camera.posR.y) * (g_camera.posV.y - g_camera.posR.y) + 
	//	(g_camera.posV.z - g_camera.posR.z) * (g_camera.posV.z - g_camera.posR.z));

	// ���Z�b�g
	if (GetKeyboardTrigger(KEYINFO_SPACE) == true)
	{
		g_camera.posV = D3DXVECTOR3(0.0f, CAMERA_POSV_Y, -CAMERA_POSV_Z);	// ���_�ʒu
		g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �����_�ʒu
		g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						// ������x�N�g��
		g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���_�̈ړ���
		g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �����_�̈ړ���
		g_camera.moveXVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���_�E�����_����������X���ړ���
		g_camera.moveZVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���_�E�����_����������Z���ړ���
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �J�����̊p�x
	}

	// ���_�E�����_�̈ړ�
	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		g_camera.moveZVR.x = sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.moveZVR.z = cosf(g_camera.rot.y) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		g_camera.moveZVR.x = sinf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
		g_camera.moveZVR.z = cosf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	}
	else
	{
		g_camera.moveZVR.x = 0.0f;
		g_camera.moveZVR.z = 0.0f;
	}

	if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{
		g_camera.moveXVR.x = cosf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
		g_camera.moveXVR.z = sinf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{
		g_camera.moveXVR.x = cosf(-g_camera.rot.y) * CAMERA_MOVE;
		g_camera.moveXVR.z = sinf(-g_camera.rot.y) * CAMERA_MOVE;
	}
	else
	{
		g_camera.moveXVR.x = 0.0f;
		g_camera.moveXVR.z = 0.0f;
	}


	// �����_�̈ړ�(���E)
	if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	{
		g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	}
	else if(GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	{
		g_camera.rot.y += D3DX_PI / CAMERA_TURN;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	}

	// �����_�̈ړ�(�㉺)
	if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	{
		g_camera.moveR.y = CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	{
		g_camera.moveR.y = -CAMERA_MOVE;
	}
	else
	{
		g_camera.moveR.y = 0.0f;
	}

	// ���_�̈ړ�(���E)
	if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true)
	{
		g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true)
	{
		g_camera.rot.y += D3DX_PI / CAMERA_TURN;

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	}

	// ���_�̈ړ�(�㉺)
	if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true)
	{
		g_camera.moveV.y = CAMERA_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true)
	{
		g_camera.moveV.y = -CAMERA_MOVE;
	}
	else
	{
		g_camera.moveV.y = 0.0f;
	}

	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2;
	}
	else if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2;
	}

	// �ړ��ʂ̉��Z
	g_camera.posV += g_camera.moveV;
	g_camera.posR += g_camera.moveR;
	g_camera.posV += g_camera.moveXVR;
	g_camera.posR += g_camera.moveXVR;
	g_camera.posV += g_camera.moveZVR;
	g_camera.posR += g_camera.moveZVR;
}

//==============================================================================
// �J�����̐ݒ菈��
//==============================================================================
void SetCamera(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(
		&g_camera.mtxProjection,
		D3DXToRadian(45.0f),							// ��p�̐ݒ�
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		// ��ʔ䗦�̐ݒ�
		10.0f,											// ��O���E�̕`�拗��
		1000.0f);										// �����E�̕`�拗��

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

// �J�����̎擾
Camera GetCamera(void)
{
	return g_camera;
}