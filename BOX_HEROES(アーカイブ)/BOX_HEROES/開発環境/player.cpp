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
#include "item.h"
#include "sound.h"
#include "gamepad.h"
#include "select.h"
#include "hp.h"
#include "light.h"
#include "particle.h"
#include "math.h"
#include <stdio.h>

//==============================================================================
// �}�N����`
//==============================================================================
#define PLAYER_MOVE		(1.0f)	// �ړ���
#define PLAYER_TURN		(0.1f)	// ����
#define TEXT_LENGTH		(128)	// �e�L�X�g�ǂݍ��݂̍ő吔
#define DATA_LENGTH		(64)	// �f�[�^�ǂݍ��݂̍ő吔
#define MOVE_MIN		(0.5f)	// �ړ����[�V�������̍ŏ��ړ���
#define MOVECNT_MAX		(20)	// �ړ����[�V�����ȍ~�J�E���g�ő�l
#define SPHERE_SLICE	(10)	// ���̃X���C�X��
#define SPHERE_STACK	(7)		// ���̃X�^�b�N��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
Player g_player[PLAYERNUM_MAX];	// �v���C���[�̍\����
int g_nSMG[PLAYERNUM_MAX];

//==============================================================================
// ����������
//==============================================================================
HRESULT InitPlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾
	Select *pSelect = GetSelect();

	// ��1�v���C���[�̏��
	g_player[0].p_type = P_TYPE_P1;

	// ��2�v���C���[��CPU��
	if (pSelect->mode == PLAYMODE_0)
	{
		g_player[1].p_type = P_TYPE_CPU;
	}
	else
	{
		g_player[1].p_type = P_TYPE_P2;
	}

	for (int nCnt = 0; nCnt < PLAYERNUM_MAX; nCnt++)
	{
		if (pSelect->chara[nCnt] == CHARA_0)
		{
			g_player[nCnt].modelType = MODELTYPE_0;
		}
		else if (pSelect->chara[nCnt] == CHARA_1)
		{
			g_player[nCnt].modelType = MODELTYPE_1;
		}
		else
		{
			g_player[nCnt].modelType = MODELTYPE_2;
		}
	}

	LoadMotion();

	g_player[0].pos = D3DXVECTOR3(-850.0f, 20.0f, -550.0f);

	g_player[1].pos = D3DXVECTOR3(850.0f, 20.0f, 550.0f);
	
	for (int nCntPlayer = 0; nCntPlayer < PLAYERNUM_MAX; nCntPlayer++)
	{
		// X�t�@�C���̓ǂݍ���
		for (int nCnt = 0; nCnt < (g_player[nCntPlayer].nNumModel); nCnt++)
		{
			D3DXLoadMeshFromX(
				g_player[nCntPlayer].aModel[nCnt].aFileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_player[nCntPlayer].aModel[nCnt].pBuffMatModel,
				NULL,
				&g_player[nCntPlayer].aModel[nCnt].nNumMatModel,
				&g_player[nCntPlayer].aModel[nCnt].pMeshModel);

			g_player[nCntPlayer].aModel[nCnt].bUse = true;

			g_player[nCntPlayer].aModel[nCnt].pBuffMatShadow = g_player[nCntPlayer].aModel[nCnt].pBuffMatModel;
		}

		for (int nShort = 0; nShort < SHORT_MAX; nShort++)
		{
			// �U�����苅�̂̐���
			D3DXCreateSphere(
				pDevice,
				g_player[nCntPlayer].as[nShort].fRadius,
				SPHERE_SLICE,
				SPHERE_STACK,
				&g_player[nCntPlayer].as[nShort].pMeshSphere,
				&g_player[nCntPlayer].as[nShort].pBuffMatSphere);

			g_player[nCntPlayer].as[nShort].bUse = false;
			g_player[nCntPlayer].as[nShort].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f);
		}


		// ���[�J���ϐ��錾
		int nNumVtx;			// ���_��
		DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

		D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

		// �}�e���A�����ɑ΂���|�C���^���擾
		for (int nCnt = 0; nCnt < g_player[nCntPlayer].nNumModel; nCnt++,pMat++)
		{
			pMat = (D3DXMATERIAL*)g_player[nCntPlayer].aModel[nCnt].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player[nCntPlayer].aModel[nCnt].nNumMatModel; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
					D3DXCreateTextureFromFile(
						pDevice,
						pMat[nCntMat].pTextureFilename,
						&g_player[nCntPlayer].aModel[nCnt].pTextureModel[nCntMat]);
				}
			}
		}

		// ���_�����擾
		nNumVtx = g_player[nCntPlayer].aModel[0].pMeshModel->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		sizeFVF = D3DXGetFVFVertexSize(g_player[nCntPlayer].aModel[0].pMeshModel->GetFVF());

		// �ϐ��̏�����
		g_player[nCntPlayer].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_player[nCntPlayer].rotDest = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_player[nCntPlayer].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCntPlayer].state = PLAYERSTATE_APPEAR;
		g_player[nCntPlayer].motionType = MOTIONTYPE_NEUTRAL;
		g_player[nCntPlayer].bLoopMotion = false;
		g_player[nCntPlayer].bOnBlock = true;
		g_player[nCntPlayer].nNumKey = 0;
		g_player[nCntPlayer].nKey = 0;
		g_player[nCntPlayer].nCounterMotion = 0;
		g_player[nCntPlayer].nCntState = 120;
		g_player[nCntPlayer].fInRadius = 0.0f;
		g_player[nCntPlayer].bJump = true;
		g_player[nCntPlayer].nMoveCnt = 0;
		g_player[nCntPlayer].nBrendFrame = 5;
		g_player[nCntPlayer].bMotionChange = false;
		g_player[nCntPlayer].vtxMaxPlayer = VTX_MAXP;
		g_player[nCntPlayer].vtxMinPlayer = VTX_MINP;
		g_player[nCntPlayer].weapon = WEAPON_NONE;
		g_player[nCntPlayer].sr = SHORT_NONE;
		g_player[nCntPlayer].nBullet = 0;
		g_nSMG[nCntPlayer] = 0;

		// �e�̐ݒ�
		//g_player[nCntPlayer].nIdx = SetShadow(D3DXVECTOR3(g_player[nCntPlayer].pos.x, 0.0f, g_player[nCntPlayer].pos.z), 10.0f, 10.0f);

		// ���_�o�b�t�@�����b�N
		g_player[nCntPlayer].aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		// ���_���W�̔�r�ƍX�V
		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

			// �e���W�̍ő�l�̔�r
			if (g_player[nCntPlayer].vtxMaxPlayer.x < vtx.x)
			{			
				g_player[nCntPlayer].vtxMaxPlayer.x = vtx.x;
			}			
			if (g_player[nCntPlayer].vtxMaxPlayer.y < vtx.y)
			{			
				g_player[nCntPlayer].vtxMaxPlayer.y = vtx.y;
			}			
			if (g_player[nCntPlayer].vtxMaxPlayer.z < vtx.z)
			{			
				g_player[nCntPlayer].vtxMaxPlayer.z = vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (g_player[nCntPlayer].vtxMinPlayer.x > vtx.x)
			{			
				g_player[nCntPlayer].vtxMinPlayer.x = vtx.x;
			}			
			if (g_player[nCntPlayer].vtxMinPlayer.y > vtx.y)
			{			
				g_player[nCntPlayer].vtxMinPlayer.y = vtx.y;
			}			
			if (g_player[nCntPlayer].vtxMinPlayer.z > vtx.z)
			{			
				g_player[nCntPlayer].vtxMinPlayer.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		// �����a�̌v�Z
		if (g_player[nCntPlayer].fInRadius < g_player[nCntPlayer].vtxMaxPlayer.x)
		{// X���ő�l
			g_player[nCntPlayer].fInRadius = g_player[nCntPlayer].vtxMaxPlayer.x;
		}
		if (g_player[nCntPlayer].fInRadius < g_player[nCntPlayer].vtxMaxPlayer.z)
		{// Z���ő�l
			g_player[nCntPlayer].fInRadius = g_player[nCntPlayer].vtxMaxPlayer.z;
		}
		if (g_player[nCntPlayer].fInRadius < -g_player[nCntPlayer].vtxMinPlayer.x)
		{// X���ŏ��l
			g_player[nCntPlayer].fInRadius = -g_player[nCntPlayer].vtxMinPlayer.x;
		}
		if (g_player[nCntPlayer].fInRadius < -g_player[nCntPlayer].vtxMinPlayer.z)
		{// Z���ŏ��l
			g_player[nCntPlayer].fInRadius = -g_player[nCntPlayer].vtxMinPlayer.z;
		}

		// �v���C���[�̍����̑��
		g_player[nCntPlayer].vtxMaxPlayer.y = g_player[nCntPlayer].fHeight;
	}
	

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitPlayer(void)
{
	for (int nCntPlayer = 0; nCntPlayer < PLAYERNUM_MAX; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < g_player[nCntPlayer].nNumModel; nCnt++)
		{
			if (g_player[nCntPlayer].aModel[nCnt].pMeshModel != NULL)
			{// ���b�V���̔j��
				g_player[nCntPlayer].aModel[nCnt].pMeshModel->Release();
				g_player[nCntPlayer].aModel[nCnt].pMeshModel = NULL;
			}

			if (g_player[nCntPlayer].aModel[nCnt].pBuffMatModel != NULL)
			{// �o�b�t�@�̔j��
				g_player[nCntPlayer].aModel[nCnt].pBuffMatModel->Release();
				g_player[nCntPlayer].aModel[nCnt].pBuffMatModel = NULL;
			}
		}

		for (int nShort = 0; nShort < SHORT_MAX; nShort++)
		{
			if (g_player[nCntPlayer].as[nShort].pMeshSphere != NULL)
			{
				g_player[nCntPlayer].as[nShort].pMeshSphere->Release();
				g_player[nCntPlayer].as[nShort].pMeshSphere = NULL;
			}						   
									   
			if (g_player[nCntPlayer].as[nShort].pBuffMatSphere != NULL)
			{						   
				g_player[nCntPlayer].as[nShort].pBuffMatSphere->Release();
				g_player[nCntPlayer].as[nShort].pBuffMatSphere = NULL;
			}
		}
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdatePlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	for (int nCntPlayer = 0; nCntPlayer < PLAYERNUM_MAX; nCntPlayer++)
	{
		// �O������̊O�όv�Z
		g_player[nCntPlayer].aPoint[0] = D3DXVECTOR3(g_player[nCntPlayer].pos.x - g_player[nCntPlayer].fOutRadius, 0.0f, g_player[nCntPlayer].pos.z - g_player[nCntPlayer].fOutRadius);
		g_player[nCntPlayer].aPoint[1] = D3DXVECTOR3(g_player[nCntPlayer].pos.x - g_player[nCntPlayer].fOutRadius, 0.0f, g_player[nCntPlayer].pos.z + g_player[nCntPlayer].fOutRadius);
		g_player[nCntPlayer].aPoint[2] = D3DXVECTOR3(g_player[nCntPlayer].pos.x + g_player[nCntPlayer].fOutRadius, 0.0f, g_player[nCntPlayer].pos.z + g_player[nCntPlayer].fOutRadius);
		g_player[nCntPlayer].aPoint[3] = D3DXVECTOR3(g_player[nCntPlayer].pos.x + g_player[nCntPlayer].fOutRadius, 0.0f, g_player[nCntPlayer].pos.z - g_player[nCntPlayer].fOutRadius);
		
		g_player[nCntPlayer].aVec[0] = g_player[nCntPlayer].aPoint[1] - g_player[nCntPlayer].aPoint[0];
		g_player[nCntPlayer].aVec[1] = g_player[nCntPlayer].aPoint[2] - g_player[nCntPlayer].aPoint[1];
		g_player[nCntPlayer].aVec[2] = g_player[nCntPlayer].aPoint[3] - g_player[nCntPlayer].aPoint[2];
		g_player[nCntPlayer].aVec[3] = g_player[nCntPlayer].aPoint[0] - g_player[nCntPlayer].aPoint[3];

		// ���[�V�����̍X�V
		UpdateMotion(g_player[nCntPlayer].motionType, nCntPlayer);

		// �v���C���[�̑���
		MovePlayer(nCntPlayer);

		// �v���C���[�̏�ԕω�
		StateChange(nCntPlayer);

		WeaponSet(nCntPlayer, g_player[nCntPlayer].weapon);

		if (g_player[nCntPlayer].nBullet <= 0 && g_player[nCntPlayer].weapon != WEAPON_KNIFE)
		{
			g_player[nCntPlayer].weapon = WEAPON_NONE;
		}

		// �����蔻��
		if(nCntPlayer == PLAYERNUM_0)
		{
			CollisionDamage(nCntPlayer, PLAYERNUM_1, D3DXVECTOR3(g_player[PLAYERNUM_0].as[g_player[PLAYERNUM_0].sr].mtxWorld._41, g_player[PLAYERNUM_0].as[g_player[PLAYERNUM_0].sr].mtxWorld._42, g_player[PLAYERNUM_0].as[g_player[PLAYERNUM_0].sr].mtxWorld._43));
		}
		else if (nCntPlayer == PLAYERNUM_1)
		{
			CollisionDamage(nCntPlayer, PLAYERNUM_0, D3DXVECTOR3(g_player[PLAYERNUM_1].as[g_player[PLAYERNUM_1].sr].mtxWorld._41, g_player[PLAYERNUM_1].as[g_player[PLAYERNUM_1].sr].mtxWorld._42, g_player[PLAYERNUM_1].as[g_player[PLAYERNUM_1].sr].mtxWorld._43));
		}

		g_player[nCntPlayer].bOnBlock = CollisionVec(&g_player[nCntPlayer].pos, &g_player[nCntPlayer].posOld, &g_player[nCntPlayer].move, g_player[nCntPlayer].fInRadius, g_player[nCntPlayer].fHeight, nCntPlayer);
		TouchItem(&g_player[nCntPlayer].pos, g_player[nCntPlayer].fInRadius, g_player[nCntPlayer].fHeight,nCntPlayer);
	}
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
	D3DLIGHT9 *pLight = GetLight();

	D3DXMATRIX mtxShadow;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;
	D3DXPLANE plane;
	D3DMATERIAL9 matShadow;

	for (int nCntPlayer = 0; nCntPlayer < PLAYERNUM_MAX; nCntPlayer++)
	{
		// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player[nCntPlayer].mtxWorld);

		// �v���C���[�̌����̔��f
		D3DXMatrixRotationYawPitchRoll(
			&mtxRot, 
			g_player[nCntPlayer].rot.y, 
			g_player[nCntPlayer].rot.x, 
			g_player[nCntPlayer].rot.z);
		D3DXMatrixMultiply(
			&g_player[nCntPlayer].mtxWorld,
			&g_player[nCntPlayer].mtxWorld, 
			&mtxRot);

		// �v���C���[�̈ʒu�𔽉f
		D3DXMatrixTranslation(
			&mtxTrans, 
			g_player[nCntPlayer].pos.x,
			g_player[nCntPlayer].pos.y, 
			g_player[nCntPlayer].pos.z);
		D3DXMatrixMultiply(
			&g_player[nCntPlayer].mtxWorld,
			&g_player[nCntPlayer].mtxWorld, 
			&mtxTrans);

		// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCntPlayer].mtxWorld);



		// �V���h�E�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxShadow);

		// ���C�g�x�N�g���̐ݒ�
		vecLight = D3DXVECTOR4(pLight->Direction.x, pLight->Direction.y, pLight->Direction.z, 0.0f);

		// ���ʂ̐���
		pos = g_player[nCntPlayer].posShadow;
		normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		D3DXPlaneFromPointNormal(&plane, &pos, &normal);


		// �V���h�E�}�g���b�N�X�̐ݒ�
		//pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matShadow);

		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

			// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// �e�p�[�c�̌����𔽉f
			D3DXMatrixRotationYawPitchRoll(
				&mtxRotModel,
				g_player[nCntPlayer].aModel[nCntModel].rot.y,
				g_player[nCntPlayer].aModel[nCntModel].rot.x,
				g_player[nCntPlayer].aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&mtxRotModel);

			// �e�p�[�c�̈ʒu�𔽉f
			D3DXMatrixTranslation(
				&mtxTransModel,
				g_player[nCntPlayer].aModel[nCntModel].pos.x,
				g_player[nCntPlayer].aModel[nCntModel].pos.y,
				g_player[nCntPlayer].aModel[nCntModel].pos.z);

			D3DXMatrixMultiply(
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&mtxTransModel);

			// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
			if (g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player[nCntPlayer].aModel[g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player[nCntPlayer].mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
			}

			// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&mtxParent);

			// ���Z�����̐���
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			for (int nCntMat = 0; nCntMat < (int)g_player[nCntPlayer].aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				matShadow.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&matShadow);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// �V���h�E�}�g���b�N�X�̐���
				D3DXMatrixShadow(&mtxShadow, &vecLight, &plane);
				D3DXMatrixMultiply(&mtxShadow, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld, &mtxShadow);

				// �V���h�E�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

				if (g_player[nCntPlayer].aModel[nCntModel].bUse == true)
				{
					// ���f��(�p�[�c)�̕`��
					g_player[nCntPlayer].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
				}
			}

			// �ʏ�̍����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matShadow);




		

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		for (int nCntModel = 0; nCntModel < g_player[nCntPlayer].nNumModel; nCntModel++)
		{
			D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

			// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// �e�p�[�c�̌����𔽉f
			D3DXMatrixRotationYawPitchRoll(
				&mtxRotModel, 
				g_player[nCntPlayer].aModel[nCntModel].rot.y, 
				g_player[nCntPlayer].aModel[nCntModel].rot.x, 
				g_player[nCntPlayer].aModel[nCntModel].rot.z);

			D3DXMatrixMultiply(
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld, 
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld, 
				&mtxRotModel);

			// �e�p�[�c�̈ʒu�𔽉f
			D3DXMatrixTranslation(
				&mtxTransModel, 
				g_player[nCntPlayer].aModel[nCntModel].pos.x, 
				g_player[nCntPlayer].aModel[nCntModel].pos.y, 
				g_player[nCntPlayer].aModel[nCntModel].pos.z);
			D3DXMatrixMultiply(
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld, 
				&mtxTransModel);

			// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
			if (g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent != -1)
			{
				mtxParent = g_player[nCntPlayer].aModel[g_player[nCntPlayer].aModel[nCntModel].nIdxModelParent].mtxWorld;
			}
			else
			{
				mtxParent = g_player[nCntPlayer].mtxWorld;	// �v���C���[�̃}�g���b�N�X��ݒ�
			}

			// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
			D3DXMatrixMultiply(
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&g_player[nCntPlayer].aModel[nCntModel].mtxWorld,
				&mtxParent);

			// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_player[nCntPlayer].aModel[nCntModel].mtxWorld);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_player[nCntPlayer].aModel[nCntModel].pBuffMatModel->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_player[nCntPlayer].aModel[nCntModel].nNumMatModel; nCntMat++)
			{
				if (g_player[nCntPlayer].state == PLAYERSTATE_APPEAR && g_player[nCntPlayer].nCntState % 2 != 0)
				{
					pMat[nCntMat].MatD3D.Diffuse.a = 0.0f;
				}
				else
				{
					pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
				}

				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, *g_player[nCntPlayer].aModel[nCntModel].pTextureModel);

				if (g_player[nCntPlayer].aModel[nCntModel].bUse == true)
				{
					// ���f��(�p�[�c)�̕`��
					g_player[nCntPlayer].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
				}
			}
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);

		AttackParts(nCntPlayer);
	}
}

