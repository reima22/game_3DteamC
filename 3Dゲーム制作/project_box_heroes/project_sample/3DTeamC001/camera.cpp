//==============================================================================
//
// �J�����̐ݒ�kcamera.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "camera.h"
#include "player.h"
#include "gamepad.h"
#include "input.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define CAMERA_MOVE		(5.0f)				// �J�����̈ړ���
#define CAMERA_TURN		(D3DX_PI / 100.0f)	// �J�����̐��񑬓x
#define CAMERA_RANGE	(400.0f)			// ���_�E�����_�Ԃ̋���
#define CAMERA_HEIGHT	(100.0f)			// �J����(���_)�̍���
#define CAMERA_SPDOWN	(0.1f)				// �����W��
#define CAMERA_REMIT_TOP	(100.0f)		// �J�����グ�̍ő�l
#define CAMERA_REMIT_BOTTOM	(-100.0f)		// �J�����~�낵�̍ŏ��l

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
Camera g_camera[CAMERA_MAX];

//==============================================================================
// ����������
//==============================================================================
void InitCamera(void)
{
	
	for (int nCnt = 0; nCnt < CAMERA_MAX; nCnt++)
	{
		CameraInfo(nCnt);
		//InitPlayer();
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
	for (int nCntPlayer = 0; nCntPlayer < CAMERA_MAX; nCntPlayer++)
	{
		MoveCamera(nCntPlayer);
	}
}

//==============================================================================
// �J�����̐ݒ菈��
//==============================================================================
void SetCamera(int nIdx)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �r���[�|�[�g�̐ݒ�
	pDevice->SetViewport(&g_camera[nIdx].viewport);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdx].mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(
		&g_camera[nIdx].mtxProjection,
		D3DXToRadian(45.0f),							// ��p�̐ݒ�
		((float)SCREEN_WIDTH / 2.0f) / (float)SCREEN_HEIGHT,		// ��ʔ䗦�̐ݒ�
		10.0f,											// ��O���E�̕`�拗��
		1500.0f);										// �����E�̕`�拗��

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera[nIdx].mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera[nIdx].mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&g_camera[nIdx].mtxView,
		&g_camera[nIdx].posV,
		&g_camera[nIdx].posR,
		&g_camera[nIdx].vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera[nIdx].mtxView);
}

//==============================================================================
// �J�����̎擾
//==============================================================================
Camera *GetCamera(void)
{
	return &g_camera[0];
}

