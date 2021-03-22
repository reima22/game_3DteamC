//==============================================================================
//
// �A�C�e���̕`��kitem.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "item.h"
#include "game.h"
#include "shadow.h"
#include "particle.h"
#include "sound.h"
#include "player.h"
#include "object.h"
#include "time.h"
#include "stdlib.h"

//==============================================================================
// �}�N����`�@
//==============================================================================
#define ITEM_TURN	(0.05f)				// �A�C�e���̉�]���x
#define SET_ITEM_W	(10)					// �A�C�e���̔z�u��(��)
#define SET_ITEM_D	(10)					// �A�C�e���̔z�u��(���s)
#define SET_WIDTH	(450.0f)			// �A�C�e���̔z�u�J�n(��)
#define SET_DEPTH	(450.0f)			// �A�C�e���̔z�u�J�n(���s)
#define SET_HALF_W	(100.0f)	// �A�C�e���̔z�u�Ԋu(��)
#define SET_HALF_D	(100.0f)	// �A�C�e���̔z�u�Ԋu(���s) 

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPD3DXMESH g_pMeshItem = NULL;			// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatItem = NULL;		// �}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatItem = 0;				// �}�e���A���̐�
ITEM g_aItem[MAX_ITEM];					// �A�C�e���̏��
int g_nCntItem;							// �z�u���J�E���g

//==============================================================================
// �A�C�e���̏���������
//==============================================================================
HRESULT InitItem(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	ITEM *pItem;

	// �����������猻���������O
	srand((unsigned int)time(0));

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̎擾
	pItem = &g_aItem[0];

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data/MODEL/coin.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatItem,
		NULL,
		&g_nNumMatItem,
		&g_pMeshItem);

	// �ϐ��̏�����
	g_nCntItem = 0;

	// ���[�J���ϐ��錾
	int nNumVtx;	// ���_��
	DWORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = g_pMeshItem->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem->GetFVF());

	// �\���̂̏�����
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		pItem->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pItem->nType = NULL;
		pItem->bUse = false;
		pItem->vtxMaxObject = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
		pItem->vtxMinObject = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
		//pItem->fAnim = 0.0f;
		//if (nCntItem == nRand)
		//{
		//	pItem->bHiScore = true;
		//}
		//else
		//{
		//	pItem->bHiScore = false;
		//}
	}

	// ���_���W�̔�r
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// ���_�o�b�t�@�����b�N
		g_pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

			// �e���W�̍ő�l�̔�r
			if (g_aItem[nCntItem].vtxMaxObject.x < vtx.x)
			{
				g_aItem[nCntItem].vtxMaxObject.x = vtx.x;
			}
			if (g_aItem[nCntItem].vtxMaxObject.y < vtx.y)
			{
				g_aItem[nCntItem].vtxMaxObject.y = vtx.y;
			}
			if (g_aItem[nCntItem].vtxMaxObject.z < vtx.z)
			{
				g_aItem[nCntItem].vtxMaxObject.z = vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (g_aItem[nCntItem].vtxMinObject.x > vtx.x)
			{
				g_aItem[nCntItem].vtxMinObject.x = vtx.x;
			}
			if (g_aItem[nCntItem].vtxMinObject.y > vtx.y)
			{
				g_aItem[nCntItem].vtxMinObject.y = vtx.y;
			}
			if (g_aItem[nCntItem].vtxMinObject.z > vtx.z)
			{
				g_aItem[nCntItem].vtxMinObject.z = vtx.z;
			}

			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@���A�����b�N
		g_pMeshItem->UnlockVertexBuffer();
	}

	//// �A�C�e���̔z�u
	//for (int nCntDep = 0; nCntDep < SET_ITEM_D; nCntDep++)
	//{
	//	for (int nCntWid = 0; nCntWid < SET_ITEM_W; nCntWid++)
	//	{
	//		SetItem(D3DXVECTOR3(-SET_WIDTH + (SET_HALF_W * (float)nCntWid), 0.0f, SET_DEPTH - (SET_HALF_D * (float)nCntDep)));
	//	}
	//}

	return S_OK;
}

//==============================================================================
// �A�C�e���̏I������
//==============================================================================
void UninitItem(void)
{
	// ���b�V���̔j��
	if (g_pMeshItem != NULL)
	{
		g_pMeshItem->Release();
		g_pMeshItem = NULL;
	}

	// �}�e���A���̔j��
	if (g_pBuffMatItem != NULL)
	{
		g_pBuffMatItem->Release();
		g_pBuffMatItem = NULL;
	}
}

//==============================================================================
// �A�C�e���̍X�V����
//==============================================================================
void UpdateItem(void)
{
	// ���[�J���ϐ��錾
	ITEM *pItem = &g_aItem[0];

	// �A�C�e���̉�]
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItem++)
	{
		if (pItem->bUse == true)
		{// �g�p��Ԃ�
			pItem->rot.y += ITEM_TURN;	// �p�x�̉��Z

			if (pItem->rot.y > D3DX_PI)
			{// �p�x�̐��l�P����
				pItem->rot.y -= D3DX_PI * 2.0f;
			}
		}
	}
}