//==============================================================================
// �v���C���[�̎擾
//==============================================================================
Player *GetPlayer(void)
{
	return &g_player[0];
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void UpdateMotion(MOTIONTYPE motionType, int nCntPlayer)
{
	// �L�[���ƃ��[�v���̑��
	g_player[nCntPlayer].nNumKey = g_player[nCntPlayer].aMotionInfo[motionType].nNumKey;
	g_player[nCntPlayer].bLoopMotion = g_player[nCntPlayer].aMotionInfo[motionType].bLoop;

	// ���[�V�����J�E���^�[�̉��Z
	if (g_player[nCntPlayer].bMotionChange == true)
	{// ���[�V�����u�����h���s��
		if (g_player[nCntPlayer].nCounterMotion < g_player[nCntPlayer].nBrendFrame)
		{// �J�E���g���
			g_player[nCntPlayer].nCounterMotion++;
		}
	}
	else
	{// �ʏ펞
		if (g_player[nCntPlayer].nCounterMotion < g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame)
		{// �J�E���g���
			g_player[nCntPlayer].nCounterMotion++;
		}
	}


	if (g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nCntFrameTotal < g_player[nCntPlayer].nFrameTotal[motionType])
	{
		g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nCntFrameTotal++;
	}

	// ���f���p�[�c���Ƃ̃��[�V�����A�j���[�V����
	for (int nCnt = 0; nCnt < MODEL_PARTS; nCnt++)
	{
		if (g_player[nCntPlayer].nKey == g_player[nCntPlayer].nNumKey - 1 && g_player[nCntPlayer].bLoopMotion == true)
		{// ���[�v���čŏ��ɖ߂�Ƃ�
			g_player[nCntPlayer].aModel[nCnt].pos.x = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosX + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosX - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosX) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].pos.y = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosY + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosY - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosY) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].pos.z = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosZ + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fPosZ - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosZ) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.x = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotX + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotX - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotX) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.y = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotY + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotY - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotY) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.z = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotZ + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[0].aKey[nCnt].fRotZ - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotZ) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].posMemo = g_player[nCntPlayer].aModel[nCnt].pos;
			g_player[nCntPlayer].aModel[nCnt].rotMemo = g_player[nCntPlayer].aModel[nCnt].rot;
		}
		else if (g_player[nCntPlayer].bMotionChange == true)
		{// ���[�V�����u�����h
			g_player[nCntPlayer].aModel[nCnt].pos.x = g_player[nCntPlayer].aModel[nCnt].posMemo.x + (g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].motionType].aKeySet[0].aKey[nCnt].fPosX - g_player[nCntPlayer].aModel[nCnt].posMemo.x) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].nBrendFrame);
			g_player[nCntPlayer].aModel[nCnt].pos.y = g_player[nCntPlayer].aModel[nCnt].posMemo.y + (g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].motionType].aKeySet[0].aKey[nCnt].fPosY - g_player[nCntPlayer].aModel[nCnt].posMemo.y) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].nBrendFrame);
			g_player[nCntPlayer].aModel[nCnt].pos.z = g_player[nCntPlayer].aModel[nCnt].posMemo.z + (g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].motionType].aKeySet[0].aKey[nCnt].fPosZ - g_player[nCntPlayer].aModel[nCnt].posMemo.z) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].nBrendFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.x = g_player[nCntPlayer].aModel[nCnt].rotMemo.x + (g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].motionType].aKeySet[0].aKey[nCnt].fRotX - g_player[nCntPlayer].aModel[nCnt].rotMemo.x) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].nBrendFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.y = g_player[nCntPlayer].aModel[nCnt].rotMemo.y + (g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].motionType].aKeySet[0].aKey[nCnt].fRotY - g_player[nCntPlayer].aModel[nCnt].rotMemo.y) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].nBrendFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.z = g_player[nCntPlayer].aModel[nCnt].rotMemo.z + (g_player[nCntPlayer].aMotionInfo[g_player[nCntPlayer].motionType].aKeySet[0].aKey[nCnt].fRotZ - g_player[nCntPlayer].aModel[nCnt].rotMemo.z) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].nBrendFrame);
			g_player[nCntPlayer].aModel[nCnt].posMemo = g_player[nCntPlayer].aModel[nCnt].pos;
			g_player[nCntPlayer].aModel[nCnt].rotMemo = g_player[nCntPlayer].aModel[nCnt].rot;
		}
		else
		{// �ʏ펞
			g_player[nCntPlayer].aModel[nCnt].pos.x = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosX + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey + 1].aKey[nCnt].fPosX - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosX) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].pos.y = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosY + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey + 1].aKey[nCnt].fPosY - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosY) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].pos.z = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosZ + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey + 1].aKey[nCnt].fPosZ - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fPosZ) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.x = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotX + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey + 1].aKey[nCnt].fRotX - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotX) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.y = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotY + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey + 1].aKey[nCnt].fRotY - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotY) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].rot.z = g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotZ + (g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey + 1].aKey[nCnt].fRotZ - g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].aKey[nCnt].fRotZ) * ((float)g_player[nCntPlayer].nCounterMotion / (float)g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame);
			g_player[nCntPlayer].aModel[nCnt].posMemo = g_player[nCntPlayer].aModel[nCnt].pos;
			g_player[nCntPlayer].aModel[nCnt].rotMemo = g_player[nCntPlayer].aModel[nCnt].rot;
		}

		if (g_player[nCntPlayer].bMotionChange == false)
		{// ���[�V�����ω��Ȃ�
			if (g_player[nCntPlayer].nCounterMotion == g_player[nCntPlayer].aMotionInfo[motionType].aKeySet[g_player[nCntPlayer].nKey].nFrame)
			{// �L�[�t���[���I����
				if (g_player[nCntPlayer].motionType != MOTIONTYPE_JUMP || g_player[nCntPlayer].nKey != g_player[nCntPlayer].nNumKey - 2)
				{// �W�����v�ȊO�ŃL�[�I�������Z�b�g
					g_player[nCntPlayer].nCounterMotion = 0;
				}

				if (g_player[nCntPlayer].nKey == g_player[nCntPlayer].nNumKey - 1 && g_player[nCntPlayer].bLoopMotion == true)
				{// ���[�v����Ƃ�
					g_player[nCntPlayer].nKey = 0;
					g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nCntFrameTotal = 0;
				}
				else if (g_player[nCntPlayer].nKey == g_player[nCntPlayer].nNumKey - 2 && g_player[nCntPlayer].bLoopMotion == false)
				{// ���[�v�����I������Ƃ�
					if (g_player[nCntPlayer].motionTypeOld != MOTIONTYPE_JUMP)
					{// ���O���W�����v�ȊO�̎�
						g_player[nCntPlayer].motionType = MOTIONTYPE_NEUTRAL;	// �j���[�g�����ֈڍs
						g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nCntFrameTotal = 0;
					}
				}
				else if (g_player[nCntPlayer].nKey < g_player[nCntPlayer].nNumKey)
				{// �L�[�̃J�E���g
					g_player[nCntPlayer].nKey++;
				}
			}
			else if (g_player[nCntPlayer].motionTypeOld != g_player[nCntPlayer].motionType)
			{// ���[�V�����ω���	
				if (g_player[nCntPlayer].motionType != MOTIONTYPE_JUMP &&
					g_player[nCntPlayer].motionType != MOTIONTYPE_LANDING)
				{
					g_player[nCntPlayer].bMotionChange = true;
				}

				g_player[nCntPlayer].nKey = 0;
				g_player[nCntPlayer].nCounterMotion = 0;
				g_player[nCntPlayer].attack.nCntFrameTotal = 0;

				if (g_player[nCntPlayer].motionTypeOld == MOTIONTYPE_NEUTRAL && g_player[nCntPlayer].motionType == MOTIONTYPE_MOVE)
				{// �j���[�g��������ړ���
					g_player[nCntPlayer].nBrendFrame = MBF_NEU_MOVE;
				}
				else if (g_player[nCntPlayer].motionTypeOld == MOTIONTYPE_MOVE && g_player[nCntPlayer].motionType == MOTIONTYPE_NEUTRAL)
				{// �ړ�����j���[�g������
					g_player[nCntPlayer].nBrendFrame = MBF_MOVE_NEU;
				}
				else if (g_player[nCntPlayer].motionTypeOld == MOTIONTYPE_NEUTRAL && g_player[nCntPlayer].motionType == MOTIONTYPE_ACTION)
				{// �j���[�g��������A�N�V������
					g_player[nCntPlayer].nBrendFrame = g_player[nCntPlayer].aMotionInfo[MOTIONTYPE_ACTION].aKeySet[0].nFrame;
				}
				else if (g_player[nCntPlayer].motionTypeOld == MOTIONTYPE_ACTION && g_player[nCntPlayer].motionType == MOTIONTYPE_NEUTRAL)
				{// �A�N�V��������j���[�g������
					g_player[nCntPlayer].nBrendFrame = MBF_ACT_NEU;
				}
				else if (g_player[nCntPlayer].motionTypeOld == MOTIONTYPE_LANDING && g_player[nCntPlayer].motionType == MOTIONTYPE_NEUTRAL)
				{// ���n����j���[�g����
					g_player[nCntPlayer].nBrendFrame = MBF_LND_NEU;
				}
				break;
			}
		}
		else if (g_player[nCntPlayer].bMotionChange == true)
		{// ���[�V�����u�����h���̃J�E���g���Z�b�g
			if (g_player[nCntPlayer].nCounterMotion == g_player[nCntPlayer].nBrendFrame || g_player[nCntPlayer].motionTypeOld != g_player[nCntPlayer].motionType)
			{
				g_player[nCntPlayer].nKey = 0;
				g_player[nCntPlayer].nCounterMotion = 0;
				g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nCntFrameTotal = 0;
				g_player[nCntPlayer].bMotionChange = false;
			}
		}

		// �Ō��̓����蔻��̗L����
		if (g_player[nCntPlayer].motionType == MOTIONTYPE_ACTION || g_player[nCntPlayer].motionType == MOTIONTYPE_SLASH)
		{
			if (g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nCntFrameTotal >= g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nStartFrame &&
			 g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nCntFrameTotal <= g_player[nCntPlayer].as[g_player[nCntPlayer].sr].nEndFrame)
			{// �J�E���g�͈͓��ŗL��
				g_player[nCntPlayer].as[g_player[nCntPlayer].sr].bUse = true;
				if (g_player[nCntPlayer].motionType == MOTIONTYPE_ACTION)
				{
					if (g_player[nCntPlayer].as[0].nCntFrameTotal == g_player[nCntPlayer].as[0].nStartFrame)
					{
						PlaySound(SOUND_LABEL_SE_SMASH);
					}
				}
				else
				{
					if (g_player[nCntPlayer].as[1].nCntFrameTotal == g_player[nCntPlayer].as[1].nStartFrame)
					{
						PlaySound(SOUND_LABEL_SE_SLASH);
					}
				}
			}
		}
		else
		{// ����ȊO
			g_player[nCntPlayer].as[g_player[nCntPlayer].sr].bUse = false;
		}

		// �����蔻��̕\��
		if (g_player[nCntPlayer].as[g_player[nCntPlayer].sr].bUse == true)
		{
			g_player[nCntPlayer].as[g_player[nCntPlayer].sr].col.a = 1.0f;
		}
		else
		{
			g_player[nCntPlayer].as[g_player[nCntPlayer].sr].col.a = 0.0f;
		}
	}

	// ���O�̃��[�V������Ԃ̕ۑ�
	g_player[nCntPlayer].motionTypeOld = g_player[nCntPlayer].motionType;
}