//==============================================================================
// �J�����̏��
//==============================================================================
void CameraInfo(int nIdx)
{
	// ���[�J���ϐ��錾
	Player *player = GetPlayer();

	player += nIdx;

	switch (nIdx)
	{
	case 0:
		// �\���̂̏�����
		g_camera[nIdx].posV = D3DXVECTOR3(
			player->pos.x,
			player->pos.y + 100.0f,
			player->pos.z - 200.0f);							// �J�������_�̈ʒu
		g_camera[nIdx].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_�ʒu
		g_camera[nIdx].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��
		g_camera[nIdx].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_camera[nIdx].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̊p�x
		g_camera[nIdx].fLength = CAMERA_RANGE;					// ���_�E�����_�Ԃ̋���
		g_camera[nIdx].fHeightV = -60.0f;						// ���_�̍���
		g_camera[nIdx].fHeightR = player->pos.y;				// �����_�̍���
		g_camera[nIdx].fFront = 15.0f;							// ���f���̑O���̋���
		g_camera[nIdx].bAutoTurn = false;						// �J�����̉�荞��ON�EOFF

		g_camera[nIdx].viewport.X = (DWORD)0.0f;				// �`�悷���ʍ���̂w���W
		g_camera[nIdx].viewport.Y = (DWORD)0.0f;				// �`�悷���ʍ���̂x���W
		g_camera[nIdx].viewport.Width = (DWORD)640.0f;			// �`�悷���ʂ̕�
		g_camera[nIdx].viewport.Height = (DWORD)720.0f;			// �`�悷���ʂ̍���
		g_camera[nIdx].viewport.MinZ = 0.0f;
		g_camera[nIdx].viewport.MaxZ = 1.0f;
		break;

	case 1:
		// �\���̂̏�����
		g_camera[nIdx].posV = D3DXVECTOR3(
			player->pos.x,
			player->pos.y + 100.0f,
			player->pos.z - 200.0f);							// �J�������_�̈ʒu
		g_camera[nIdx].posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �����_�ʒu
		g_camera[nIdx].vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// ������x�N�g��
		g_camera[nIdx].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
		g_camera[nIdx].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �J�����̊p�x
		g_camera[nIdx].fLength = CAMERA_RANGE;					// ���_�E�����_�Ԃ̋���
		g_camera[nIdx].fHeightV = -60.0f;						// ���_�̍���
		g_camera[nIdx].fHeightR = player->pos.y;				// �����_�̍���
		g_camera[nIdx].fFront = 15.0f;							// ���f���̑O���̋���
		g_camera[nIdx].bAutoTurn = false;						// �J�����̉�荞��ON�EOFF
		g_camera[nIdx].viewport.X = (DWORD)640.0f;				// �`�悷���ʍ���̂w���W
		g_camera[nIdx].viewport.Y = (DWORD)0.0f;				// �`�悷���ʍ���̂x���W 
		g_camera[nIdx].viewport.Width = (DWORD)640.0f;			// �`�悷���ʂ̕�
		g_camera[nIdx].viewport.Height = (DWORD)720.0f;			// �`�悷���ʂ̍���
		g_camera[nIdx].viewport.MinZ = 0.0f;
		g_camera[nIdx].viewport.MaxZ = 1.0f;

		break;
	default:
		break;
	}
}

