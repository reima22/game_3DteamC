//==============================================================================
//
// 3D�v���C���[�̕`��kplayer.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "object.h"
#include "math.h"
#include <stdio.h>

//==============================================================================
// �}�N����`
//==============================================================================
//#define MODEL_MOVE	(1.0f)
//#define MODEL_TURN	(0.1f)
#define PLAYER_MOVE		(1.0f)
#define PLAYER_TURN		(0.1f)
#define VTX_MINP		(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// �����_�ŏ��l
#define	VTX_MAXP		(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// �����_�ő�l
//#define MAT_MAX		(3)		// �}�e���A���̍ő吔
//#define TEX_MAX		(3)		// �e�N�X�`���̍ő吔

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================

//LPD3DXMESH g_pMeshPlayer = NULL;						// ���b�V��(���_���)�ւ̃|�C���^
//LPD3DXBUFFER g_pBuffMatPlayer = NULL;					// �}�e���A��(�ގ����)�ւ̃|�C���^
//LPDIRECT3DTEXTURE9 g_apTextureModel[TEX_MAX] = {};	// �e�N�X�`���ւ̃|�C���^
//DWORD g_nNumMatPlayer = 0;							// �}�e���A���̐�
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxPlayer;	// ���f���̊e���W�̍ő�l�E�ŏ��l
Player g_player;							// �v���C���[�̍\����

//==============================================================================
// ����������
//==============================================================================
HRESULT InitPlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	//LoadMotion();

	//for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	//{
	//	// X�t�@�C���̓ǂݍ���
	//	D3DXLoadMeshFromX(
	//		g_player.aModel[nCnt].aFileName,
	//		D3DXMESH_SYSTEMMEM,
	//		pDevice,
	//		NULL,
	//		&g_player.aModel[nCnt].pBuffMatModel,
	//		NULL,
	//		&g_player.aModel[nCnt].nNumMatModel,
	//		&g_player.aModel[nCnt].pMeshModel);
	//}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data/MODEL/00_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMatModel,
		NULL,
		&g_player.aModel[0].nNumMatModel,
		&g_player.aModel[0].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/01_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMatModel,
		NULL,
		&g_player.aModel[1].nNumMatModel,
		&g_player.aModel[1].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/02_arm_top_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[2].pBuffMatModel,
		NULL,
		&g_player.aModel[2].nNumMatModel,
		&g_player.aModel[2].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/03_arm_under_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[3].pBuffMatModel,
		NULL,
		&g_player.aModel[3].nNumMatModel,
		&g_player.aModel[3].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/04_hand_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[4].pBuffMatModel,
		NULL,
		&g_player.aModel[4].nNumMatModel,
		&g_player.aModel[4].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/05_arm_top_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[5].pBuffMatModel,
		NULL,
		&g_player.aModel[5].nNumMatModel,
		&g_player.aModel[5].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/06_arm_under_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[6].pBuffMatModel,
		NULL,
		&g_player.aModel[6].nNumMatModel,
		&g_player.aModel[6].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/07_hand_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[7].pBuffMatModel,
		NULL,
		&g_player.aModel[7].nNumMatModel,
		&g_player.aModel[7].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/08_leg_top_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[8].pBuffMatModel,
		NULL,
		&g_player.aModel[8].nNumMatModel,
		&g_player.aModel[8].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/09_leg_under_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[9].pBuffMatModel,
		NULL,
		&g_player.aModel[9].nNumMatModel,
		&g_player.aModel[9].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/10_foot_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[10].pBuffMatModel,
		NULL,
		&g_player.aModel[10].nNumMatModel,
		&g_player.aModel[10].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/11_leg_top_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[11].pBuffMatModel,
		NULL,
		&g_player.aModel[11].nNumMatModel,
		&g_player.aModel[11].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/12_leg_under_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[12].pBuffMatModel,
		NULL,
		&g_player.aModel[12].nNumMatModel,
		&g_player.aModel[12].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/13_foot_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[13].pBuffMatModel,
		NULL,
		&g_player.aModel[13].nNumMatModel,
		&g_player.aModel[13].pMeshModel);

	g_player.nNumModel = MODEL_PARTS;

	// ���[�J���ϐ��錾
	int nNumVtx;			// ���_��
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

	//D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^
	//						// �}�e���A�����ɑ΂���|�C���^���擾
	//pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	//for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
	//		D3DXCreateTextureFromFile(
	//			pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&g_apTextureModel[nCntMat]);
	//	}
	//}

	// ���_�����擾
	nNumVtx = g_player.aModel[0].pMeshModel->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].pMeshModel->GetFVF());

	// �e�p�[�c�̊K�w�\���ݒ�
	// ��
	g_player.aModel[0].nIdxModelParent = -1;					// �e���f���̃C���f�b�N�X��ݒ�
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ��
	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �E��r
	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-7.5f, 17.5f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �E���r
	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-4.5f, 0.0f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �E��
	g_player.aModel[4].nIdxModelParent = 3;
	g_player.aModel[4].pos = D3DXVECTOR3(-5.5f, 0.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ����r
	g_player.aModel[5].nIdxModelParent = 0;
	g_player.aModel[5].pos = D3DXVECTOR3(7.5f, 17.5f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �����r
	g_player.aModel[6].nIdxModelParent = 5;
	g_player.aModel[6].pos = D3DXVECTOR3(4.5f, 0.0f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ����
	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(5.5f, 0.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �E��
	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �E����
	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -7.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �E��
	g_player.aModel[10].nIdxModelParent = 9;
	g_player.aModel[10].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ����
	g_player.aModel[11].nIdxModelParent = 0;
	g_player.aModel[11].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ������
	g_player.aModel[12].nIdxModelParent = 11;
	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -7.0f, 0.0f);
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ����r
	g_player.aModel[13].nIdxModelParent = 12;
	g_player.aModel[13].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �ϐ��̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.motionType = MOTIONTYPE_NEUTRAL;
	g_player.bLoopMotion = false;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;
	g_vtxMinPlayer = VTX_MINP;
	g_vtxMaxPlayer = VTX_MAXP;

	// �e�̐ݒ�
	g_player.nIdx = SetShadow(D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z), 10.0f, 10.0f);

	// ���_�o�b�t�@�����b�N
	g_player.aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���_���W�̔�r�ƍX�V
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

		// �e���W�̍ő�l�̔�r
		if (g_vtxMaxPlayer.x < vtx.x)
		{			
			g_vtxMaxPlayer.x = vtx.x;
		}			
		if (g_vtxMaxPlayer.y < vtx.y)
		{			
			g_vtxMaxPlayer.y = vtx.y;
		}			
		if (g_vtxMaxPlayer.z < vtx.z)
		{			
			g_vtxMaxPlayer.z = vtx.z;
		}

		// �e���W�̍ŏ��l�̔�r
		if (g_vtxMinPlayer.x > vtx.x)
		{			
			g_vtxMinPlayer.x = vtx.x;
		}			
		if (g_vtxMinPlayer.y > vtx.y)
		{			
			g_vtxMinPlayer.y = vtx.y;
		}			
		if (g_vtxMinPlayer.z > vtx.z)
		{			
			g_vtxMinPlayer.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_player.aModel[0].pMeshModel->UnlockVertexBuffer();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		if (g_player.aModel[nCnt].pMeshModel != NULL)
		{// ���b�V���̔j��
			g_player.aModel[nCnt].pMeshModel->Release();
			g_player.aModel[nCnt].pMeshModel = NULL;
		}
		
		if (g_player.aModel[nCnt].pBuffMatModel != NULL)
		{// �o�b�t�@�̔j��
			g_player.aModel[nCnt].pBuffMatModel->Release();
			g_player.aModel[nCnt].pBuffMatModel = NULL;
		}
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdatePlayer(void)
{
	// �J�����̎擾
	Camera camera = GetCamera();
	//double dSqrt = sqrt(2);		// 2�̕�����

	g_player.posOld = g_player.pos;

	// �ʒu�̃��Z�b�g
	if (GetKeyboardTrigger(KEYINFO_PRESET) == true)
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �e�̔���
	if (GetKeyboardPress(KEYINFO_SHOT) == true)
	{
		SetBullet(
			D3DXVECTOR3(g_player.pos.x + sinf(D3DX_PI - g_player.rot.y) * -10.0f, g_player.pos.y + 50.0f, g_player.pos.z + cosf(D3DX_PI - g_player.rot.y) * 10.0f)
			/*D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 30.0f, g_player.pos.z)*/,
			D3DXVECTOR3(sinf(D3DX_PI - g_player.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - g_player.rot.y) * 5.0f),
			100);
	}

	// ���[�V�����J�E���^�[�̉��Z
	g_player.nCounterMotion++;

	// ���[�V�����̍X�V
	UpdateMotion(g_player.motionType);

	// �ړ��ʂ̉��Z
	g_player.pos += g_player.move;

	// �e�̒Ǐ]
	SetPositionShadow(g_player.nIdx, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));

	// ���f���̈ړ�
	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		g_player.motionType = MOTIONTYPE_MOVE;
		if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// �������
			g_player.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// �E�����
			g_player.move.x += cosf(camera.rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y - (D3DX_PI * 3 / 4);
		}
		else
		{// �����
			g_player.move.x += sinf(camera.rot.y) * PLAYER_MOVE;
			g_player.move.z += cosf(camera.rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		g_player.motionType = MOTIONTYPE_MOVE;
		if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// ��������
			g_player.move.x += cosf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI / 4;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// �E������
			g_player.move.x -= cosf(camera.rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI / -4;
		}
		else
		{// ������
			g_player.move.x += sinf(camera.rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player.move.z += cosf(camera.rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y;
		}
	}
	else if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{// ������
		g_player.move.x -= cosf(camera.rot.y) * PLAYER_MOVE;
		g_player.move.z += sinf(camera.rot.y) * PLAYER_MOVE;
		g_player.rotDest.y = camera.rot.y + (D3DX_PI / 2);
		g_player.motionType = MOTIONTYPE_MOVE;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{// �E����
		g_player.move.x += cosf(camera.rot.y) * PLAYER_MOVE;
		g_player.move.z -= sinf(camera.rot.y) * PLAYER_MOVE;
		g_player.rotDest.y = camera.rot.y + (D3DX_PI / -2);
		g_player.motionType = MOTIONTYPE_MOVE;
	}
	else
	{
		g_player.motionType = MOTIONTYPE_NEUTRAL;
	}

	if (GetKeyboardTrigger(KEYINFO_UP) == true || GetKeyboardTrigger(KEYINFO_DOWN) == true || GetKeyboardTrigger(KEYINFO_RIGHT) == true || GetKeyboardTrigger(KEYINFO_LEFT) == true)
	{
		g_player.nCounterMotion = 0;
		g_player.aModel[0].pos.y = 20.0f;
	}

	if (GetKeyboardRelease(KEYINFO_UP) == true || GetKeyboardRelease(KEYINFO_DOWN) == true || GetKeyboardRelease(KEYINFO_RIGHT) == true || GetKeyboardRelease(KEYINFO_LEFT) == true)
	{
		g_player.nCounterMotion = 0;
		g_player.nKey = 0;
		g_player.aModel[0].pos.y = 20.0f;
		g_player.motionType = MOTIONTYPE_NEUTRAL;
	}

	//	//model.moveZ.x = sinf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//model.moveZ.z = cosf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//model.rot.y = camera.rot.y;
	//	//if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
	//	//{
	//	//	model.moveX.x = cosf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//	model.moveX.z = sinf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//	model.rot.y = camera.rot.y + D3DX_PI / 4;
	//	//	//model.moveX.x /= dSqrt;
	//	//	//model.moveX.z /= dSqrt;
	//	//	//model.moveZ.x /= dSqrt;
	//	//	//model.moveZ.z /= dSqrt;
	//	//}
	//	//else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
	//	//{
	//	//	model.moveX.x = cosf(-camera.rot.y) * MODEL_MOVE;
	//	//	model.moveX.z = sinf(-camera.rot.y) * MODEL_MOVE;
	//	//	model.rot.y = camera.rot.y + D3DX_PI / -4;
	//	//	//model.moveX.x /= dSqrt;
	//	//	//model.moveX.z /= dSqrt;
	//	//	//model.moveZ.x /= dSqrt;
	//	//	//model.moveZ.z /= dSqrt;
	//	//}
	//}

	// ���f���̏㏸�E���~
	if (GetKeyboardPress(KEYINFO_UP_MODEL) == true)
	{
		g_player.move.y = 2;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_MODEL) == true)
	{
		g_player.move.y = -2;
	}
	else
	{
		g_player.move.y = 0;
	}

	// ���f���̐���
	if (GetKeyboardPress(KEYINFO_TURN_LEFT_MODEL) == true)
	{
		g_player.rotDest.y += D3DX_PI / 36;
	}
	if (GetKeyboardPress(KEYINFO_TURN_RIGHT_MODEL) == true)
	{
		g_player.rotDest.y -= D3DX_PI / 36;
	}

	// �ړI�̉�]�p�̏��
	if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	// ������̌�������
	g_player.move.x += (0.0f - g_player.move.x) * SPEEDDOWN;
	g_player.move.z += (0.0f - g_player.move.z) * SPEEDDOWN;

	CollisionVec(&g_player.pos, &g_player.posOld, &g_player.move, g_vtxMaxPlayer.x, g_vtxMinPlayer.x, g_vtxMaxPlayer.z, g_vtxMinPlayer.z, g_vtxMaxPlayer.y, g_vtxMinPlayer.y);
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawPlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// �v���C���[�̌����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// �v���C���[�̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// �e�p�[�c�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel,g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// �e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
			//if (g_player.aModel[nCntModel].nIdxModelParent == 0)
			//{// �e��0�̎�
			//	mtxParent = g_player.aModel[0].mtxWorld;
			//}
			//else if (g_player.aModel[nCntModel].nIdxModelParent != 0)
			//{// �e��0�ȊO�̎�
			//	mtxParent = g_player.aModel[nCntModel - 1].mtxWorld;
			//}
		}
		else
		{
			mtxParent = g_player.mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			// ���f��(�p�[�c)�̕`��
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// ���f���̎擾
//==============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}

//==============================================================================
// ���[�V�����̐ݒ�
//==============================================================================
void SetMotion(MOTIONTYPE motionType)
{
	//g_player.motionType = motionType;

	if (motionType == MOTIONTYPE_NEUTRAL)
	{// �ҋ@���[�V����
		g_player.bLoopMotion = true;	// ���[�v����
		g_player.nNumKey = 2;	// �L�[��
		g_player.aMotionInfo[0].aKeySet[0].nFrame = 40;	// �t���[����

		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotY = -0.25f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotZ = 0.28f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotY = 0.25f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotZ = -0.28f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotZ = 0.0f;
														 
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotX = 0.09f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotX = -0.18f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotX = 0.09f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotX = 0.09f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotZ = 0.0f;
														  
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotX = -0.18f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotZ = 0.0f;
														  
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotX = 0.09f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[0].aKeySet[1].nFrame = 40;	// �t���[����

		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosY = -0.5f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotX = -0.13f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotX = -0.12f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotY = -0.44f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotZ = 0.5f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotY = -0.24f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[4].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotY = 0.44f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotZ = -0.5f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotY = 0.24f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotX = 0.47f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotX = -0.6f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotX = 0.25f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotX = 0.47f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotX = -0.6f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotX = 0.25f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotZ = 0.0f;
	}
	else if (g_player.motionType == MOTIONTYPE_MOVE)
	{// �ړ����[�V����
		g_player.bLoopMotion = true;					// ���[�v����
		g_player.nNumKey = 4;							// �L�[��
		g_player.aMotionInfo[1].aKeySet[0].nFrame = 4;	// �t���[����
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosY = 2.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotX = -0.31f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotY = -0.35f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotX = 0.09f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotY = 0.19f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotZ = 0.09f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotY = 1.67f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotZ = 0.25f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotZ = 0.69f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotY = -1.35f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotZ = -2.39f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotZ = -1.41f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotX = 1.92f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotY = 0.41f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotZ = 0.09f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotX = -0.79f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotX = -0.09f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotX = -1.04f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotY = 0.16f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotZ = 0.15f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotX = -0.34f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotX = -0.03f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[1].nFrame = 12;	// �t���[����
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosY = -0.5f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotX = -0.25f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotY = -0.35f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotX = 0.09f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotY = 0.19f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotZ = 0.09f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotY = 1.79f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotZ = 0.19f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotZ = 0.66f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotX = 0.16f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotY = -1.51f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotZ = -2.61f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotZ = -1.63f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotX = 1.73f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotY = 0.44f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotZ = 0.16f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotX = -0.79f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotX = -0.09f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotX = -0.95f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotY = 0.13f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotZ = 0.19f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotX = -0.34f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotX = -0.03f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].nFrame = 4;	// �t���[����
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosY = 2.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotX = -0.31f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotY = 0.35f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotX = 0.09f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotY = -0.19f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotZ = -0.09f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotX = 0.03f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotY = 1.26f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotZ = 2.73f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotZ = 1.51f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotX = 0.16f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotY = -1.73f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotZ = 0.16f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotY = -0.03f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotZ = -0.82f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotX = -1.04f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotY = -0.16f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotZ = -0.15f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotX = -0.34f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotX = -0.03f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotX = 1.91f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotY = -0.41f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotZ = -0.09f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotX = -0.79f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotX = -0.09f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].nFrame = 12;	// �t���[����
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosY = -0.5f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotX = -0.25f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotY = 0.35f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotX = 0.09f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotY = -0.19f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotZ = -0.09f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotX = 0.09f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotY = 1.38f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotZ = 2.79f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotZ = 0.91f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotX = -0.03f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotY = -1.8f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotZ = -0.47f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotZ = -0.47f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotX = -0.95f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotY = -0.13f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotZ = -0.19f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotX = -0.34f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotX = -0.03f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotX = 1.73f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotY = -0.44f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotZ = -0.16f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotX = -0.79f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotZ = 0.0f;
										
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotX = -0.09f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotZ = 0.0f;
	}
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void UpdateMotion(MOTIONTYPE motionType)
{
	SetMotion(motionType);

	// ���[�J���ϐ��錾
	//D3DXVECTOR3 pos[MAX_KEY][MODEL_PARTS];
	//D3DXVECTOR3 rot[MAX_KEY][MODEL_PARTS];
	//float fFrame[MAX_KEY];
	//float fCntMotion = (float)g_player.nCounterMotion;
	//KEY *pKey = &g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[0];
	//KEY *pKeyDest = &g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[0];
	//KEY *pKeyTop = &g_player.aMotionInfo[motionType].aKeySet[0].aKey[0];

	// �ϐ����
	//for (int nCnt = 0; nCnt < g_player.nNumKey; nCnt++)
	//{
	//	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	//	{
	//		pos[nCnt][nCntModel].x = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fPosX;
	//		pos[nCnt][nCntModel].y = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fPosY;
	//		pos[nCnt][nCntModel].z = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fPosZ;
	//		rot[nCnt][nCntModel].x = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fRotX;
	//		rot[nCnt][nCntModel].y = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fRotY;
	//		rot[nCnt][nCntModel].z = g_player.aMotionInfo[motionType].aKeySet[nCnt].aKey[nCntModel].fRotZ;
	//	}
	//	fFrame[nCnt] = (float)g_player.aMotionInfo[motionType].aKeySet[nCnt].nFrame;
	//}

	for (int nCnt = 0; nCnt < MODEL_PARTS; nCnt++)
	{
		if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			//g_player.aModel[nCnt].rot.x = pKey->fPosX + (pKeyTop->fPosX - pKey->fPosX) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel
			//g_player.aModel[nCnt].rot.x = rot[g_player.nKey][nCnt].x + (rot[0][nCnt].x - rot[g_player.nKey][nCnt].x) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.y = rot[g_player.nKey][nCnt].y + (rot[0][nCnt].y - rot[g_player.nKey][nCnt].y) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.z = rot[g_player.nKey][nCnt].z + (rot[0][nCnt].z - rot[g_player.nKey][nCnt].z) * (fCntMotion / fFrame[g_player.nKey]);
		}
		else
		{
			g_player.aModel[nCnt].pos.x += (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosX) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.y += (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosY) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].pos.z += (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fPosZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fPosZ) / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame;
			g_player.aModel[nCnt].rot.x = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotX - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotX) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.y = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotY - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotY) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			g_player.aModel[nCnt].rot.z = g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ + (g_player.aMotionInfo[motionType].aKeySet[g_player.nKey + 1].aKey[nCnt].fRotZ - g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].aKey[nCnt].fRotZ) * ((float)g_player.nCounterMotion / (float)g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame);
			//g_player.aModel[nCnt].rot.x = rot[g_player.nKey][nCnt].x + (rot[g_player.nKey + 1][nCnt].x - rot[g_player.nKey][nCnt].x) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.y = rot[g_player.nKey][nCnt].y + (rot[g_player.nKey + 1][nCnt].y - rot[g_player.nKey][nCnt].y) * (fCntMotion / fFrame[g_player.nKey]);
			//g_player.aModel[nCnt].rot.z = rot[g_player.nKey][nCnt].z + (rot[g_player.nKey + 1][nCnt].z - rot[g_player.nKey][nCnt].z) * (fCntMotion / fFrame[g_player.nKey]);


			if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == false)
			{
				break;
			}
		}

		if (g_player.nCounterMotion == g_player.aMotionInfo[motionType].aKeySet[g_player.nKey].nFrame)
		{
			g_player.nCounterMotion = 0;

			if (g_player.nKey == g_player.nNumKey - 1 && g_player.bLoopMotion == true)
			{
				g_player.nKey = 0;
			}
			else
			{
				g_player.nKey++;
			}
		}
	}
}