//==============================================================================
// .txt�t�H���_�̓ǂݍ���
//==============================================================================
void LoadMotion(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char aEqual[2] = { NULL };					// �u=�v�ǂݎ��p�ϐ�
	bool bComment = false;						// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = {NULL};			// �e�L�X�g�ǂݎ��p�ϐ�
	char aCharaSet[DATA_LENGTH] = { NULL };		// �L�����f�[�^�ǂݎ��p�ϐ�
	char aPartsSet[DATA_LENGTH] = { NULL };		// �p�[�c�f�[�^�ǂݎ��p�ϐ�
	char aMotionSet[DATA_LENGTH] = { NULL };	// ���[�V�����ǂݎ��p�ϐ�
	char aKeySet[DATA_LENGTH] = { NULL };		// �L�[�ݒ���ǂݎ��p�ϐ�
	char aKey[DATA_LENGTH] = { NULL };			// �L�[���ǂݎ��p�ϐ�

	Select *pSelect = GetSelect();

	//g_player[0].modelType = (ModelType)pSelect->chara;

	// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];					
	char *pCharaSet = &aCharaSet[0];
	char *pPartsSet = &aPartsSet[0];
	char *pMotionSet = &aMotionSet[0];
	char *pKeySet = &aKeySet[0];
	char *pKey = &aKey[0];

	for (int nCnt = 0; nCnt < PLAYERNUM_MAX; nCnt++)
	{
		switch (g_player[nCnt].modelType)
		{
		case 0:
			// �f�[�^�̓ǂݍ���
			pFile = fopen("data/TEXT/motion_player00.txt", "r");

			break;

		case 1:
			// �f�[�^�̓ǂݍ���
			pFile = fopen("data/TEXT/motion_player01.txt", "r");

			break;

		case 2:
			// �f�[�^�̓ǂݍ���
			pFile = fopen("data/TEXT/motion_player02.txt", "r");

			break;

		default:
			break;
		}

		if (pFile != NULL)
		{ //�t�@�C���W�J�\
			aText[0] = { NULL };
			aCharaSet[0] = { NULL };
			aPartsSet[0] = { NULL };
			aMotionSet[0] = { NULL };
			aKeySet[0] = { NULL };	
			aKey[0] = { NULL };
			int nIdxParts = 0;			// �p�[�c��
			int nMotion = 0;			// ���[�V�����̐�
			int nCntFile = 0;			// X�f�[�^�̐�
			int nAs = 0;
			while (strcmp("END_SCRIPT", pText) != 0)
			{
				aText[0] = { NULL };
				if (bComment == false)
				{// �R�����g�A�E�g���Ă��Ȃ�
					fscanf(pFile, "%s", &aText[0]);

					if (aText[0] == '#')
					{// ������̐擪���u#�v�Ȃ�΃R�����g�A�E�g��
						bComment = true;
					}
					else
					{// �ʏ펞
						if (strcmp("NUM_MODEL", pText) == 0)
						{// ���f���̐�
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &g_player[nCnt].nNumModel);
						}
						else if (strcmp("NUM_WEAPON", pText) == 0)
						{
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%d", &g_player[nCnt].nNumWeapon);
						}
						else if (strcmp("MODEL_FILENAME", pText) == 0)
						{// X�t�@�C�����̓ǂݍ���
							fscanf(pFile, "%s", &aEqual[0]);
							fscanf(pFile, "%s", &g_player[nCnt].aModel[nCntFile].aFileName[0]);
							nCntFile++;
						}
						else if (strcmp("CHARACTERSET", pText) == 0)
						{// �L�����̏��
							while (strcmp("END_CHARACTERSET", pCharaSet) != 0)
							{// �L�������̓ǂݎ��
								fscanf(pFile, "%s", &aCharaSet[0]);
								if (strcmp("NUM_PARTS", pCharaSet) == 0)
								{

								}
								else if (strcmp("MOVE", pCharaSet) == 0)
								{// �����蔻��
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f", &g_player[nCnt].fMove);
								}
								else if (strcmp("JUMP", pCharaSet) == 0)
								{// �����蔻��
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f", &g_player[nCnt].fJump);
								}
								else if (strcmp("RADIUS", pCharaSet) == 0)
								{// �����蔻��
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f", &g_player[nCnt].fOutRadius);
								}
								else if (strcmp("HEIGHT", pCharaSet) == 0)
								{// �����蔻��
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%f", &g_player[nCnt].fHeight);
								}
								else if (strcmp("PARTSSET", pCharaSet) == 0)
								{// �p�[�c���
									aPartsSet[0] = { NULL };

									while (strcmp("END_PARTSSET", pPartsSet) != 0)
									{
										fscanf(pFile, "%s", &aPartsSet[0]);
										if (strcmp("INDEX", pPartsSet) == 0)
										{// �p�[�c���̓ǂݎ��
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%d", &nIdxParts);
										}
										else if (strcmp("PARENT", pPartsSet) == 0)
										{// �p�[�c�̐e���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%d", &g_player[nCnt].aModel[nIdxParts].nIdxModelParent);
										}
										else if (strcmp("POS", pPartsSet) == 0)
										{// �p�[�c�̈ʒu���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%f", &g_player[nCnt].aModel[nIdxParts].pos.x);
											fscanf(pFile, "%f", &g_player[nCnt].aModel[nIdxParts].pos.y);
											fscanf(pFile, "%f", &g_player[nCnt].aModel[nIdxParts].pos.z);
											g_player[nCnt].aModel[nIdxParts].posReset = g_player[nCnt].aModel[nIdxParts].pos;
										}
										else if (strcmp("ROT", pPartsSet) == 0)
										{// �p�[�c�̊p�x���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%f", &g_player[nCnt].aModel[nIdxParts].rot.x);
											fscanf(pFile, "%f", &g_player[nCnt].aModel[nIdxParts].rot.y);
											fscanf(pFile, "%f", &g_player[nCnt].aModel[nIdxParts].rot.z);
										}
									}
								}
							}
						}
						else if (strcmp("MOTIONSET", pText) == 0)
						{
							// �ϐ��̏�����
							aMotionSet[0] = { NULL };

							// ���[�J���ϐ��錾
							int nLoop = 0;
							int nKeySet = 0;

							while (strcmp("END_MOTIONSET", pMotionSet) != 0)
							{// ���[�V�����̓ǂݍ���
								fscanf(pFile, "%s", &aMotionSet[0]);
								if (strcmp("LOOP", pMotionSet) == 0)
								{// ���[�v���邩
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%d", &nLoop);
									if (nLoop == 1)
									{// �P�̏ꍇ���[�v����
										g_player[nCnt].bLoopMotion = true;
										g_player[nCnt].aMotionInfo[nMotion].bLoop = true;
									}
								}
								else if (strcmp("NUM_KEY", pMotionSet) == 0)
								{// �L�[���̓ǂݍ���
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%d", &g_player[nCnt].nNumKey);
								}
								else if (strcmp("COLLISION", pMotionSet) == 0)
								{
									fscanf(pFile, "%s", &aEqual[0]);
									fscanf(pFile, "%d", &g_player[nCnt].as[nAs].nParts);
									fscanf(pFile, "%f", &g_player[nCnt].as[nAs].pos.x);
									fscanf(pFile, "%f", &g_player[nCnt].as[nAs].pos.y);
									fscanf(pFile, "%f", &g_player[nCnt].as[nAs].pos.z);
									fscanf(pFile, "%f", &g_player[nCnt].as[nAs].fRadius);
									fscanf(pFile, "%d", &g_player[nCnt].as[nAs].nStartFrame);
									fscanf(pFile, "%d", &g_player[nCnt].as[nAs].nEndFrame);
									nAs++;
								}
								else if (strcmp("KEYSET", pMotionSet) == 0)
								{// �L�[�̓ǂݍ���
								 // ���[�J���ϐ��錾
									int nKey = 0;
									// �ϐ��̏�����
									aKeySet[0] = { NULL };

									while (strcmp("END_KEYSET", pKeySet) != 0)
									{// �L�[��񍀖ڂ̓ǂݍ���
										fscanf(pFile, "%s", &aKeySet[0]);

										if (aKeySet[0] == '#')
										{// �R�����g�A�E�g
										 // ���[�J���ϐ��錾
											char c = NULL;
											char d = NULL;
											fscanf(pFile, "%c", &c);
											while (c != '\n' && d != '\n')
											{
												fscanf(pFile, "%s", &aKey[0]);
												fscanf(pFile, "%c", &d);
											}
										}

										if (strcmp("KEY", pKeySet) == 0)
										{// �L�[���̓ǂݍ���
											aKey[0] = { NULL };
											while (strcmp("END_KEY", pKey) != 0)
											{// �ʒu�E�p�x�̓ǂݍ���
												fscanf(pFile, "%s", &aKey[0]);
												if (strcmp("POS", pKey) == 0)
												{// �ʒu���̓ǂݍ���
													fscanf(pFile, "%s", &aEqual[0]);
													fscanf(pFile, "%f", &g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosX);
													fscanf(pFile, "%f", &g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosY);
													fscanf(pFile, "%f", &g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosZ);
													g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosX += g_player[nCnt].aModel[nKey].pos.x;
													g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosY += g_player[nCnt].aModel[nKey].pos.y;
													g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fPosZ += g_player[nCnt].aModel[nKey].pos.z;
												}
												else if (strcmp("ROT", pKey) == 0)
												{// �p�x���̓ǂݍ���
													fscanf(pFile, "%s", &aEqual[0]);
													fscanf(pFile, "%f", &g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fRotX);
													fscanf(pFile, "%f", &g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fRotY);
													fscanf(pFile, "%f", &g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].aKey[nKey].fRotZ);
												}
											}
											nKey++;
										}
										else if (strcmp("FRAME", pKeySet) == 0)
										{// �L�[�t���[�����̓ǂݍ���
											fscanf(pFile, "%s", &aEqual[0]);
											fscanf(pFile, "%d", &g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].nFrame);
											g_player[nCnt].nFrameTotal[nMotion] += g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].nFrame;
											if (g_player[nCnt].aMotionInfo[nMotion].bLoop == false && nKeySet == (g_player[nCnt].nNumKey - 1))
											{
												g_player[nCnt].nFrameTotal[nMotion] -= g_player[nCnt].aMotionInfo[nMotion].aKeySet[nKeySet].nFrame;
											}
										}
									}
									nKeySet++;
								}
							}
							g_player[nCnt].aMotionInfo[nMotion].nNumKey = nKeySet;	// �L�[���̐ݒ�
							nMotion++;
						}
					}
				}
				else if (bComment == true)
				{// �R�����g�A�E�g����
				 // ���[�J���ϐ��錾
					char a = NULL;
					char b = NULL;
					fscanf(pFile, "%c", &a);
					while (a != '\n' && b != '\n')
					{
						fscanf(pFile, "%s", &aText[0]);
						fscanf(pFile, "%c", &b);
					}
					bComment = false;
				}
			}
			fclose(pFile);
		}
		else
		{ // �t�@�C���W�J�s��
		}
	}
}