// �J�����̑���
void MoveCamera(int nCntPlayer)
{
	// ���[�J���ϐ��錾
	Player *player = GetPlayer();

	player += nCntPlayer;

	// �J�������v���C���[�̔w���
	if (GetKeyboardTrigger(KEYINFO_CAMERA_FRONT) == true || BuDo(KEYINFO::KEYINFO_CAMERA_FRONT,nCntPlayer) == true)
	{
		g_camera[nCntPlayer].rot.y = player->rot.y - D3DX_PI;
	}

	//// �����_�̈ړ�(�㉺)(T,B�L�[)
	//if (GetKeyboardPress(KEYINFO_UP_CENTER) == true)
	//{
	//	g_camera[nCntPlayer].fHeightR += CAMERA_MOVE;
	//}
	//if (GetKeyboardPress(KEYINFO_DOWN_CENTER) == true)
	//{
	//	g_camera[nCntPlayer].fHeightR -= CAMERA_MOVE;
	//}

	//���_�̈ړ�(���E)(Z,C�L�[)
	if (GetKeyboardPress(KEYINFO_LEFT_TURN) == true || BuPu(KEYINFO::KEYINFO_LEFT_TURN,nCntPlayer) == true)
	{
		g_camera[nCntPlayer].rot.y += CAMERA_TURN;

		if (g_camera[nCntPlayer].rot.y > D3DX_PI)
		{
			g_camera[nCntPlayer].rot.y -= D3DX_PI * 2.0f;
		}

		g_camera[nCntPlayer].posV.x = g_camera[nCntPlayer].posR.x - sinf(g_camera[nCntPlayer].rot.y) * g_camera[nCntPlayer].fLength;
		g_camera[nCntPlayer].posV.z = g_camera[nCntPlayer].posR.z - cosf(g_camera[nCntPlayer].rot.y) * g_camera[nCntPlayer].fLength;
	}
	if (GetKeyboardPress(KEYINFO_RIGHT_TURN) == true || BuPu(KEYINFO::KEYINFO_RIGHT_TURN,nCntPlayer) == true)
	{
		g_camera[nCntPlayer].rot.y -= CAMERA_TURN;

		if (g_camera[nCntPlayer].rot.y < -D3DX_PI)
		{
			g_camera[nCntPlayer].rot.y += D3DX_PI * 2.0f;
		}

		g_camera[nCntPlayer].posV.x = g_camera[nCntPlayer].posR.x - sinf(g_camera[nCntPlayer].rot.y) * g_camera[nCntPlayer].fLength;
		g_camera[nCntPlayer].posV.z = g_camera[nCntPlayer].posR.z - cosf(g_camera[nCntPlayer].rot.y) * g_camera[nCntPlayer].fLength;
	}


	// ���_�̈ړ�(�㉺)(Y,N�L�[)
	if (GetKeyboardPress(KEYINFO_UP_SIGHT) == true || BuPu(KEYINFO::KEYINFO_UP_SIGHT,nCntPlayer) == true)
	{
		if (g_camera[nCntPlayer].fHeightR < CAMERA_REMIT_TOP)
		{
			g_camera[nCntPlayer].fHeightR += 2.5f;
		}
	}
	if (GetKeyboardPress(KEYINFO_DOWN_SIGHT) == true || BuPu(KEYINFO::KEYINFO_DOWN_SIGHT,nCntPlayer) == true)
	{
		if (g_camera[nCntPlayer].fHeightR > CAMERA_REMIT_BOTTOM)
		{
			g_camera[nCntPlayer].fHeightR -= 2.5f;
		}
	}

	// 1�������p�x�̏C��
	if (g_camera[nCntPlayer].rot.y < -D3DX_PI)
	{
		g_camera[nCntPlayer].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_camera[nCntPlayer].rot.y > D3DX_PI)
	{
		g_camera[nCntPlayer].rot.y -= D3DX_PI * 2.0f;
	}

	// �ړI�̒����_
	g_camera[nCntPlayer].posRDest.x = player->pos.x - g_camera[nCntPlayer].fFront * sinf(player->rotDest.y);
	g_camera[nCntPlayer].posRDest.z = player->pos.z - g_camera[nCntPlayer].fFront * cosf(player->rotDest.y);
	g_camera[nCntPlayer].posRDest.y = player->pos.y + g_camera[nCntPlayer].fHeightR;

	// �ړI�̎��_
	g_camera[nCntPlayer].posVDest.x = player->pos.x - sinf(g_camera[nCntPlayer].rot.y) * g_camera[nCntPlayer].fLength;
	g_camera[nCntPlayer].posVDest.z = player->pos.z - cosf(g_camera[nCntPlayer].rot.y) * g_camera[nCntPlayer].fLength;
	g_camera[nCntPlayer].posVDest.y = player->pos.y + cosf(g_camera[nCntPlayer].rot.x) * g_camera[nCntPlayer].fLength + g_camera[nCntPlayer].fHeightV;

	// �����_�̈ʒu�X�V
	g_camera[nCntPlayer].posR.x += (g_camera[nCntPlayer].posRDest.x - g_camera[nCntPlayer].posR.x) * CAMERA_SPDOWN;
	g_camera[nCntPlayer].posR.z += (g_camera[nCntPlayer].posRDest.z - g_camera[nCntPlayer].posR.z) * CAMERA_SPDOWN;
	g_camera[nCntPlayer].posR.y += (g_camera[nCntPlayer].posRDest.y - g_camera[nCntPlayer].posR.y) * CAMERA_SPDOWN;
																			   
	// ���_�̈ʒu�X�V														
	g_camera[nCntPlayer].posV.x += (g_camera[nCntPlayer].posVDest.x - g_camera[nCntPlayer].posV.x) * CAMERA_SPDOWN;
	g_camera[nCntPlayer].posV.z += (g_camera[nCntPlayer].posVDest.z - g_camera[nCntPlayer].posV.z) * CAMERA_SPDOWN;
	g_camera[nCntPlayer].posV.y += (g_camera[nCntPlayer].posVDest.y - g_camera[nCntPlayer].posV.y) * CAMERA_SPDOWN;
}