//==============================================================================
// .txt�t�H���_�̓ǂݍ���
//==============================================================================
void LoadMotion(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	//int nNumChar = 80;
	char aBuffer[128];
	char aScript[16] = {};
	char aData[128];			// �ǂݍ��ރf�[�^�̎��
	char cEqual;
	int nCntFile = 0;
	char aCharaData[16];	// ���f���̃f�[�^�̎��
	char aPartsData[8];		// �p�[�c�̃f�[�^���
	int nIdx;				// �C���f�b�N�X
	int nSetPos = 0;
	int nSetRot = 0;

	char aText[128];
	char aTextOld[128] = {};	// �ۑ��p
	char *pText = &aText[0];	// �ǂݎ��p�|�C���^
	int nLength;
	bool bComment = false;		// �R�����g�A�E�g���邩
	char c;

	// �f�[�^�̓ǂݍ���
	pFile = fopen("player_horiai.txt", "r");
	if (pFile != NULL)
	{ //�t�@�C���W�J�\
		while (strcmp("END_SCRIPT",pText) != 0)
		{
			fscanf(pFile, "%s", &aText[0]);

			if (strcmp("#", aTextOld) == 0)
			{
				bComment = true;
				nLength = strlen(aText);

				for (int nCnt = 0; nCnt < nLength + 1; nCnt++)
				{
					c = aText[nCnt];
				}


			}

			if (strncmp("#",&aText[0],1) != 0 || strcmp("#",aTextOld) != 0)
			{

			}


			strcpy(aTextOld, aText);
		}
		//while (fgets(aBuffer, 85, pFile))
		//{
		//	if (aBuffer[0] != '#')
		//	{
		//		while (aScript != "SCRIPT")
		//		{
		//			fscanf(pFile, "%s", &aScript[0]);
		//		}
		//	}
		//}

		//while (aScript[0] != '#')
		//{		
		//	if (aScript != "SCRIPT")
		//	{
		//		for (int nCnt = 0; nCnt < 16; nCnt++)
		//		{
		//			aScript[nCnt] = NULL;
		//		}
		//	}
		//}

		//while (aData != "END_SCRIPT")
		//{
		//	fscanf(pFile, "%s", &aData[0]);
		//	if (aData == "NUM_MODEL")
		//	{
		//		fscanf(pFile,"%c",&cEqual);
		//		fscanf(pFile,"%d",&g_player.nNumModel);
		//	}

		//	if (aData == "MODEL_FILENAME")
		//	{
		//		fscanf(pFile,"%c",&cEqual);
		//		fscanf(pFile, "%s", &g_player.aModel[nCntFile].aFileName[0]);
		//		nCntFile++;
		//	}

		//	if (aData == "CHARACTER_SET")
		//	{				
		//		fscanf(pFile,"%s",&aCharaData[0]);
		//		if (aCharaData == "PARTSSET")
		//		{
		//			fscanf(pFile,"%s",&aPartsData[0]);
		//			if (aPartsData == "INDEX")
		//			{
		//				fscanf(pFile, "%c", &cEqual);
		//				fscanf(pFile, "%d", &nIdx);
		//			}
		//			if (aPartsData == "PARENT")
		//			{
		//				fscanf(pFile, "%c", &cEqual);
		//				fscanf(pFile, "%d", &g_player.aModel[nIdx].nIdxModelParent);
		//			}
		//			if (aPartsData == "POS")
		//			{
		//				fscanf(pFile,"%c",&cEqual);
		//				fscanf(pFile, "%f", &g_player.aModel[nIdx].pos.x);
		//				fscanf(pFile, "%f", &g_player.aModel[nIdx].pos.y);
		//				fscanf(pFile, "%f", &g_player.aModel[nIdx].pos.z);
		//			}
		//			if (aPartsData == "ROT")
		//			{
		//				fscanf(pFile, "%c", &cEqual);
		//				fscanf(pFile, "%f", &g_player.aModel[nIdx].rot.x);
		//				fscanf(pFile, "%f", &g_player.aModel[nIdx].rot.y);
		//				fscanf(pFile, "%f", &g_player.aModel[nIdx].rot.z);
		//			}
		//			if (aPartsData == "END_PARTSSET")
		//			{
		//				break;
		//			}
		//		}
		//	}
		//}
		//for (int nCount = 0; nCount < ; nCount++)
		//{
		//	fscanf(pFile, "%s", );
		//}
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}