//==============================================================================
// �v���C���[�̏�ԕω�
//==============================================================================
void StateChange(int nCnt)
{
	// ���[�J���ϐ��錾
	Player *pPlayer = &g_player[0];

	pPlayer += nCnt;

	// �v���C���[�̏�Ԃ��Ƃ̏���
	switch (pPlayer->state)
	{
	case PLAYERSTATE_DAMAGE:	// ��_���[�W
		pPlayer->bOnBlock = false;					// �n�ʂ��痣���
		pPlayer->move.x *= -1;						// �ړ��͂𔽓]
		pPlayer->move.z *= -1;
		pPlayer->move.y = 5.0f;						// �v���C���[���΂�
		pPlayer->bJump = true;
		pPlayer->nKey = 0;							// �L�[�J�E���g�̃��Z�b�g
		pPlayer->nCounterMotion = 0;				// ���[�V�����J�E���g�̃��Z�b�g
		pPlayer->motionType = MOTIONTYPE_DAMAGE;	// �_���[�W���[�V�����̎��s

		pPlayer->nCntState--;					// ��ԃJ�E���g�̌��Z
		if (pPlayer->nCntState <= 0)
		{// ���̏�Ԃֈڍs
			pPlayer->nCntState = 50;
			pPlayer->state = PLAYERSTATE_APPEAR;
		}
		//else
		//{// �̗͂�0�̎�
		//	pPlayer->state = PLAYERSTATE_GAMEOVER;		// �Q�[���[�I�[�o�[
		//}

		break;

	case PLAYERSTATE_APPEAR:	// �o����
		pPlayer->nCntState--;							// ��ԃJ�E���g�̌��Z

		if (pPlayer->nCntState <= 0)
		{// �ʏ��Ԃւ̈ڍs
			pPlayer->state = PLAYERSTATE_NORMAL;		// �ʏ���
		}
		break;
	}
}