//==============================================================================
// �A�C�e���̕`�揈��
//==============================================================================
void DrawItem(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
	ITEM *pItem = &g_aItem[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItem++)
	{
		if (pItem->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pItem->mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pItem->rot.y, pItem->rot.x, pItem->rot.z);
			D3DXMatrixMultiply(&pItem->mtxWorld, &pItem->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pItem->pos.x, pItem->pos.y, pItem->pos.z);
			D3DXMatrixMultiply(&pItem->mtxWorld, &pItem->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pItem->mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatItem->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatItem; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_pMeshItem->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==============================================================================
// �A�C�e���̐ݒ�
//==============================================================================
void SetItem(D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	ITEM *pItem = &g_aItem[0];

	// �A�C�e���̐ݒ�
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItem++)
	{
		if (pItem->bUse == false)
		{// �A�C�e�������g�p��
			pItem->pos = pos;	// �ʒu

			// �e���_�ʒu
			pItem->posPoint[0] = D3DXVECTOR3(pItem->pos.x + pItem->vtxMinObject.x, 0.0f, pItem->pos.z + pItem->vtxMinObject.x);
			pItem->posPoint[1] = D3DXVECTOR3(pItem->pos.x + pItem->vtxMinObject.x, 0.0f, pItem->pos.z + pItem->vtxMaxObject.x);
			pItem->posPoint[2] = D3DXVECTOR3(pItem->pos.x + pItem->vtxMaxObject.x, 0.0f, pItem->pos.z + pItem->vtxMaxObject.x);
			pItem->posPoint[3] = D3DXVECTOR3(pItem->pos.x + pItem->vtxMaxObject.x, 0.0f, pItem->pos.z + pItem->vtxMinObject.x);

			// �S�ӂ̃x�N�g��
			pItem->vecPoint[0] = pItem->posPoint[1] - pItem->posPoint[0];
			pItem->vecPoint[1] = pItem->posPoint[2] - pItem->posPoint[1];
			pItem->vecPoint[2] = pItem->posPoint[3] - pItem->posPoint[2];
			pItem->vecPoint[3] = pItem->posPoint[0] - pItem->posPoint[3];

			// �e�̐ݒ�
			pItem->nIdx = SetShadow(D3DXVECTOR3(pItem->pos.x, 0.0f, pItem->pos.z), 10.0f, 10.0f);

			g_nCntItem++;		// �z�u�A�C�e�����̉��Z

			pItem->bUse = true;	// �g�p��Ԃֈڍs

			break;
		}
	}
}

//==============================================================================
// �G�̎擾
//==============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}

//==============================================================================
// �����_���Ńn�C�X�R�A�A�C�e���̑I��
//==============================================================================
int RandItem(void)
{
	//// ���[�J���ϐ��錾
	//ITEM *pItem;
	//int nStage = GetStage();
	int nHigh = 0;

	//// �A�C�e���̎擾
	//pItem = &g_aItem[0];

	//if (nStage == 0)
	//{
	//	nHigh = rand() % COIN_STAGE1;
	//}
	//else if (nStage == 1)
	//{
	//	nHigh = rand() % COIN_STAGE2;
	//}
	//else if(nStage == 2)
	//{
	//	nHigh = rand() % COIN_STAGE3;
	//}

	return nHigh;
}

//==============================================================================
// �A�C�e���̎擾
//==============================================================================
void TouchItem(D3DXVECTOR3 *pPos, float fInRadius, float fHeight,int nCntPlayer)
{
	// ���[�J���ϐ��錾
	ITEM *pItem = &g_aItem[0];
	Player *pPlayer = GetPlayer();	// �v���C���[�̎擾
	D3DXVECTOR3 aVec[FOUR_POINT];	// �e���_����v���C���[�ւ̃x�N�g��
	float fItemVec[FOUR_POINT];		// ����p�ϐ�
	D3DXVECTOR3 pos = *pPos;		// �v���C���[�̈ʒu

	pPlayer += nCntPlayer;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{// �A�C�e���̊O�ϓ����蔻��
			for (int nCnt = 0; nCnt < FOUR_POINT; nCnt++)
			{
				switch (nCnt)
				{
				case 0:	// ����
					aVec[nCnt] = pos + D3DXVECTOR3(fInRadius, 0.0f, 0.0f) - pItem->posPoint[nCnt];
					break;

				case 1:	// ����
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, -fInRadius) - pItem->posPoint[nCnt];
					break;

				case 2:	// �E��
					aVec[nCnt] = pos + D3DXVECTOR3(-fInRadius, 0.0f, 0.0f) - pItem->posPoint[nCnt];
					break;

				case 3:	// ��O��
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fInRadius) - pItem->posPoint[nCnt];
					break;
				}

				// ����p���l�Z�o
				fItemVec[nCnt] = (pItem->vecPoint[nCnt].z * aVec[nCnt].x) - (pItem->vecPoint[nCnt].x * aVec[nCnt].z);
			}

			// �A�C�e���Ƃ̐ڐG
			if (fItemVec[0] > 0.0f && fItemVec[1] > 0.0f && fItemVec[2] > 0.0f && fItemVec[3] > 0.0f && 
				pPlayer->pos.y <= (pItem->pos.y + pItem->vtxMaxObject.y) && (pPlayer->pos.y + pPlayer->fHeight) >= pItem->pos.y)
			{// �A�C�e���̎擾
				// �G�t�F�N�g�̔���
				SetEffect(D3DXVECTOR3(pItem->pos.x, pItem->pos.y + 5.0f, pItem->pos.z), 0.01f, D3DXCOLOR(1.0f, 1.0f, 0.1f, 1.0f), 5.0f, 0.05f, 30);
				PlaySound(SOUND_LABEL_SE_COIN);	// ���ʉ��̍Đ�
				Shadow *pShadow = GetShadow();	// �e�̎擾
				pShadow += pItem->nIdx;
				pShadow->bUse = false;			// �e�̏���
				pItem->bUse = false;			// �A�C�e���̏���
				g_nCntItem--;					// �A�C�e���J�E���g�̌��Z
				if (g_nCntItem <= 0)
				{// �A�C�e���S�擾�����Ƃ�
					pPlayer->state = PLAYERSTATE_CLEAR;
				}
				break;
			}
		}
	}
}