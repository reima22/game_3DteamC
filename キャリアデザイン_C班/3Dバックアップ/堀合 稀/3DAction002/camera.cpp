//==============================================================================
//
// �J�����̐ݒ�kcamera.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "camera.h"
#include "player.h"
#include "model.h"
#include "input.h"

//==============================================================================
// �}�N����`
//==============================================================================

//#define CAMERA_POSV_X	(0.0f)
//#define CAMERA_POSV_Y	(100.0f)			
//#define CAMERA_POSV_Z	(200.0f)
//#define CAMERA_ANGLE	(atan2f(600, 300))	// �J�����̊p�x
#define CAMERA_MOVE		(2.0f)				// �J�����̈ړ���
#define CAMERA_TURN		(D3DX_PI / 100.0f)	// �J�����̐��񑬓x
#define CAMERA_RANGE	(200.0f)			// ���_�E�����_�Ԃ̋���
#define CAMERA_HEIGHT	(100.0f)			// �J����(���_)�̍���
#define CAMERA_SPDOWN	(0.1f)				// �����W�� 

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
Camera g_camera;

//==============================================================================
// ����������
//==============================================================================
void InitCamera(void)
{
	// ���[�J���ϐ��錾
	//Model model = *GetModel();
	Player *player = GetPlayer();

	// �\���̂̏�����
	g_camera.posV = D3DXVECTOR3(
		player->pos.x,
		player->pos.y + 100.0f,
		player->pos.z - 200.0f);						// ���_�ʒu

	//g_camera.posV = D3DXVECTOR3(
	//	model.pos.x, 
	//	model.pos.y + 100.0f, 
	//	model.pos.z - 200.0f);							// ���_�ʒu
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_�ʒu
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
	g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���

	//g_camera.moveV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// ���_�̈ړ���
	//g_camera.moveR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						// �����_�̈ړ���
	//g_camera.moveXVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���_�E�����_����������X���ړ���
	//g_camera.moveZVR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ���_�E�����_����������Z���ړ���

	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̊p�x
	g_camera.fLength = CAMERA_RANGE;					// ���_�E�����_�Ԃ̋���
	g_camera.fHeightV = -60.0f;							// ���_�̍���
	g_camera.fHeightR = player->pos.y;					// �����_�̍���
	g_camera.fFront = 15.0f;							// ���f���̑O���̋���
	g_camera.bAutoTurn = false;							// �J�����̉�荞��ON�EOFF
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

	// ���[�J���ϐ��錾
	//Model model = *GetModel();
	Player *player = GetPlayer();

	// ���Z�b�g
	if (GetKeyboardTrigger(KEYINFO_CRESET) == true)
	{
		//g_camera.posV = D3DXVECTOR3(
		//	model.pos.x, 
		//	model.pos.y + 100.0f, 
		//	model.pos.z - 200.0f);							// ���݂̎��_�ʒu
		//g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̎��_�ʒu
		//g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���݂̒����_�ʒu
		//g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̒����_�ʒu
		//g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// ������x�N�g��
		//g_camera.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���

		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̊p�x
		g_camera.fLength = CAMERA_RANGE;				// ���_�E�����_�Ԃ̋���
		g_camera.fHeightV = -60.0f;						// ���_�̍���
		g_camera.fHeightR = 0.0f;						// �����_�̍���
		g_camera.fFront = 15.0f;						// ���f���̑O���̋���
		g_camera.bAutoTurn = false;						// �J�����̉�荞��ON�EOFF
	}

	 //���_�E�����_�̈ړ�
	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_camera.move.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z += cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_camera.move.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_camera.move.x -= cosf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z += sinf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_camera.move.x += cosf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.move.z -= sinf(g_camera.rot.y) * CAMERA_MOVE;
	//}

	 //�����_�̈ړ�(���E)
	//if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y += D3DX_PI * 2.0f;
	//	}
	//}
	//if (GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y -= D3DX_PI * 2.0f;
	//	}
	//}

	// �����_�̈ړ�(�㉺)(T,B�L�[)
	if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	{
		g_camera.fHeightR += CAMERA_MOVE;
	}
	if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	{
		g_camera.fHeightR -= CAMERA_MOVE;
	}

	 //���_�̈ړ�(���E)(Z,C�L�[)
	if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true)
	{
		g_camera.rot.y += CAMERA_TURN;

		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y -= D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}
	if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true)
	{
		g_camera.rot.y -= CAMERA_TURN;

		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2.0f;
		}

		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}


	// ���_�̈ړ�(�㉺)(Y,N�L�[)
	if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true)
	{
		g_camera.fHeightV += CAMERA_MOVE;
	}
	if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true)
	{
		g_camera.fHeightV -= CAMERA_MOVE;
	}

	// �����_�ւ̃Y�[������(U,M�L�[)
	if (GetKeyboardPress(KEYINFO_ZOOMIN) == true && g_camera.fLength >= 100.0f)
	{
		g_camera.fLength -= CAMERA_MOVE;
	}
	if (GetKeyboardPress(KEYINFO_ZOOMOUT) == true && g_camera.fLength <= 300.0f)
	{
		g_camera.fLength += CAMERA_MOVE;
	}
	if (g_camera.fLength > 300.0f)
	{
		g_camera.fLength = 300.0f;
	}
	if (g_camera.fLength < 100.0f)
	{
		g_camera.fLength = 100.0f;
	}

	// ���f���O���̋���
	if (GetKeyboardPress(KEYINFO_FRONT_PLUS) == true && g_camera.fFront <= 25.0f)
	{
		g_camera.fFront += 0.1f;
	}
	if (GetKeyboardPress(KEYINFO_FRONT_MINUS) == true && g_camera.fFront >= 0.0f)
	{
		g_camera.fFront -= 0.1f;
	}
	if (g_camera.fFront > 25.0f)
	{
		g_camera.fFront = 25.0f;
	}
	if (g_camera.fFront < 0.0f)
	{
		g_camera.fFront = 0.0f;
	}

	// 1�������p�x�̏C��
	if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}

	// �ړ��ʂ̌���(����)
	//g_camera.move.x += (0.0f - g_camera.move.x) * 0.4f;
	//g_camera.move.z += (0.0f - g_camera.move.z) * 0.4f;

	// �ړ��ʂ̉��Z
	//g_camera.posV.x += g_camera.move.x;
	//g_camera.posV.z += g_camera.move.z;
	//g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;

	// ���f���̈ʒu�֒����_��u��
	//g_camera.posR.x = model.pos.x;
	//g_camera.posR.z = model.pos.z;
	//g_camera.posV.x = model.pos.x + sinf(g_camera.rot.y) * -g_camera.fLength;
	//g_camera.posV.z = model.pos.z + cosf(g_camera.rot.y) * -g_camera.fLength;
	//g_camera.posV.y = model.pos.y + cosf(g_camera.rot.x) * 200.0f;

	//// �ړI�̒����_
	//g_camera.posRDest.x = model.pos.x - g_camera.fFront * sinf(model.rotDest.y);
	//g_camera.posRDest.z = model.pos.z - g_camera.fFront * cosf(model.rotDest.y);
	//g_camera.posRDest.y = model.pos.y + g_camera.fHeightR;

	//// �ړI�̎��_
	//g_camera.posVDest.x = model.pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posVDest.z = model.pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
	//g_camera.posVDest.y = model.pos.y + cosf(g_camera.rot.x) * g_camera.fLength + g_camera.fHeightV;

	//// �����_�̈ʒu�X�V
	//g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * CAMERA_SPDOWN;
	//g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * CAMERA_SPDOWN;
	//g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * CAMERA_SPDOWN;

	//// ���_�̈ʒu�X�V
	//g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_SPDOWN;
	//g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_SPDOWN;
	//g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * CAMERA_SPDOWN;

	// �ړI�̒����_
	g_camera.posRDest.x = player->pos.x - g_camera.fFront * sinf(player->rotDest.y);
	g_camera.posRDest.z = player->pos.z - g_camera.fFront * cosf(player->rotDest.y);
	g_camera.posRDest.y = player->pos.y + g_camera.fHeightR;

	// �ړI�̎��_
	g_camera.posVDest.x = player->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posVDest.z = player->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
	g_camera.posVDest.y = player->pos.y + cosf(g_camera.rot.x) * g_camera.fLength + g_camera.fHeightV;

	// �����_�̈ʒu�X�V
	g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * CAMERA_SPDOWN;
	g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * CAMERA_SPDOWN;
	g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * CAMERA_SPDOWN;

	// ���_�̈ʒu�X�V
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * CAMERA_SPDOWN;
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * CAMERA_SPDOWN;
	g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * CAMERA_SPDOWN;

	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_camera.moveZVR.x = sinf(g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.moveZVR.z = cosf(g_camera.rot.y) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_camera.moveZVR.x = sinf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//	g_camera.moveZVR.z = cosf(g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveZVR.x = 0.0f;
	//	g_camera.moveZVR.z = 0.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_camera.moveXVR.x = cosf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//	g_camera.moveXVR.z = sinf(-g_camera.rot.y - D3DX_PI) * CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_camera.moveXVR.x = cosf(-g_camera.rot.y) * CAMERA_MOVE;
	//	g_camera.moveXVR.z = sinf(-g_camera.rot.y) * CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveXVR.x = 0.0f;
	//	g_camera.moveXVR.z = 0.0f;
	//}

	//// �����_�̈ړ�(���E)
	//if (GetKeyboardPress(KEYINFO_LEFT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}
	//else if(GetKeyboardPress(KEYINFO_RIGHT_CENTER) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}

	//// �����_�̈ړ�(�㉺)
	//if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	//{
	//	g_camera.moveR.y = CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	//{
	//	g_camera.moveR.y = -CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveR.y = 0.0f;
	//}

	//// ���_�̈ړ�(���E)
	//if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / -CAMERA_TURN;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}
	//else if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true)
	//{
	//	g_camera.rot.y += D3DX_PI / CAMERA_TURN;

	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * CAMERA_RANGE;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * CAMERA_RANGE;
	//}

	//// ���_�̈ړ�(�㉺)
	//if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true)
	//{
	//	g_camera.moveV.y = CAMERA_MOVE;
	//}
	//else if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true)
	//{
	//	g_camera.moveV.y = -CAMERA_MOVE;
	//}
	//else
	//{
	//	g_camera.moveV.y = 0.0f;
	//}

	//if (g_camera.rot.y < -D3DX_PI)
	//{
	//	g_camera.rot.y += D3DX_PI * 2;
	//}
	//else if (g_camera.rot.y > D3DX_PI)
	//{
	//	g_camera.rot.y -= D3DX_PI * 2;
	//}

	//// �ړ��ʂ̉��Z
	//g_camera.posV += g_camera.moveV;
	//g_camera.posR += g_camera.moveR;
	//g_camera.posV += g_camera.moveXVR;
	//g_camera.posR += g_camera.moveXVR;
	//g_camera.posV += g_camera.moveZVR;
	//g_camera.posR += g_camera.moveZVR;
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

//==============================================================================
// �J�����̎擾
//==============================================================================
Camera GetCamera(void)
{
	return g_camera;
}