//==============================================================================
// �v���C���[�̑���
//==============================================================================
void MovePlayer(int nCnt)
{
	// �J�����̎擾
	Camera *pCamera = GetCamera();

	pCamera += nCnt;

	// ���O�̈ʒu�̕ۑ�
	g_player[nCnt].posOld = g_player[nCnt].pos;

	// �d�͂̔���
	if (g_player[nCnt].pos.y > 0.0f && g_player[nCnt].bOnBlock == false)
	{
		if (GetKeyboardPress(KEYINFO_JUMP) != true || BuPu(KEYINFO::KEYINFO_OK,nCnt) != true)
		{
			g_player[nCnt].move.y -= PLUS_GRAVITY;
		}
	}

	// �v���C���[�̒��n����
	if (g_player[nCnt].pos.y < 0.0f)
	{
		g_player[nCnt].bOnBlock = true;
		g_player[nCnt].nKey = 0;
		g_player[nCnt].nCounterMotion = 0;
		g_player[nCnt].motionType = MOTIONTYPE_LANDING;
		g_player[nCnt].posShadow = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
	}
	if (g_player[nCnt].bOnBlock == true)
	{
		if (g_player[nCnt].pos.y < 0.0f)
		{
			g_player[nCnt].pos.y = 0.0f;
		}
		g_player[nCnt].bJump = false;
		g_player[nCnt].move.y = 0.0f;
	}

	// �ʒu�̃��Z�b�g
	if (GetKeyboardTrigger(KEYINFO_PRESET) == true)
	{
		g_player[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_player[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �W�����v
	if (GetKeyboardTrigger(KEYINFO_JUMP) == true || BuDo(KEYINFO::KEYINFO_OK,nCnt) == true)
	{
		if (g_player[nCnt].bOnBlock == true)
		{
			PlaySound(SOUND_LABEL_SE_JUMP);
			g_player[nCnt].nKey = 0;
			g_player[nCnt].nCounterMotion = 0;
			g_player[nCnt].motionType = MOTIONTYPE_JUMP;
		}
		g_player[nCnt].bOnBlock = false;
	}
	if (GetKeyboardPress(KEYINFO_JUMP) == true || BuPu(KEYINFO::KEYINFO_OK,nCnt) == true)
	{
		if (g_player[nCnt].bJump == false)
		{
			if (g_player[nCnt].nJumpCnt == 1)
			{
				g_player[nCnt].move.y = g_player[nCnt].fJump;
			}
			if (g_player[nCnt].nJumpCnt < 7)
			{
				g_player[nCnt].nJumpCnt++;
				g_player[nCnt].move.y += 1.0f;
			}
		}
	}
	if (GetKeyboardRelease(KEYINFO_JUMP) == true || BuUp(KEYINFO::KEYINFO_OK,nCnt) == true)
	{
		if (g_player[nCnt].bJump == false)
		{
			g_player[nCnt].nJumpCnt = 0;
			g_player[nCnt].bJump = true;
		}
	}

	// �U���s��
	if (g_player[nCnt].weapon == WEAPON_MACHINEGUN)
	{// �}�V���K��
		if (GetKeyboardPress(KEYINFO_ATTACK) == true || BuPu(KEYINFO::KEYINFO_ATTACK, nCnt) == true)
		{
			// �J�������v���C���[�̔w���
			if (GetKeyboardTrigger(KEYINFO_CAMERA_FRONT) == true || BuDo(KEYINFO::KEYINFO_CAMERA_FRONT, nCnt) == true)
			{
				pCamera->rot.y = g_player[nCnt].rot.y - D3DX_PI;
			}

			g_player[nCnt].nKey = 0;
			g_player[nCnt].nCounterMotion = 0;
			WeaponAction(nCnt, g_player[nCnt].weapon);
			g_nSMG[nCnt]++;
			if (g_nSMG[nCnt] % 8 == 0)
			{
				SetBullet(D3DXVECTOR3(
					g_player[nCnt].aModel[17].mtxWorld._41 + sinf(D3DX_PI - g_player[nCnt].rot.y) * -10.0f,
					g_player[nCnt].aModel[17].mtxWorld._42 + 25.0f,
					g_player[nCnt].aModel[17].mtxWorld._43 + cosf(D3DX_PI - g_player[nCnt].rot.y) * 10.0f),
					D3DXVECTOR3(sinf(D3DX_PI - g_player[nCnt].rot.y) * -15.0f, 0.0f, cosf(D3DX_PI - g_player[nCnt].rot.y) * 15.0f), 100, 1, nCnt);
				g_player[nCnt].nBullet--;
				PlaySound(SOUND_LABEL_SE_SHOT);
			}


		}
		if (GetKeyboardRelease(KEYINFO_ATTACK) == true || BuUp(KEYINFO::KEYINFO_ATTACK, nCnt) == true)
		{
			g_nSMG[nCnt] = 0;
		}
	}
	else if (g_player[nCnt].weapon == WEAPON_HANDGUN)
	{// �n���h�K��
		if (GetKeyboardTrigger(KEYINFO_ATTACK) == true || BuDo(KEYINFO::KEYINFO_ATTACK, nCnt) == true)
		{
			g_player[nCnt].nKey = 0;
			g_player[nCnt].nCounterMotion = 0;
			WeaponAction(nCnt, g_player[nCnt].weapon);
			SetBullet(D3DXVECTOR3(
				g_player[nCnt].aModel[16].mtxWorld._41 + sinf(D3DX_PI - g_player[nCnt].rot.y) * -10.0f,
				g_player[nCnt].aModel[16].mtxWorld._42 + 25.0f,
				g_player[nCnt].aModel[16].mtxWorld._43 + cosf(D3DX_PI - g_player[nCnt].rot.y) * 10.0f),
				D3DXVECTOR3(sinf(D3DX_PI - g_player[nCnt].rot.y) * -20.0f, 0.0f, cosf(D3DX_PI - g_player[nCnt].rot.y) * 20.0f), 100, 0, nCnt);
			g_player[nCnt].nBullet--;
			PlaySound(SOUND_LABEL_SE_SHOT);
		}
	}
	else if (g_player[nCnt].weapon == WEAPON_RUNCHER && g_player[nCnt].motionType != MOTIONTYPE_MOVE)
	{// �����`���[
		if (GetKeyboardTrigger(KEYINFO_ATTACK) == true || BuDo(KEYINFO::KEYINFO_ATTACK, nCnt) == true)
		{
			g_player[nCnt].nKey = 0;
			g_player[nCnt].nCounterMotion = 0;
			WeaponAction(nCnt, g_player[nCnt].weapon);
			SetBullet(D3DXVECTOR3(
				g_player[nCnt].aModel[18].mtxWorld._41 + sinf(D3DX_PI - g_player[nCnt].rot.y) * -10.0f,
				g_player[nCnt].aModel[18].mtxWorld._42 + 25.0f,
				g_player[nCnt].aModel[18].mtxWorld._43 + cosf(D3DX_PI - g_player[nCnt].rot.y) * 10.0f),
				D3DXVECTOR3(sinf(D3DX_PI - g_player[nCnt].rot.y) * -20.0f, 0.0f, cosf(D3DX_PI - g_player[nCnt].rot.y) * 20.0f), 100, 2, nCnt);
			g_player[nCnt].nBullet--;
			PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}
	}
	else
	{
		if (GetKeyboardTrigger(KEYINFO_ATTACK) == true || BuDo(KEYINFO::KEYINFO_ATTACK, nCnt) == true)
		{// �ߐ�
			if (g_player[nCnt].motionType == MOTIONTYPE_NEUTRAL)
			{
				g_player[nCnt].nKey = 0;
				g_player[nCnt].nCounterMotion = 0;
				WeaponAction(nCnt, g_player[nCnt].weapon);
				//g_player[nCnt].motionType = MOTIONTYPE_ACTION;
			}
		}
	}

	if (g_player[nCnt].weapon != WEAPON_NONE && BuDo(KEYINFO::KEYINFO_WEAPON_DROP, nCnt) == true)
	{
		g_player[nCnt].weapon = WEAPON_NONE;
		g_player[nCnt].sr = SHORT_NONE;
		g_player[nCnt].nBullet = 0;
	}

	// �ړ��ʂ̉��Z
	g_player[nCnt].pos += g_player[nCnt].move;

	// ���f���̈ړ�
	if (GetKeyboardPress(KEYINFO_UP) == true || BuPu(KEYINFO::KEYINFO_UP,nCnt) == true)
	{
		if (g_player[nCnt].nMoveCnt < 20)
		{
			g_player[nCnt].nMoveCnt++;
		}

		if (g_player[nCnt].motionType != MOTIONTYPE_JUMP)
		{
			g_player[nCnt].motionType = MOTIONTYPE_MOVE;
		}
		if (GetKeyboardPress(KEYINFO_LEFT) == true || BuPu(KEYINFO::KEYINFO_LEFT,nCnt) == true)
		{// �������
			g_player[nCnt].move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * g_player[nCnt].fMove;
			g_player[nCnt].move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * g_player[nCnt].fMove;
			g_player[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true || BuPu(KEYINFO::KEYINFO_RIGHT,nCnt) == true)
		{// �E�����
			g_player[nCnt].move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * g_player[nCnt].fMove;
			g_player[nCnt].move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * g_player[nCnt].fMove;
			g_player[nCnt].rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
		}
		else
		{// �����
			g_player[nCnt].move.x += sinf(pCamera->rot.y) * g_player[nCnt].fMove;
			g_player[nCnt].move.z += cosf(pCamera->rot.y) * g_player[nCnt].fMove;
			g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true || BuPu(KEYINFO::KEYINFO_DOWN,nCnt) == true)
	{
		if (g_player[nCnt].nMoveCnt < MOVECNT_MAX)
		{
			g_player[nCnt].nMoveCnt++;
		}

		if (g_player[nCnt].motionType != MOTIONTYPE_JUMP)
		{
			g_player[nCnt].motionType = MOTIONTYPE_MOVE;
		}

		if (GetKeyboardPress(KEYINFO_LEFT) == true || BuPu(KEYINFO::KEYINFO_LEFT, nCnt) == true)
		{// ��������
			g_player[nCnt].move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * g_player[nCnt].fMove;
			g_player[nCnt].move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * g_player[nCnt].fMove;
			g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / 4;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true || BuPu(KEYINFO::KEYINFO_RIGHT, nCnt) == true)
		{// �E������
			g_player[nCnt].move.x -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * g_player[nCnt].fMove;
			g_player[nCnt].move.z += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * g_player[nCnt].fMove;
			g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / -4;
		}
		else
		{// ������
			g_player[nCnt].move.x += sinf(pCamera->rot.y - D3DX_PI) * g_player[nCnt].fMove;
			g_player[nCnt].move.z += cosf(pCamera->rot.y - D3DX_PI) * g_player[nCnt].fMove;
			g_player[nCnt].rotDest.y = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(KEYINFO_LEFT) == true || BuPu(KEYINFO::KEYINFO_LEFT, nCnt) == true)
	{// ������
		if (g_player[nCnt].nMoveCnt < MOVECNT_MAX)
		{
			g_player[nCnt].nMoveCnt++;
		}

		g_player[nCnt].move.x -= cosf(pCamera->rot.y) * g_player[nCnt].fMove;
		g_player[nCnt].move.z += sinf(pCamera->rot.y) * g_player[nCnt].fMove;
		g_player[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI / 2);

		if (g_player[nCnt].motionType != MOTIONTYPE_JUMP)
		{
			g_player[nCnt].motionType = MOTIONTYPE_MOVE;
		}
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true || BuPu(KEYINFO::KEYINFO_RIGHT, nCnt) == true)
	{// �E����
		if (g_player[nCnt].nMoveCnt < MOVECNT_MAX)
		{
			g_player[nCnt].nMoveCnt++;
		}

		g_player[nCnt].move.x += cosf(pCamera->rot.y) * g_player[nCnt].fMove;
		g_player[nCnt].move.z -= sinf(pCamera->rot.y) * g_player[nCnt].fMove;
		g_player[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI / -2);
		if (g_player[nCnt].motionType != MOTIONTYPE_JUMP)
		{
			g_player[nCnt].motionType = MOTIONTYPE_MOVE;
		}
	}
	else
	{
		if (g_player[nCnt].nMoveCnt > 0)
		{
			g_player[nCnt].nMoveCnt--;
		}
	}

	// �ړ����[�V��������ҋ@���[�V������
	if (g_player[nCnt].motionType == MOTIONTYPE_MOVE && g_player[nCnt].nMoveCnt == 0)
	{
		g_player[nCnt].nCounterMotion = 0;
		g_player[nCnt].nKey = 0;
		g_player[nCnt].motionType = MOTIONTYPE_NEUTRAL;
	}

	// �ړI�̉�]�p�̏��
	if (g_player[nCnt].rotDest.y - g_player[nCnt].rot.y < -D3DX_PI)
	{
		g_player[nCnt].rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player[nCnt].rotDest.y - g_player[nCnt].rot.y > D3DX_PI)
	{
		g_player[nCnt].rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	g_player[nCnt].rot.y += (g_player[nCnt].rotDest.y - g_player[nCnt].rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (g_player[nCnt].rot.y < -D3DX_PI)
	{
		g_player[nCnt].rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player[nCnt].rot.y > D3DX_PI)
	{
		g_player[nCnt].rot.y -= D3DX_PI * 2.0f;
	}

	// ������̌�������
	g_player[nCnt].move.x += (0.0f - g_player[nCnt].move.x) * SPEEDDOWN;
	g_player[nCnt].move.z += (0.0f - g_player[nCnt].move.z) * SPEEDDOWN;

	// �ړ����EX��
	if (g_player[nCnt].pos.x >= 1500.0f - g_player[nCnt].vtxMaxPlayer.x)
	{
		g_player[nCnt].pos.x = 1500.0f - g_player[nCnt].vtxMaxPlayer.x;
	}
	else if (g_player[nCnt].pos.x <= -1500.0f - g_player[nCnt].vtxMinPlayer.x)
	{
		g_player[nCnt].pos.x = -1500.0f - g_player[nCnt].vtxMinPlayer.x;
	}

	// �ړ����EZ��
	if (g_player[nCnt].pos.z >= 1500.0f - g_player[nCnt].vtxMaxPlayer.z)
	{
		g_player[nCnt].pos.z = 1500.0f - g_player[nCnt].vtxMaxPlayer.z;
	}
	else if (g_player[nCnt].pos.z <= -1500.0f - g_player[nCnt].vtxMinPlayer.z)
	{
		g_player[nCnt].pos.z = -1500.0f - g_player[nCnt].vtxMinPlayer.z;
	}
}

//==============================================================================
// �v���C���[�̍U���ʒu���f
//==============================================================================
void AttackParts(int nCnt)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRotAttack, mtxTransAttack;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X
	D3DXMATERIAL *pMat;

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �U������}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player[nCnt].as[g_player[nCnt].sr].mtxWorld);

	// �U������̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(
		&mtxRotAttack,
		g_player[nCnt].as[g_player[nCnt].sr].rot.y,
		g_player[nCnt].as[g_player[nCnt].sr].rot.x,
		g_player[nCnt].as[g_player[nCnt].sr].rot.z);
	D3DXMatrixMultiply(
		&g_player[nCnt].as[g_player[nCnt].sr].mtxWorld,
		&g_player[nCnt].as[g_player[nCnt].sr].mtxWorld,
		&mtxRotAttack);

	// �e�p�[�c�̈ʒu�𔽉f
	D3DXMatrixTranslation(
		&mtxTransAttack,
		g_player[nCnt].as[g_player[nCnt].sr].pos.x,
		g_player[nCnt].as[g_player[nCnt].sr].pos.y,
		g_player[nCnt].as[g_player[nCnt].sr].pos.z);
	D3DXMatrixMultiply(
		&g_player[nCnt].as[g_player[nCnt].sr].mtxWorld,
		&g_player[nCnt].as[g_player[nCnt].sr].mtxWorld,
		&mtxTransAttack);

	mtxParent = g_player[nCnt].aModel[g_player[nCnt].as[g_player[nCnt].sr].nParts].mtxWorld;

	// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɣ��蔭���p�[�c�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(
		&g_player[nCnt].as[g_player[nCnt].sr].mtxWorld,
		&g_player[nCnt].as[g_player[nCnt].sr].mtxWorld,
		&mtxParent);

	// ����̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].as[g_player[nCnt].sr].mtxWorld);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_player[nCnt].as[g_player[nCnt].sr].pBuffMatSphere->GetBufferPointer();

	pMat[0].MatD3D.Diffuse = g_player[nCnt].as[g_player[nCnt].sr].col;

	// �}�e���A���̐ݒ�
	pDevice->SetMaterial(&pMat[0].MatD3D);

	if (g_player[nCnt].as[g_player[nCnt].sr].bUse == true)
	{
		// ���f��(�p�[�c)�̕`��
		//g_player[nCnt].as[g_player[nCnt].sr].pMeshSphere->DrawSubset(nCnt);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// �U���̓����蔻��
//==============================================================================
void CollisionDamage(int nCnt,int nTarget,D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 aVec[COLLISION_PARTS];	// ��`���_���画��Ώۂւ̃x�N�g��

	for (int nCntVec = 0; nCntVec < COLLISION_PARTS; nCntVec++)
	{
		if (nCntVec == 0)
		{// ����
			aVec[nCntVec] = pos - g_player[nTarget].aPoint[nCntVec];
		}					    
		else if (nCntVec == 1)  
		{// ����				  
			aVec[nCntVec] = pos - g_player[nTarget].aPoint[nCntVec];
		}					    
		else if (nCntVec == 2)  
		{// �E��				  
			aVec[nCntVec] = pos - g_player[nTarget].aPoint[nCntVec];
		}					    
		else if (nCntVec == 3)  
		{// ��O				  
			aVec[nCntVec] = pos - g_player[nTarget].aPoint[nCntVec];
		}

		g_player[nTarget].attack.fGetDamage[nCntVec] = (g_player[nTarget].aVec[nCntVec].z * aVec[nCntVec].x) - (g_player[nTarget].aVec[nCntVec].x * aVec[nCntVec].z);
	}

	if (g_player[nCnt].as[g_player[nCnt].sr].bUse == true && g_player[nTarget].state != PLAYERSTATE_DAMAGE && g_player[nTarget].state != PLAYERSTATE_APPEAR)
	{
		if (g_player[nTarget].attack.fGetDamage[0] > 0.0f &&
			g_player[nTarget].attack.fGetDamage[1] > 0.0f &&
			g_player[nTarget].attack.fGetDamage[2] > 0.0f &&
			g_player[nTarget].attack.fGetDamage[3] > 0.0f)
		{
			g_player[nTarget].nCntState = 1;
			if (g_player[nTarget].sr == 0)
			{
				CalcuHp(nTarget, 40.0f, false);
				PlaySound(SOUND_LABEL_SE_SMASH_HIT);
			}
			else
			{
				CalcuHp(nTarget, 70.0f, false);
				PlaySound(SOUND_LABEL_SE_SLASH_HIT);
			}
			
			g_player[nTarget].state = PLAYERSTATE_DAMAGE;
		}
	}
}

//==============================================================================
// �e�̒Ǐ]
//==============================================================================
void SetPosShadow(int nPlayer,D3DXVECTOR3 pos)
{
	g_player[nPlayer].posShadow = pos;
}

//==============================================================================
// ����ۗ̕L���
//==============================================================================
void WeaponSet(int nCntPlayer,Weapon weapon)
{
	// ���[�J���ϐ��錾
	Player *pPlayer = &g_player[nCntPlayer];
	int nCnt = (pPlayer->nNumModel - pPlayer->nNumWeapon);

	for (int nCntWeapon = nCnt; nCntWeapon < pPlayer->nNumModel; nCntWeapon++)
	{
		if ((int)weapon != 0 && (int)weapon == nCntWeapon - nCnt + 1)
		{
			pPlayer->aModel[nCntWeapon].bUse = true;
		}
		else
		{
			pPlayer->aModel[nCntWeapon].bUse = false;
		}

		//switch (weapon)
		//{
		//case WEAPON_NONE:
		//	break;
		//case WEAPON_KNIFE:
		//	break;
		//case WEAPON_HANDGUN:
		//	break;
		//case WEAPON_MACHINEGUN:
		//	break;
		//case WEAPON_RUNCHER:
		//	break;
		//default: 
		//	break;
		//}
	}
}

//==============================================================================
// ���킲�Ƃ̃A�N�V�����Ǘ�
//==============================================================================
void WeaponAction(int nCntPlayer,Weapon weapon)
{
	Player *pPlayer = &g_player[nCntPlayer];

	switch(weapon)
	{
	case WEAPON_NONE:
		pPlayer->motionType = MOTIONTYPE_ACTION;
		break;

	case WEAPON_KNIFE:
		pPlayer->motionType = MOTIONTYPE_SLASH;
		break;

	case WEAPON_HANDGUN:
		pPlayer->motionType = MOTIONTYPE_SHOT;
		break;

	case WEAPON_MACHINEGUN:
		pPlayer->motionType = MOTIONTYPE_SHOT;
		break;

	case WEAPON_RUNCHER:
		pPlayer->motionType = MOTIONTYPE_RANCHER;
		break;

	default:
		break;
	}
}

//==============================================================================
// �e�̓����蔻��
//==============================================================================
bool CollisionBullet(D3DXVECTOR3 pos,int nType,int nPlayer)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 aVec[COLLISION_PARTS];	// ��`���_���画��Ώۂւ̃x�N�g��
	bool bBullet = true;
	
	for (int nCntVec = 0; nCntVec < COLLISION_PARTS; nCntVec++)
	{
		if (nCntVec == 0)
		{// ����
			aVec[nCntVec] = pos - g_player[nPlayer].aPoint[nCntVec];
		}
		else if (nCntVec == 1)
		{// ����				  
			aVec[nCntVec] = pos - g_player[nPlayer].aPoint[nCntVec];
		}
		else if (nCntVec == 2)
		{// �E��				  
			aVec[nCntVec] = pos - g_player[nPlayer].aPoint[nCntVec];
		}
		else if (nCntVec == 3)
		{// ��O				  
			aVec[nCntVec] = pos - g_player[nPlayer].aPoint[nCntVec];
		}

		g_player[nPlayer].attack.fGetDamage[nCntVec] = (g_player[nPlayer].aVec[nCntVec].z * aVec[nCntVec].x) - (g_player[nPlayer].aVec[nCntVec].x * aVec[nCntVec].z);
	}

	if (g_player[nPlayer].state != PLAYERSTATE_DAMAGE && g_player[nPlayer].state != PLAYERSTATE_APPEAR)
	{
		if (g_player[nPlayer].attack.fGetDamage[0] > 0.0f &&
			g_player[nPlayer].attack.fGetDamage[1] > 0.0f &&
			g_player[nPlayer].attack.fGetDamage[2] > 0.0f &&
			g_player[nPlayer].attack.fGetDamage[3] > 0.0f && 
			g_player[nPlayer].fHeight > pos.y &&
			g_player[nPlayer].pos.y < pos.y)
		{
			g_player[nPlayer].state = PLAYERSTATE_DAMAGE;
			bBullet = false;
			switch (nType)
			{
			case 0:
				CalcuHp(nPlayer, 50.0f, false);
				PlaySound(SOUND_LABEL_SE_SHOT_HIT);		// �������̍Đ�
				break;

			case 1:
				CalcuHp(nPlayer, 10.0f, false);
				PlaySound(SOUND_LABEL_SE_SHOT_HIT);
				break;

			case 2:
				CalcuHp(nPlayer, 200.0f, false);
				SetEffect(pos, 0.05f, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), 10.0f, 0.05f, 100);
				PlaySound(SOUND_LABEL_SE_EXPLOSION_HIT);
				break;

			default:
				break;
			}
		}
	}

	return bBullet;
}