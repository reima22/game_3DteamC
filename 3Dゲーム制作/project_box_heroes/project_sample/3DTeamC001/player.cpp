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
#include "math.h"
#include <stdio.h>

//==============================================================================
// �}�N����`
//==============================================================================
#define PLAYER_MOVE		(1.0f)	// �ړ���
#define PLAYER_TURN		(0.1f)	// ����
#define PLAYER_NUM		(2)		// �v���C���[�̐�
#define TEXT_LENGTH		(128)	// �e�L�X�g�ǂݍ��݂̍ő吔
#define DATA_LENGTH		(64)	// �f�[�^�ǂݍ��݂̍ő吔
#define MOVE_MIN		(0.5f)	// �ړ����[�V�������̍ŏ��ړ���
#define MOVECNT_MAX		(20)	// �ړ����[�V�����ȍ~�J�E���g�ő�l

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
Player g_player[PLAYER_NUM];	// �v���C���[�̍\����

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
	
	LoadMotion();

	g_player[0].pos = D3DXVECTOR3(-50.0f, 20.0f, 0.0f);

	g_player[1].pos = D3DXVECTOR3(50.0f, 20.0f, 0.0f);
	
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
	{
		// X�t�@�C���̓ǂݍ���
		for (int nCnt = 0; nCnt < g_player[nCntPlayer].nNumModel; nCnt++)
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
		}

		// ���[�J���ϐ��錾
		int nNumVtx;			// ���_��
		DWORD sizeFVF;			// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^

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
		g_player[nCntPlayer].nLife = MAX_LIFE;
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

		// �e�̐ݒ�
		g_player[nCntPlayer].nIdx = SetShadow(D3DXVECTOR3(g_player[nCntPlayer].pos.x, 0.0f, g_player[nCntPlayer].pos.z), 10.0f, 10.0f);

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
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
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
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdatePlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
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

		// �����蔻��
		if(nCntPlayer == 0 && g_player[1].state != PLAYERSTATE_DAMAGE && g_player[1].state != PLAYERSTATE_APPEAR)
		{
			CollisionDamage(nCntPlayer, 1, 
				D3DXVECTOR3(
					g_player[1].pos.x + sinf(D3DX_PI - g_player[1].rot.y) * -20.0f, 
					20.0f, 
					g_player[1].pos.z + cosf(D3DX_PI - g_player[1].rot.y) * 20.0f));
		}
		else if (nCntPlayer == 1 && g_player[0].state != PLAYERSTATE_DAMAGE&& g_player[0].state != PLAYERSTATE_APPEAR)
		{
			CollisionDamage(nCntPlayer, 0, 
				D3DXVECTOR3(
					g_player[0].pos.x + sinf(D3DX_PI - g_player[0].rot.y) * -20.0f,
					20.0f, 
					g_player[0].pos.z + cosf(D3DX_PI - g_player[0].rot.y) * 20.0f));
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

	for (int nCntPlayer = 0; nCntPlayer < PLAYER_NUM; nCntPlayer++)
	{
		// �v���C���[�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_player[nCntPlayer].mtxWorld);

		// �v���C���[�̌����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player[nCntPlayer].rot.y, g_player[nCntPlayer].rot.x, g_player[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&g_player[nCntPlayer].mtxWorld, &g_player[nCntPlayer].mtxWorld, &mtxRot);

		// �v���C���[�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_player[nCntPlayer].pos.x, g_player[nCntPlayer].pos.y, g_player[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&g_player[nCntPlayer].mtxWorld, &g_player[nCntPlayer].mtxWorld, &mtxTrans);

		// �v���C���[�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_player[nCntPlayer].mtxWorld);

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
				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_player[nCntPlayer].aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
			}
		}

		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
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

	if (g_player[nCntPlayer].attack.nCntFrameTotal < g_player[nCntPlayer].nFrameTotal[motionType])
	{
		g_player[nCntPlayer].attack.nCntFrameTotal++;
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
				if (g_player[nCntPlayer].motionType != MOTIONTYPE_JUMP)
				{// �W�����v�ȊO�ŃL�[�I�������Z�b�g
					g_player[nCntPlayer].nCounterMotion = 0;
				}

				if (g_player[nCntPlayer].nKey == g_player[nCntPlayer].nNumKey - 1 && g_player[nCntPlayer].bLoopMotion == true)
				{// ���[�v����Ƃ�
					g_player[nCntPlayer].nKey = 0;
					g_player[nCntPlayer].attack.nCntFrameTotal = 0;
				}
				else if (g_player[nCntPlayer].nKey == g_player[nCntPlayer].nNumKey - 2 && g_player[nCntPlayer].bLoopMotion == false)
				{// ���[�v�����I������Ƃ�
					if (g_player[nCntPlayer].motionTypeOld != MOTIONTYPE_JUMP)
					{// ���O���W�����v�ȊO�̎�
						g_player[nCntPlayer].motionType = MOTIONTYPE_NEUTRAL;	// �j���[�g�����ֈڍs
						g_player[nCntPlayer].attack.nCntFrameTotal = 0;
						if (g_player[nCntPlayer].motionTypeOld == MOTIONTYPE_LANDING)
						{
							break;

						}
					}
				}
				else if (g_player[nCntPlayer].nKey < g_player[nCntPlayer].nNumKey)
				{// �L�[�̃J�E���g
					g_player[nCntPlayer].nKey++;
				}
			}
			else if (g_player[nCntPlayer].motionTypeOld != g_player[nCntPlayer].motionType && g_player[nCntPlayer].motionTypeOld != MOTIONTYPE_JUMP)
			{// ���[�V�����ω���	
				g_player[nCntPlayer].nKey = 0;
				g_player[nCntPlayer].nCounterMotion = 0;
				g_player[nCntPlayer].bMotionChange = true;
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
				g_player[nCntPlayer].bMotionChange = false;
			}
		}

		// �Ō��̓����蔻��
		if (g_player[nCntPlayer].motionType == MOTIONTYPE_ACTION)
		{
			if (g_player[nCntPlayer].attack.nCntFrameTotal >= g_player[nCntPlayer].attack.nStartFrame &&
			 g_player[nCntPlayer].attack.nCntFrameTotal <= g_player[nCntPlayer].attack.nEndFrame)
			{// �J�E���g�͈͓��ŗL��
				g_player[nCntPlayer].attack.bUse = true;
			}
			else
			{// ����ȊO
				g_player[nCntPlayer].attack.bUse = false;
			}
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
	FILE *pFile;
	char aEqual[2] = { NULL };					// �u=�v�ǂݎ��p�ϐ�
	bool bComment = false;						// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = {NULL};			// �e�L�X�g�ǂݎ��p�ϐ�
	char aCharaSet[DATA_LENGTH] = { NULL };		// �L�����f�[�^�ǂݎ��p�ϐ�
	char aPartsSet[DATA_LENGTH] = { NULL };		// �p�[�c�f�[�^�ǂݎ��p�ϐ�
	char aMotionSet[DATA_LENGTH] = { NULL };	// ���[�V�����ǂݎ��p�ϐ�
	char aKeySet[DATA_LENGTH] = { NULL };		// �L�[�ݒ���ǂݎ��p�ϐ�
	char aKey[DATA_LENGTH] = { NULL };			// �L�[���ǂݎ��p�ϐ�

	Select *pSelect = GetSelect();

	// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];					
	char *pCharaSet = &aCharaSet[0];
	char *pPartsSet = &aPartsSet[0];
	char *pMotionSet = &aMotionSet[0];
	char *pKeySet = &aKeySet[0];
	char *pKey = &aKey[0];

	for (int nCnt = 0; nCnt < PLAYER_NUM; nCnt++)
	{
		switch (pSelect->chara[nCnt])
		{
		case CHARA_0:
			// �f�[�^�̓ǂݍ���
			pFile = fopen("data/TEXT/player_horiai.txt", "r");

			break;

		case CHARA_1:
			// �f�[�^�̓ǂݍ���
			pFile = fopen("data/TEXT/player_horiai.txt", "r");

			break;

		case CHARA_2:
			// �f�[�^�̓ǂݍ���
			pFile = fopen("data/TEXT/motion_runningman.txt", "r");

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
									fscanf(pFile, "%d", &g_player[nCnt].attack.nParts);
									fscanf(pFile, "%f", &g_player[nCnt].attack.pos.x);
									fscanf(pFile, "%f", &g_player[nCnt].attack.pos.y);
									fscanf(pFile, "%f", &g_player[nCnt].attack.pos.z);
									fscanf(pFile, "%f", &g_player[nCnt].attack.fRadius);
									fscanf(pFile, "%d", &g_player[nCnt].attack.nStartFrame);
									fscanf(pFile, "%d", &g_player[nCnt].attack.nEndFrame);
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
		PlaySound(SOUND_LABEL_SE_HIT000);			// �������̍Đ�
		pPlayer->move.x *= -1;						// �ړ��͂𔽓]
		pPlayer->move.z *= -1;
		pPlayer->move.y = 5.0f;						// �v���C���[���΂�
		pPlayer->bJump = true;
		pPlayer->nKey = 0;							// �L�[�J�E���g�̃��Z�b�g
		pPlayer->nCounterMotion = 0;				// ���[�V�����J�E���g�̃��Z�b�g
		pPlayer->motionType = MOTIONTYPE_DAMAGE;	// �_���[�W���[�V�����̎��s

		// �̗͂��c��ꍇ
		if (pPlayer->nLife > 0)
		{
			pPlayer->nCntState--;					// ��ԃJ�E���g�̌��Z
			if (pPlayer->nCntState <= 0)
			{// ���̏�Ԃֈڍs
				pPlayer->nCntState = 120;
				pPlayer->state = PLAYERSTATE_APPEAR;
			}
		}
		else
		{// �̗͂�0�̎�
			pPlayer->state = PLAYERSTATE_GAMEOVER;		// �Q�[���[�I�[�o�[
		}

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
				g_player[nCnt].move.y = 5.0f;
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
	if (GetKeyboardTrigger(KEYINFO_ATTACK) == true || BuDo(KEYINFO::KEYINFO_ATTACK,nCnt) == true)
	{
		if (g_player[nCnt].motionType == MOTIONTYPE_NEUTRAL)
		{
			g_player[nCnt].nKey = 0;
			g_player[nCnt].nCounterMotion = 0;
			g_player[nCnt].motionType = MOTIONTYPE_ACTION;
		}
	}

	// �ړ��ʂ̉��Z
	g_player[nCnt].pos += g_player[nCnt].move;

	// �e�̒Ǐ]
	SetPositionShadow(g_player[nCnt].nIdx, D3DXVECTOR3(g_player[nCnt].pos.x, 0.0f, g_player[nCnt].pos.z));

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
			g_player[nCnt].move.x -= cosf(pCamera->rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player[nCnt].move.z += sinf(pCamera->rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player[nCnt].rotDest.y = pCamera->rot.y + (D3DX_PI * 3 / 4);
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true || BuPu(KEYINFO::KEYINFO_RIGHT,nCnt) == true)
		{// �E�����
			g_player[nCnt].move.x += cosf(pCamera->rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player[nCnt].move.z -= sinf(pCamera->rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player[nCnt].rotDest.y = pCamera->rot.y - (D3DX_PI * 3 / 4);
		}
		else
		{// �����
			g_player[nCnt].move.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player[nCnt].move.z += cosf(pCamera->rot.y) * PLAYER_MOVE;
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
			g_player[nCnt].move.x += cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player[nCnt].move.z -= sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / 4;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true || BuPu(KEYINFO::KEYINFO_RIGHT, nCnt) == true)
		{// �E������
			g_player[nCnt].move.x -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player[nCnt].move.z += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player[nCnt].rotDest.y = pCamera->rot.y + D3DX_PI / -4;
		}
		else
		{// ������
			g_player[nCnt].move.x += sinf(pCamera->rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player[nCnt].move.z += cosf(pCamera->rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player[nCnt].rotDest.y = pCamera->rot.y;
		}
	}
	else if (GetKeyboardPress(KEYINFO_LEFT) == true || BuPu(KEYINFO::KEYINFO_LEFT, nCnt) == true)
	{// ������
		if (g_player[nCnt].nMoveCnt < MOVECNT_MAX)
		{
			g_player[nCnt].nMoveCnt++;
		}

		g_player[nCnt].move.x -= cosf(pCamera->rot.y) * PLAYER_MOVE;
		g_player[nCnt].move.z += sinf(pCamera->rot.y) * PLAYER_MOVE;
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

		g_player[nCnt].move.x += cosf(pCamera->rot.y) * PLAYER_MOVE;
		g_player[nCnt].move.z -= sinf(pCamera->rot.y) * PLAYER_MOVE;
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

	//// �ړ����EX��
	//if (g_player[nCnt].pos.x >= 500.0f - g_vtxMaxPlayer.x)
	//{
	//	g_player[nCnt].pos.x = 500.0f - g_vtxMaxPlayer.x;
	//}
	//else if (g_player[nCnt].pos.x <= -500.0f - g_vtxMinPlayer.x)
	//{
	//	g_player[nCnt].pos.x = -500.0f - g_vtxMinPlayer.x;
	//}

	//// �ړ����EZ��
	//if (g_player[nCnt].pos.z >= 500.0f - g_vtxMaxPlayer.z)
	//{
	//	g_player[nCnt].pos.z = 500.0f - g_vtxMaxPlayer.z;
	//}
	//else if (g_player[nCnt].pos.z <= -500.0f - g_vtxMinPlayer.z)
	//{
	//	g_player[nCnt].pos.z = -500.0f - g_vtxMinPlayer.z;
	//}
}

//==============================================================================
// �v���C���[�̍U���ʒu���f
//==============================================================================
void AttackParts(int nCnt)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRotAttack, mtxTransAttack;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

	//g_player[nCnt].attack.pos = g_player[nCnt].attack.AttackCollision;

	// �U������}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player[nCnt].attack.mtxWorld);

	// �U������̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(
		&mtxRotAttack,
		g_player[nCnt].attack.rot.y,
		g_player[nCnt].attack.rot.x,
		g_player[nCnt].attack.rot.z);
	D3DXMatrixMultiply(
		&g_player[nCnt].attack.mtxWorld,
		&g_player[nCnt].attack.mtxWorld,
		&mtxRotAttack);

	// �e�p�[�c�̈ʒu�𔽉f
	D3DXMatrixTranslation(
		&mtxTransAttack,
		g_player[nCnt].attack.pos.x,
		g_player[nCnt].attack.pos.y,
		g_player[nCnt].attack.pos.z);
	D3DXMatrixMultiply(
		&g_player[nCnt].attack.mtxWorld,
		&g_player[nCnt].attack.mtxWorld,
		&mtxTransAttack);

	mtxParent = g_player[nCnt].aModel[g_player[nCnt].attack.nParts].mtxWorld;

	// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɣ��蔭���p�[�c�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(
		&g_player[nCnt].attack.mtxWorld,
		&g_player[nCnt].attack.mtxWorld,
		&mtxParent);

	// ����̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player[nCnt].attack.mtxWorld);
}


void CollisionDamage(int nCnt,int nTarget,D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 aVec[COLLISION_PARTS];	// ��`���_���画��Ώۂւ̃x�N�g��

	for (int nCntVec = 0; nCntVec < COLLISION_PARTS; nCntVec++)
	{
		if (nCntVec == 0)
		{// ����
			aVec[nCntVec] = pos - g_player[nCnt].aPoint[nCntVec];
		}					    
		else if (nCntVec == 1)  
		{// ����				  
			aVec[nCntVec] = pos - g_player[nCnt].aPoint[nCntVec];
		}					    
		else if (nCntVec == 2)  
		{// �E��				  
			aVec[nCntVec] = pos - g_player[nCnt].aPoint[nCntVec];
		}					    
		else if (nCntVec == 3)  
		{// ��O				  
			aVec[nCntVec] = pos - g_player[nCnt].aPoint[nCntVec];
		}

		g_player[nTarget].attack.fGetDamage[nCntVec] = (g_player[nCnt].aVec[nCntVec].z * aVec[nCntVec].x) - (g_player[nCnt].aVec[nCntVec].x * aVec[nCntVec].z);
	}

	if (g_player[0].attack.bUse == true && g_player[1].state != PLAYERSTATE_DAMAGE)
	{
		if (g_player[1].attack.fGetDamage[0] > 0.0f && 
			g_player[1].attack.fGetDamage[1] > 0.0f && 
			g_player[1].attack.fGetDamage[2] > 0.0f && 
			g_player[1].attack.fGetDamage[3] > 0.0f)
		{
			g_player[1].nCntState = 1;
			g_player[1].state = PLAYERSTATE_DAMAGE;
		}
	}
	else if (g_player[1].attack.bUse == true && g_player[0].state != PLAYERSTATE_DAMAGE)
	{
		if (g_player[0].attack.fGetDamage[0] > 0.0f &&
			g_player[0].attack.fGetDamage[1] > 0.0f &&
			g_player[0].attack.fGetDamage[2] > 0.0f &&
			g_player[0].attack.fGetDamage[3] > 0.0f)
		{
			g_player[0].nCntState = 1;
			g_player[0].state = PLAYERSTATE_DAMAGE;
		}
	}
}