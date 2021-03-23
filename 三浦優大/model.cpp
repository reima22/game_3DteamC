//================================================
//
//���f������[model.h]
// Author; miura yuudai
//
//================================================

#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "math.h"
#include "stone.h"
#include <stdio.h>
#include "Billboard.h"
#include "enemy.h"
#include "gamepad.h"
#include "wall.h"
#include "item.h"

//==============================================================================
// �}�N����`
//==============================================================================
//#define MODEL_MOVE	(1.0f)
//#define MODEL_TURN	(0.1f)
#define PLAYER_MOVE		(5.65f)
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
Player g_player;							// �v���C���[�̍\����

//==============================================================================
// ����������
//==============================================================================
HRESULT InitModel(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�̎擾

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

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/bodymiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[0].pBuffMatModel, NULL, &g_player.aModel[0].nNumMatModel, &g_player.aModel[0].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/atamamiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[1].pBuffMatModel, NULL, &g_player.aModel[1].nNumMatModel, &g_player.aModel[1].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/armmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[2].pBuffMatModel, NULL, &g_player.aModel[2].nNumMatModel, &g_player.aModel[2].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/arm2miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[3].pBuffMatModel, NULL, &g_player.aModel[3].nNumMatModel, &g_player.aModel[3].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/handmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[4].pBuffMatModel, NULL, &g_player.aModel[4].nNumMatModel, &g_player.aModel[4].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/udemiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[5].pBuffMatModel, NULL, &g_player.aModel[5].nNumMatModel, &g_player.aModel[5].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/arm3miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[6].pBuffMatModel, NULL, &g_player.aModel[6].nNumMatModel, &g_player.aModel[6].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/handRmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[7].pBuffMatModel, NULL, &g_player.aModel[7].nNumMatModel, &g_player.aModel[7].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/legRmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[8].pBuffMatModel, NULL, &g_player.aModel[8].nNumMatModel, &g_player.aModel[8].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/footmiuraL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[9].pBuffMatModel, NULL, &g_player.aModel[9].nNumMatModel, &g_player.aModel[9].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/leg2miuraR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[10].pBuffMatModel, NULL, &g_player.aModel[10].nNumMatModel, &g_player.aModel[10].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/legmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[11].pBuffMatModel, NULL, &g_player.aModel[11].nNumMatModel, &g_player.aModel[11].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/footmiura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[12].pBuffMatModel, NULL, &g_player.aModel[12].nNumMatModel, &g_player.aModel[12].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/leg2miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[13].pBuffMatModel, NULL, &g_player.aModel[13].nNumMatModel, &g_player.aModel[13].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/body2miura.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[14].pBuffMatModel, NULL, &g_player.aModel[14].nNumMatModel, &g_player.aModel[14].pMeshModel);
	D3DXLoadMeshFromX("data/MODEL/gun.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[15].pBuffMatModel, NULL, &g_player.aModel[15].nNumMatModel, &g_player.aModel[15].pMeshModel);

	g_player.nNumModel = MODEL_PARTS;

	// ���[�J���ϐ��錾
	int nNumVtx;			// ���_��
	DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

	D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_player.aModel[0].pBuffMatModel->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)g_player.nNumModel; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
	//		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/body_d.tga",&g_player.aModel[0].pTextureModel);
	//	}
	//}

	// ���_�����擾
	nNumVtx = g_player.aModel[0].pMeshModel->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].pMeshModel->GetFVF());

	//�e�p�[�c�̊K�w�\���ݒ�
	g_player.aModel[0].nIdxModelParent = -1;//�e�̃C���f�b�N�X��ݒ� //��
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);//�ʒu�̐ݒ�
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[1].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ�@//��
	g_player.aModel[1].pos = D3DXVECTOR3(-1.0f, 57.0f, -4.0f);//�ʒu�̐ݒ�
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[2].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ� //�E�r
	g_player.aModel[2].pos = D3DXVECTOR3(-10.5f, 50.5f, 0.0f);//�ʒu�̐ݒ�
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[3].nIdxModelParent = 2;//�e�̃C���f�b�N�X��ݒ�@//�E��
	g_player.aModel[3].pos = D3DXVECTOR3(-8.0f, -18.0f, -2.5f);//�����̐ݒ�
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[4].nIdxModelParent = 3;//�e�̃C���f�b�N�X��ݒ� //���r
	g_player.aModel[4].pos = D3DXVECTOR3(-5.0f, -29.0f, 3.0f);//�ʒu�̐ݒ�
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[5].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ�@//����
	g_player.aModel[5].pos = D3DXVECTOR3(8.5f, 50.5f, 0.0f);//�ʒu�̐ݒ�
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

	g_player.aModel[6].nIdxModelParent = 5;//�e�̃C���f�b�N�X��ݒ�@//�E��
	g_player.aModel[6].pos = D3DXVECTOR3(8.0f, -18.0f, 0.0f);//�ʒu�̐ݒ�
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[7].nIdxModelParent = 6;//�e�̃C���f�b�N�X��ݒ�@//�E��
	g_player.aModel[7].pos = D3DXVECTOR3(5.0f, -29.0f, 3.0f);//�ʒu�̐ݒ�
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

	g_player.aModel[8].nIdxModelParent = 14;//�e�̃C���f�b�N�X��ݒ� //����
	g_player.aModel[8].pos = D3DXVECTOR3(0.0f, 4.0f, 4.0f);//�ʒu�̐ݒ�
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[9].nIdxModelParent = 11;//�e�̃C���f�b�N�X��ݒ�@//����
	g_player.aModel[9].pos = D3DXVECTOR3(3.0f, -32.0f, -4.0f);//�ʒu�̐ݒ�
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[10].nIdxModelParent = 9;//�e�̃C���f�b�N�X��ݒ�@//�E�I
	g_player.aModel[10].pos = D3DXVECTOR3(6.0f, -36.0f, 1.0f);//�ʒu�̐ݒ�
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[11].nIdxModelParent = 14;//�e�̃C���f�b�N�X��ݒ�@//���I
	g_player.aModel[11].pos = D3DXVECTOR3(-2.0f, 6.0f, 4.0f);//�ʒu�̐ݒ�
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[12].nIdxModelParent = 8;//�e�̃C���f�b�N�X��ݒ�@//�E�G
	g_player.aModel[12].pos = D3DXVECTOR3(-4.0f, -30.0f, -5.0f);//�ʒu�̐ݒ�
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�
	
	g_player.aModel[13].nIdxModelParent = 12;//�e�̃C���f�b�N�X��ݒ�@//���G
	g_player.aModel[13].pos = D3DXVECTOR3(-4.0f, -36.0f, 0.0f);//�ʒu�̐ݒ�
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

	g_player.aModel[14].nIdxModelParent = 0;//�e�̃C���f�b�N�X��ݒ�@//��
	g_player.aModel[14].pos = D3DXVECTOR3(0.0f, 2.0f, 0.0f);//�ʒu�̐ݒ�
	g_player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�

	g_player.aModel[15].nIdxModelParent = 4;//�e�̃C���f�b�N�X��ݒ�@//�e
	g_player.aModel[15].pos = D3DXVECTOR3(0.0f, -15.0f, -3.0f);//�ʒu�̐ݒ�
	g_player.aModel[15].rot = D3DXVECTOR3(0.0f, 1.45f, -0.75f);//�����̐ݒ�

	g_player.aModel[16].nIdxModelParent = 4;//�e�̃C���f�b�N�X��ݒ�@//�����`���[
	g_player.aModel[16].pos = D3DXVECTOR3(5.0f, -20.0f, -15.0f);//�ʒu�̐ݒ�
	g_player.aModel[16].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̐ݒ�


	// �ϐ��̏�����
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
	g_player.bLoopMotion = false;
	g_player.nNumKey = 0;
	g_player.nKey = 0;
	g_player.nCounterMotion = 0;
	g_player.g_vtxMinPlayer = VTX_MINP;
	g_player.g_vtxMaxPlayer = VTX_MAXP;
	g_player.state = PLAYERSTATE_NOMAL;

	// �e�̐ݒ�
	g_player.nIdx = SetShadow(D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z), 10.0f, 10.0f);

	// ���_�o�b�t�@�����b�N
	g_player.aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���_���W�̔�r�ƍX�V
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

		// �e���W�̍ő�l�̔�r
		if (g_player.g_vtxMaxPlayer.x < vtx.x)
		{
			g_player.g_vtxMaxPlayer.x = vtx.x;
		}
		if (g_player.g_vtxMaxPlayer.y < vtx.y)
		{
			g_player.g_vtxMaxPlayer.y = vtx.y;
		}
		if (g_player.g_vtxMaxPlayer.z < vtx.z)
		{
			g_player.g_vtxMaxPlayer.z = vtx.z;
		}

		// �e���W�̍ŏ��l�̔�r
		if (g_player.g_vtxMinPlayer.x > vtx.x)
		{
			g_player.g_vtxMinPlayer.x = vtx.x;
		}
		if (g_player.g_vtxMinPlayer.y > vtx.y)
		{
			g_player.g_vtxMinPlayer.y = vtx.y;
		}
		if (g_player.g_vtxMinPlayer.z > vtx.z)
		{
			g_player.g_vtxMinPlayer.z = vtx.z;
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
void UninitModel(void)
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
void UpdateModel(void)
{
	// �J�����̎擾
	Camera camera = GetCamera();
	//double dSqrt = sqrt(2);		// 2�̕�����

	g_player.posOld = g_player.pos;

	// ���[�V�����J�E���^�[�̉��Z
	g_player.nCounterMotion++;

	// ���[�V�����̍X�V
	UpdateMotion(g_player.motionType);

	// �ړ��ʂ̉��Z
	g_player.pos += g_player.move;

	// �e�̒Ǐ]
	SetPositionShadow(g_player.nIdx, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));

	D3DXVECTOR3 pos;
	int nLife;
	D3DXVECTOR3 move;
	float fAngle;

	pos = D3DXVECTOR3(g_player.aModel[2].mtxWorld._41,
		g_player.aModel[2].mtxWorld._42,
		g_player.aModel[2].mtxWorld._43);//�ʒu

	nLife = 20;//�����������_��
	fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
	move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
	move.y = 0.5f;//y���̒e�̑��x
	move.z = cosf(fAngle)*2.5f;//y���̒e�̑��x
	SetBillboard(pos, nLife, move, 0);//�G�t�F�N�g����

	if (g_player.state == PLAYERSTATE_NOMAL)
	{
		// ���f���̈ړ�
		if (IsButtonPush(KEYINFO_UP))
			//if (GetKeyboardPress(DIK_UP) == true)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
			if (IsButtonPush(KEYINFO_LEFT) == true)
			{// �������
				g_player.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
				g_player.move.z += sinf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
				g_player.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
			}
			else if (IsButtonPush(KEYINFO_RIGHT) == true)
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
		else if (IsButtonPush(KEYINFO_DOWN) == true)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
			if (IsButtonPush(KEYINFO_LEFT) == true)
			{// ��������
				g_player.move.x += cosf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
				g_player.move.z -= sinf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
				g_player.rotDest.y = camera.rot.y + D3DX_PI / 4;
			}
			else if (IsButtonPush(KEYINFO_RIGHT) == true)
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
		else if (IsButtonPush(KEYINFO_LEFT) == true)
		{// ������
			g_player.move.x -= cosf(camera.rot.y) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + (D3DX_PI / 2);
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}
		else if (IsButtonPush(KEYINFO_RIGHT) == true)
		{// �E����
			g_player.move.x += cosf(camera.rot.y) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + (D3DX_PI / -2);
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}
		else
		{
			g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		// ���f���̈ړ�
		if (GetKeyboardPress(DIK_UP) == true)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
			if (GetKeyboardPress(DIK_LEFT) == true)
			{// �������
				g_player.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
				g_player.move.z += sinf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
				g_player.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
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
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{
			g_player.motionType = MOTIONTYPE_MODELMOVE;
			if (GetKeyboardPress(DIK_LEFT) == true)
			{// ��������
				g_player.move.x += cosf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
				g_player.move.z -= sinf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
				g_player.rotDest.y = camera.rot.y + D3DX_PI / 4;
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
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
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{// ������
			g_player.move.x -= cosf(camera.rot.y) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + (D3DX_PI / 2);
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}
		else if (GetKeyboardPress(DIK_RIGHT) == true)
		{// �E����
			g_player.move.x += cosf(camera.rot.y) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + (D3DX_PI / -2);
			g_player.motionType = MOTIONTYPE_MODELMOVE;
		}
		else
		{
			g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.aModel[0].pos.y = 70.0f;
		}

		if (GetKeyboardRelease(DIK_UP) == true || GetKeyboardRelease(DIK_DOWN) == true || GetKeyboardRelease(DIK_RIGHT) == true || GetKeyboardRelease(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.nKey = 0;
			g_player.aModel[0].pos.y = 70.0f;
			g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		if (IsButtonPush(KEYINFO_A) == true)
		{
			g_player.motionType = MOTIONTYPE_MODELACTION;

			//// �e�̔���
			//if (IsButtonPush(KEYINFO_B) == true)
			//{
			//	SetBullet(
			//		D3DXVECTOR3(g_player.pos.x + sinf(D3DX_PI - g_player.rot.y) * -10.0f, g_player.pos.y, g_player.pos.z - 70 + cosf(D3DX_PI - g_player.rot.y) * 10.0f)
			//		/*D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 30.0f, g_player.pos.z)*/,
			//		D3DXVECTOR3(sinf(D3DX_PI - g_player.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - g_player.rot.y) * 5.0f),
			//		100);
			//}
		}

		if (IsButtonDown(KEYINFO_UP) == true || IsButtonDown(KEYINFO_DOWN) == true || IsButtonDown(KEYINFO_RIGHT) == true || IsButtonDown(KEYINFO_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.aModel[0].pos.y = 75.0f;
			//g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		if (IsButtonUp(KEYINFO_UP) == true || IsButtonUp(KEYINFO_DOWN) == true || IsButtonUp(KEYINFO_RIGHT) == true || IsButtonUp(KEYINFO_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.nKey = 0;
			g_player.aModel[0].pos.y = 75.0f;
			g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		int Itemgun;
		Itemgun = Releaseitem();
		int Itemnaihu;
		Itemnaihu = Releaseitemm();
		// ���[�J���ϐ��錾
		LPDIRECT3DDEVICE9 pDevice = GetDevice();// �f�o�C�X�̎擾

		if (Itemgun == 1)
		{
			D3DXLoadMeshFromX("data/MODEL/gun.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[15].pBuffMatModel, NULL, &g_player.aModel[15].nNumMatModel, &g_player.aModel[15].pMeshModel);
			g_player.state = PLAYERSTATE_GUN;
		}

		if (Itemnaihu == 3)
		{
			D3DXLoadMeshFromX("data/MODEL/rancher.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_player.aModel[16].pBuffMatModel, NULL, &g_player.aModel[16].nNumMatModel, &g_player.aModel[16].pMeshModel);
		}

		// �e�̔���
		if (GetKeyboardPress(DIK_A) == true)
		{
			SetBullet(
				D3DXVECTOR3(g_player.pos.x + g_player.aModel[0].pos.x + g_player.aModel[2].pos.x + g_player.aModel[3].pos.x + sinf(D3DX_PI - g_player.rot.y) * -10.0f, g_player.pos.y + g_player.aModel[0].pos.y + g_player.aModel[2].pos.y + g_player.aModel[3].pos.y, g_player.pos.z + g_player.aModel[0].pos.z + g_player.aModel[2].pos.z + g_player.aModel[3].pos.z + cosf(D3DX_PI - g_player.rot.y) * 10.0f)
				/*D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 30.0f, g_player.pos.z)*/,
				D3DXVECTOR3(sinf(D3DX_PI - g_player.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - g_player.rot.y) * 5.0f),
				100);
		}

		if (GetKeyboardPress(DIK_Q) == true)
		{
			g_player.motionType = MOTIONTYPE_MODELACTION;;
		}

		//if (GetKeyboardTrigger(DIK_A) == true)
		//{
		//	g_player.nCounterMotion = 0;
		//	//g_player.aModel[0].rot.y = 2.15f;
		//}

		//if (GetKeyboardRelease(DIK_A) == true)
		//{
		//	g_player.nCounterMotion = 0;
		//	g_player.nKey = 0;
		//	//g_player.aModel[0].rot.y = 2.15f;
		//	g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		//}

		//for (int nCntMat = 0; nCntMat < 46; nCntMat++)
		//{
		//	D3DXVECTOR3 pos;
		//	int nLife;
		//	D3DXVECTOR3 move;
		//	float fAngle;

		//	pos = D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 105, g_player.pos.z);//�ʒu
		//	nLife = 15 + rand() % 20;//�����������_��
		//	fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
		//	move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
		//	move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
		//	move.z = cosf(fAngle)*2.5f;//y���̒e�̑��x
		//	SetBillboard(pos, nLife, move, 1);//�G�t�F�N�g����
		//}
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
		if (GetKeyboardPress(DIK_T) == true)
		{
			g_player.move.y = 2;
		}
		else if (GetKeyboardPress(DIK_X) == true)
		{
			g_player.move.y = -2;
		}
		else
		{
			g_player.move.y = 0;
		}

		// ���f���̐���
		if (GetKeyboardPress(DIK_K) == true)
		{
			g_player.rotDest.y += D3DX_PI / 36;
		}
		if (GetKeyboardPress(DIK_L) == true)
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
		g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
		g_player.move.z += (0.0f - g_player.move.z) * 0.5f;

		CollisionVec(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
		CollisionVecItem(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
		//CollisionVecSord(&g_player.pos, &g_player.posOld, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
		CollisionVecWall(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
	}

	else if (g_player.state == PLAYERSTATE_GUN)
	{
			// ���f���̈ړ�
			if (GetKeyboardPress(DIK_UP) == true)
			{
				g_player.motionType = MOTIONTYPE_MODELMOVE;

				if (GetKeyboardPress(DIK_LEFT) == true)
				{// �������
					g_player.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
					g_player.move.z += sinf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
					g_player.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
				}
				else if (GetKeyboardPress(DIK_RIGHT) == true)
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
			else if (GetKeyboardPress(DIK_DOWN) == true)
			{
				g_player.motionType = MOTIONTYPE_MODELMOVE;
				if (GetKeyboardPress(DIK_LEFT) == true)
				{// ��������
					g_player.move.x += cosf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
					g_player.move.z -= sinf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
					g_player.rotDest.y = camera.rot.y + D3DX_PI / 4;
				}
				else if (GetKeyboardPress(DIK_RIGHT) == true)
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
			else if (GetKeyboardPress(DIK_LEFT) == true)
			{// ������
				g_player.move.x -= cosf(camera.rot.y) * PLAYER_MOVE;
				g_player.move.z += sinf(camera.rot.y) * PLAYER_MOVE;
				g_player.rotDest.y = camera.rot.y + (D3DX_PI / 2);
				g_player.motionType = MOTIONTYPE_MODELMOVE;
			}
			else if (GetKeyboardPress(DIK_RIGHT) == true)
			{// �E����
				g_player.move.x += cosf(camera.rot.y) * PLAYER_MOVE;
				g_player.move.z -= sinf(camera.rot.y) * PLAYER_MOVE;
				g_player.rotDest.y = camera.rot.y + (D3DX_PI / -2);
				g_player.motionType = MOTIONTYPE_MODELMOVE;
			}
			else
			{
				g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
			}

			if (GetKeyboardPress(DIK_Q) == true)
			{
				g_player.motionType = MOTIONTYPE_MODELACTION;
			}


		if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_RIGHT) == true || GetKeyboardTrigger(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.aModel[0].pos.y = 70.0f;
		}

		if (GetKeyboardRelease(DIK_UP) == true || GetKeyboardRelease(DIK_DOWN) == true || GetKeyboardRelease(DIK_RIGHT) == true || GetKeyboardRelease(DIK_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.nKey = 0;
			g_player.aModel[0].pos.y = 70.0f;
			g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		if (IsButtonPush(KEYINFO_A) == true)
		{
			g_player.motionType = MOTIONTYPE_MODELACTION;

			// �e�̔���
			if (IsButtonPush(KEYINFO_B) == true)
			{
				SetBullet(
					D3DXVECTOR3(g_player.pos.x + sinf(D3DX_PI - g_player.rot.y) * -10.0f, g_player.pos.y + 130, g_player.pos.z - 70 + cosf(D3DX_PI - g_player.rot.y) * 10.0f)
					/*D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 30.0f, g_player.pos.z)*/,
					D3DXVECTOR3(sinf(D3DX_PI - g_player.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - g_player.rot.y) * 5.0f),
					100);
			}
		}

		if (IsButtonDown(KEYINFO_UP) == true || IsButtonDown(KEYINFO_DOWN) == true || IsButtonDown(KEYINFO_RIGHT) == true || IsButtonDown(KEYINFO_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.aModel[0].pos.y = 75.0f;
			//g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		if (IsButtonUp(KEYINFO_UP) == true || IsButtonUp(KEYINFO_DOWN) == true || IsButtonUp(KEYINFO_RIGHT) == true || IsButtonUp(KEYINFO_LEFT) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.nKey = 0;
			g_player.aModel[0].pos.y = 75.0f;
			g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		if (GetKeyboardTrigger(DIK_Q) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.aModel[0].pos.y = 80.0f;
		}

		if (GetKeyboardRelease(DIK_Q) == true)
		{
			g_player.nCounterMotion = 0;
			g_player.nKey = 0;
			g_player.aModel[0].pos.y = 80.0f;
			g_player.motionType = MOTIONTYPE_MODELNEUTRAL;
		}

		// ���f���̏㏸�E���~
		if (GetKeyboardPress(DIK_T) == true)
		{
			g_player.move.y = 2;
		}
		else if (GetKeyboardPress(DIK_X) == true)
		{
			g_player.move.y = -2;
		}
		else
		{
			g_player.move.y = 0;
		}

		// ���f���̐���
		if (GetKeyboardPress(DIK_K) == true)
		{
			g_player.rotDest.y += D3DX_PI / 36;
		}
		if (GetKeyboardPress(DIK_L) == true)
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
		g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
		g_player.move.z += (0.0f - g_player.move.z) * 0.5f;

		CollisionVec(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
		CollisionVecItem(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
		//CollisionVecSord(&g_player.pos, &g_player.posOld, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
		CollisionVecWall(&g_player.pos, &g_player.posOld, &g_player.move, g_player.g_vtxMaxPlayer.x, g_player.g_vtxMinPlayer.x, g_player.g_vtxMaxPlayer.z, g_player.g_vtxMinPlayer.z, g_player.g_vtxMaxPlayer.y, g_player.g_vtxMinPlayer.y);
	}

}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawModel(void)
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
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// �e�p�[�c�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
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
		pMat = (D3DXMATERIAL*)g_player.aModel[0].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_player.aModel[0].pTextureModel);

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
Player *GetModel(void)
{
	return &g_player;
}

//==============================================================================
// ���[�V�����̐ݒ�
//==============================================================================
void SetMotion(MOTIONMODELTYPE motionType)
{
	//g_player.motionType = motionType;

	if (motionType == MOTIONTYPE_MODELNEUTRAL)
	{// �ҋ@���[�V����
		g_player.bLoopMotion = true;	// ���[�v����
		g_player.nNumKey = 2;	// �L�[��
		g_player.aMotionInfo[0].aKeySet[0].nFrame = 40;	// �t���[����

		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosY = -0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fPosZ = -0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[0].fRotX = -0.0f;
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
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[2].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[3].fRotY = -0.0f;
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
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[5].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[6].fRotZ = -0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[7].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[8].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[9].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[10].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[11].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[12].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[13].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[14].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[0].aKeySet[0].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[15].fPosY = -20.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[15].fPosZ = -3.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[15].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[15].fRotY = 1.45f;
		g_player.aMotionInfo[0].aKeySet[0].aKey[15].fRotZ = -0.75f;

		g_player.aMotionInfo[0].aKeySet[1].nFrame = 8;	// �t���[����

		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosY = -0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fPosZ = -0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[0].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[1].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[2].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[3].fRotY = -0.0f;
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
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[5].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[6].fRotZ = -0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[7].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[8].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[9].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[10].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[11].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotX = -0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[12].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[13].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fRotY = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[14].fRotZ = 0.0f;
										
		g_player.aMotionInfo[0].aKeySet[1].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[15].fPosY = -20.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[15].fPosZ = -3.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[15].fRotX = 0.0f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[15].fRotY = 1.45f;
		g_player.aMotionInfo[0].aKeySet[1].aKey[15].fRotZ = -0.75f;
	}
	else if (g_player.motionType == MOTIONTYPE_MODELMOVE)
	{// �ړ����[�V����
		g_player.bLoopMotion = true;					// ���[�v����
		g_player.nNumKey = 4;							// �L�[��
		g_player.aMotionInfo[1].aKeySet[0].nFrame = 8;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosY = -7.20f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotX = -0.22f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotY = 0.25f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[0].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotY = -0.19f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[1].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotX = -1.29f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[2].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotX = 1.29f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[3].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[4].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotX = 0.50f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[5].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotX = 1.01f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[6].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[7].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotX = 1.17f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[8].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotX = -0.85f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[9].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[10].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotX = -0.44f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[11].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotX = -0.44f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[12].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[13].fRotZ = 0.0f;
							 			
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fRotY = -0.31f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[14].fRotZ = 0.03f;

		g_player.aMotionInfo[1].aKeySet[0].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[15].fPosY = -20.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[15].fPosZ = -3.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[15].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[15].fRotY = 1.45f;
		g_player.aMotionInfo[1].aKeySet[0].aKey[15].fRotZ = -0.75f;

		g_player.aMotionInfo[1].aKeySet[1].nFrame = 10;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosY = -19.10f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotX = -0.22f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotY = 0.25f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotY = -0.19f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotX = -0.54f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotX = 1.29f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[3].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[5].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotX = 1.54f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[6].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[7].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotX = 1.13f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[8].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotX = -1.82f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotX = 0.41f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[11].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotX = -1.32f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotX = 0.41f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fRotY = -0.31f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[14].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[1].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[15].fPosY = -20.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[15].fPosZ = -3.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[15].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[15].fRotY = 1.45f;
		g_player.aMotionInfo[1].aKeySet[1].aKey[15].fRotZ = -0.75f;

		g_player.aMotionInfo[1].aKeySet[2].nFrame = 8;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosY = -10.90f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotX = -0.22f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotY = -0.25f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotX = 0.57f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotX = 0.88f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[3].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotX = -0.91f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[5].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotX = 1.01f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[6].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[7].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotX = -0.57f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[8].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotX = -0.47f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotX = 1.23f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[11].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotX = -0.50f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fRotY = 0.35f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[14].fRotZ = 0.06f;

		g_player.aMotionInfo[1].aKeySet[2].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[15].fPosY = -20.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[15].fPosZ = -3.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[15].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[15].fRotY = 1.45f;
		g_player.aMotionInfo[1].aKeySet[2].aKey[15].fRotZ = -0.75f;


		g_player.aMotionInfo[1].aKeySet[3].nFrame = 10;	// �t���[����

		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosY = -18.20f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotX = -0.22f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotY = -0.25f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotX = 0.03f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[2].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotX = 0.88f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[3].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotX = -0.44f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[5].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotX = 1.01f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[6].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[7].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotX = 0.16f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[8].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotX = -1.13f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[9].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotX = 0.38f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotX = 1.04f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[11].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotX = -1.73f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fRotY = 0.35f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[14].fRotZ = 0.0f;

		g_player.aMotionInfo[1].aKeySet[3].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[15].fPosY = -20.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[15].fPosZ = -3.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[15].fRotX = 0.0f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[15].fRotY = 1.45f;
		g_player.aMotionInfo[1].aKeySet[3].aKey[15].fRotZ = -0.75f;
	}

	else if (g_player.motionType == MOTIONTYPE_MODELACTION)
	{// �ړ����[�V����
		g_player.bLoopMotion = true;					// ���[�v����
		g_player.nNumKey = 2;							// �L�[��
		g_player.aMotionInfo[2].aKeySet[0].nFrame = 15;	// �t���[����

		g_player.aMotionInfo[2].aKeySet[0].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[0].fPosY = -14.70f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[0].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[0].fRotY = 0.47f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[0].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[1].fRotY = -0.35f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[1].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[2].fRotX = 1.45f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[2].fRotY = -0.75f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[2].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[3].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[4].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[5].fRotX = 0.38f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[5].fRotY = 0.06f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[5].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[6].fRotX = 1.26f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[6].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[7].fRotX = -0.16f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[7].fRotY = -0.09f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[7].fRotZ = -0.06f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[8].fRotX = -0.31f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[8].fRotZ = 0.06f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[9].fRotX = -0.60f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[9].fRotY = 0.06f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[9].fRotZ = -0.06f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[10].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[10].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[11].fRotX = 0.57f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[11].fRotY = 0.09f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[11].fRotZ = -0.06f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[12].fRotX = -0.31f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[12].fRotY = -0.16f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[12].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[13].fRotX = 0.35f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[13].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[14].fRotY = -0.50f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[14].fRotZ = 0.0f;
							 
		g_player.aMotionInfo[2].aKeySet[0].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[15].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[15].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[15].fRotX = 0.25f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[15].fRotY = 1.60f;
		g_player.aMotionInfo[2].aKeySet[0].aKey[15].fRotZ = -1.41f;


		g_player.aMotionInfo[2].aKeySet[1].nFrame = 15;	// �t���[����

		g_player.aMotionInfo[2].aKeySet[1].aKey[0].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[0].fPosY = -14.70f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[0].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[0].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[0].fRotY = 0.47f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[0].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[1].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[1].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[1].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[1].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[1].fRotY = -0.35f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[1].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[2].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[2].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[2].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[2].fRotX = 1.45f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[2].fRotY = -0.75f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[2].fRotZ = -0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[3].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[3].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[3].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[3].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[3].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[3].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[4].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[4].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[4].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[4].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[4].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[4].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[5].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[5].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[5].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[5].fRotX = 0.38f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[5].fRotY = 0.06f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[5].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[6].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[6].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[6].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[6].fRotX = 1.26f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[6].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[6].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[7].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[7].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[7].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[7].fRotX = -0.16f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[7].fRotY = -0.09f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[7].fRotZ = -0.06f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[8].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[8].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[8].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[8].fRotX = -0.31f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[8].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[8].fRotZ = 0.06f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[9].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[9].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[9].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[9].fRotX = -0.60f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[9].fRotY = 0.06f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[9].fRotZ = -0.06f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[10].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[10].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[10].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[10].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[10].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[10].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[11].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[11].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[11].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[11].fRotX = 0.57f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[11].fRotY = 0.09f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[11].fRotZ = -0.06f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[12].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[12].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[12].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[12].fRotX = -0.31f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[12].fRotY = -0.16f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[12].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[13].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[13].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[13].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[13].fRotX = 0.35f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[13].fRotY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[13].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[14].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[14].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[14].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[14].fRotX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[14].fRotY = -0.50f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[14].fRotZ = 0.0f;

		g_player.aMotionInfo[2].aKeySet[1].aKey[15].fPosX = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[15].fPosY = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[15].fPosZ = 0.0f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[15].fRotX = 0.25f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[15].fRotY = 1.60f;
		g_player.aMotionInfo[2].aKeySet[1].aKey[15].fRotZ = -1.41f;
	}
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void UpdateMotion(MOTIONMODELTYPE motionType)
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

////==============================================================================
//// �O�ς𗘗p���������蔻��
////==============================================================================
//bool CollisionVecEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
//{
//	bool bLand = false;
//
//	D3DXVECTOR3 pos = *pPos;// ����Ώۂ̈ʒu
//
//	ENEMYPLAYER	*pPlayer;
//	pPlayer = GetEnemy();
//
//	//aPos�̒l�ݒ�
//	g_player.aPos[0] = D3DXVECTOR3(g_player.pos.x + g_player.g_vtxMinPlayer.x, 0.0f, g_player.pos.z + g_player.g_vtxMinPlayer.z);
//	g_player.aPos[1] = D3DXVECTOR3(g_player.pos.x + g_player.g_vtxMinPlayer.x, 0.0f, g_player.pos.z + g_player.g_vtxMaxPlayer.z);
//	g_player.aPos[2] = D3DXVECTOR3(g_player.pos.x + g_player.g_vtxMaxPlayer.x, 0.0f, g_player.pos.z + g_player.g_vtxMaxPlayer.z);
//	g_player.aPos[3] = D3DXVECTOR3(g_player.pos.x + g_player.g_vtxMaxPlayer.x, 0.0f, g_player.pos.z + g_player.g_vtxMinPlayer.z);
//
//	//�O�ς̎�
//	g_player.Vec[0] = g_player.aPos[1] - g_player.aPos[0];
//	g_player.Vec[1] = g_player.aPos[2] - g_player.aPos[1];
//	g_player.Vec[2] = g_player.aPos[3] - g_player.aPos[2];
//	g_player.Vec[3] = g_player.aPos[0] - g_player.aPos[3];
//
//	// �I�u�W�F�N�g�Ƃ̓����蔻��
//	for (int nCnt = 0; nCnt < 4; nCnt++)
//	{
//		if (nCnt == 0)
//		{// ����
//			g_player.g_Vec[nCnt] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_player.aPos[nCnt];
//		}
//		else if (nCnt == 1)
//		{// ����
//			g_player.g_Vec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_player.aPos[nCnt];
//		}
//		else if (nCnt == 2)
//		{// �E��
//			g_player.g_Vec[nCnt] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_player.aPos[nCnt];
//		}
//		else if (nCnt == 3)
//		{// ��O
//			g_player.g_Vec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_player.aPos[nCnt];
//		}
//
//		//aVec[nCnt] = pos - g_aPos[nCnt];	// �ʂ̎n�_�ƑΏۂ̃x�N�g��
//
//		// ���l���u+�v�̎��A�����蔻�肪�L��
//		g_player.PlayerVec[nCnt] = (g_player.Vec[nCnt].z * g_player.g_Vec[nCnt].x) - (g_player.Vec[nCnt].x * g_player.g_Vec[nCnt].z);
//
//		if (pPos->y <= g_player.pos.y + g_player.g_vtxMaxPlayer.y - fHeightMin && pPos->y > g_player.pos.y + g_player.g_vtxMinPlayer.y - fHeightMax)
//		{
//			if (g_player.PlayerVec[0] > 0.0f && g_player.PlayerVec[1] > 0.0f && g_player.PlayerVec[2] > 0.0f && g_player.PlayerVec[3] > 0.0f)
//			{
//					if (pPos->x > pPosOld->x && pPosOld->x < g_player.pos.x + g_player.g_vtxMinPlayer.x)
//					{// ����	
//						//pPos->x = g_player.pos.x + g_player.g_vtxMinPlayer.x - fWidthMax;
//						//pPlayer->aModel[0].bUse = false;
//						//for (int nCntMat = 0; nCntMat < 246; nCntMat++)
//						//{
//						//	D3DXVECTOR3 pos;
//						//	int nLife;
//						//	D3DXVECTOR3 move;
//						//	float fAngle;
//
//						//	pos = pPlayer->Pos;//�ʒu
//						//	nLife = 35 + rand() % 55;//�����������_��
//						//	fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
//						//	move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
//						//	move.y = 1.5f;//y���̒e�̑��x
//						//	move.z = cosf(fAngle)*2.5f;//y���̒e�̑��x
//						//	SetBillboard(pos, nLife, move, 0);//�G�t�F�N�g����
//						//}
//						//pMove->x = 0.0f;
//						//g_player.aModel[15].pos = D3DXVECTOR3(800, 800, 800);
//					}
//					else if (pPos->x < pPosOld->x && pPosOld->x > g_player.pos.x + g_player.g_vtxMaxPlayer.x)
//					{// �E��	
//						//pPos->x = g_player.pos.x + g_player.g_vtxMaxPlayer.x - fWidthMin;
//						pPlayer->aModel[0].bUse = false;
//						for (int nCntMat = 0; nCntMat < 246; nCntMat++)
//						{
//							D3DXVECTOR3 pos;
//							int nLife;
//							D3DXVECTOR3 move;
//							float fAngle;
//
//							pos = pPlayer->Pos;//�ʒu
//							nLife = 15 + rand() % 20;//�����������_��
//							fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
//							move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
//							move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
//							move.z = cosf(fAngle)*2.5f;//y���̒e�̑��x
//							SetBillboard(pos, nLife, move, 1);//�G�t�F�N�g����
//						}
//						//pMove->x = 0.0f;
//					}
//					else if (pPos->z <= pPosOld->z && pPos->z > g_player.pos.z)
//					{// ����
//						//pPos->z = g_player.pos.z + g_player.g_vtxMaxPlayer.z - fDepthMin;
//						pPlayer->aModel[0].bUse = false;
//						for (int nCntMat = 0; nCntMat < 200; nCntMat++)
//						{
//							D3DXVECTOR3 pos;
//							int nLife;
//							D3DXVECTOR3 move;
//							float fAngle;
//
//							pos = pPlayer->Pos;//�ʒu
//							nLife = 15 + rand() % 20;//�����������_��
//							fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
//							move.x = sinf(fAngle)*4.5f;//x���̒e�̑��x
//							move.y = 5.5f;//y���̒e�̑��x
//							move.z = cosf(fAngle)*4.5f;//y���̒e�̑��x
//							SetBillboard(pos, nLife, move, 1);//�G�t�F�N�g����
//						}
//						//pMove->z = 0.0f;
//					}
//					else if (pPos->z >= pPosOld->z && pPos->z < g_player.pos.z)
//					{// ��O
//						//pPos->z = g_player.pos.z + g_player.g_vtxMaxPlayer.z - fDepthMax;
//						pPlayer->aModel[0].bUse = false;
//						for (int nCntMat = 0; nCntMat < 246; nCntMat++)
//						{
//							D3DXVECTOR3 pos;
//							int nLife;
//							D3DXVECTOR3 move;
//							float fAngle;
//
//							pos = pPlayer->Pos;//�ʒu
//							nLife = 15 + rand() % 20;//�����������_��
//							fAngle = (float)(rand() % 628 - 314) / 100.0f;//�����͈̔�
//							move.x = sinf(fAngle)*2.5f;//x���̒e�̑��x
//							move.y = cosf(fAngle)*2.5f;//y���̒e�̑��x
//							move.z = cosf(fAngle)*2.5f;//y���̒e�̑��x
//							SetBillboard(pos, nLife, move, 1);//�G�t�F�N�g����
//						}
//						//pMove->z = 0.0f;
//					}
//			}
//		}
//	}
//	return bLand;
//}