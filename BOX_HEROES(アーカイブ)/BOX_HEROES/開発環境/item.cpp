//==============================================================================
//
// �A�C�e���̕`��kitem.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "item.h"
#include "game.h"
#include "shadow.h"
#include "particle.h"
#include "sound.h"
#include "player.h"
#include "object.h"
#include "time.h"
#include "select.h"
#include "stdlib.h"
#include <stdio.h>

//==============================================================================
// �}�N����`�@
//==============================================================================
#define ITEM_TURN		(0.05f)		// �A�C�e���̉�]���x
#define ITEM_SET_MAX	(8)			// �z�u����A�C�e���̍ő吔

#define SET_0_0			(D3DXVECTOR3(-400.0f, 0.0f, 0.0f))
#define SET_0_1			(D3DXVECTOR3(400.0f, 0.0f, 0.0f))
#define SET_0_2			(D3DXVECTOR3(0.0f, 0.0f, -400.0f))
#define SET_0_3			(D3DXVECTOR3(0.0f, 0.0f, 400.0f))
#define SET_0_4			(D3DXVECTOR3(400.0f, 0.0f, 400.0f))
#define SET_0_5			(D3DXVECTOR3(400.0f, 0.0f, -400.0f))
#define SET_0_6			(D3DXVECTOR3(-400.0f, 0.0f, 400.0f))
#define SET_0_7			(D3DXVECTOR3(-400.0f, 0.0f, -400.0f))

//#define SET_1_0			(D3DXVECTOR3(-400.0f,0.0f,0.0f))
//#define SET_1_1			(D3DXVECTOR3(400.0f,0.0f,0.0f))
//#define SET_1_2			(D3DXVECTOR3(0.0f,0.0f,-400.0f))
//#define SET_1_3			(D3DXVECTOR3(0.0f,0.0f,400.0f))
//#define SET_1_4			(D3DXVECTOR3(-400.0f, 0.0f, 400.0f))
//#define SET_1_5			(D3DXVECTOR3(400.0f, 0.0f, -400.0f))
//#define SET_1_6			(D3DXVECTOR3(400.0f, 0.0f, -400.0f))
//#define SET_1_7			(D3DXVECTOR3(-400.0f, 0.0f, 400.0f))
//
//#define SET_2_0			(D3DXVECTOR3(-400.0f, 0.0f, 0.0f))
//#define SET_2_1			(D3DXVECTOR3(400.0f, 0.0f, 0.0f))
//#define SET_2_2			(D3DXVECTOR3(0.0f, 0.0f, -400.0f))
//#define SET_2_3			(D3DXVECTOR3(0.0f, 0.0f, 400.0f))
//#define SET_2_4			(D3DXVECTOR3(-400.0f, 0.0f, 400.0f))
//#define SET_2_5			(D3DXVECTOR3(400.0f, 0.0f, -400.0f))
//#define SET_2_6			(D3DXVECTOR3(400.0f, 0.0f, -400.0f))
//#define SET_2_7			(D3DXVECTOR3(-400.0f, 0.0f, 400.0f))

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
Item g_Item;	// �A�C�e���̏��
D3DXVECTOR3 g_RandPos[ITEM_SET_MAX];	// �����_���̃A�C�e���z�u�ʒu

//==============================================================================
// �A�C�e���̏���������
//==============================================================================
HRESULT InitItem(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	ItemTypeInfo *pItemType = &g_Item.typeinfo[0];
	ItemInfo *pItemInfo = &g_Item.iteminfo[0];

	// ���[�J���ϐ��錾
	int nNumVtx[ITEMTYPE_MAX];	// ���_��
	DWORD sizeFVF[ITEMTYPE_MAX];	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	// �����������猻���������O
	srand((unsigned int)time(0));

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	LoadItem();

	for (int nCnt = 0; nCnt < ITEM_SET_MAX; nCnt++)
	{
		//g_RandPos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Item.iteminfo[nCnt].bSet = false;
	}
	g_RandPos[0] = SET_0_0;
	g_RandPos[1] = SET_0_1;
	g_RandPos[2] = SET_0_2;
	g_RandPos[3] = SET_0_3;
	g_RandPos[4] = SET_0_4;
	g_RandPos[5] = SET_0_5;
	g_RandPos[6] = SET_0_6;
	g_RandPos[7] = SET_0_7;

	for (int nCntItem = 0; nCntItem < g_Item.nNumType; nCntItem++,pItemType++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(
			pItemType->aFileName,
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&pItemType->pBuffMatItem,
			NULL,
			&pItemType->nNumMatItem,
			&pItemType->pMeshItem);

		// ���_�����擾
		nNumVtx[nCntItem] = pItemType->pMeshItem->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		sizeFVF[nCntItem] = D3DXGetFVFVertexSize(pItemType->pMeshItem->GetFVF());

		// ���_�o�b�t�@�����b�N
		pItemType->pMeshItem->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx[nCntItem]; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

			// �e���W�̍ő�l�̔�r
			if (pItemType->vtxMaxItem.x < vtx.x)
			{
				pItemType->vtxMaxItem.x = vtx.x;
			}
			if (pItemType->vtxMaxItem.y < vtx.y)
			{
				pItemType->vtxMaxItem.y = vtx.y;
			}
			if (pItemType->vtxMaxItem.z < vtx.z)
			{
				pItemType->vtxMaxItem.z = vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (pItemType->vtxMinItem.x > vtx.x)
			{
				pItemType->vtxMinItem.x = vtx.x;
			}
			if (pItemType->vtxMinItem.y > vtx.y)
			{
				pItemType->vtxMinItem.y = vtx.y;
			}
			if (pItemType->vtxMinItem.z > vtx.z)
			{
				pItemType->vtxMinItem.z = vtx.z;
			}

			if (pItemType->vtxMinItem.x > pItemType->vtxMinItem.z)
			{
				pItemType->vtxMinItem.z = pItemType->vtxMinItem.x;
			}
			if (pItemType->vtxMinItem.x < pItemType->vtxMinItem.z)
			{
				pItemType->vtxMinItem.x = pItemType->vtxMinItem.z;
			}

			if (pItemType->vtxMaxItem.x < pItemType->vtxMaxItem.z)
			{
				pItemType->vtxMaxItem.x = pItemType->vtxMaxItem.z;
			}
			if (pItemType->vtxMaxItem.x > pItemType->vtxMaxItem.z)
			{
				pItemType->vtxMaxItem.z = pItemType->vtxMaxItem.x;
			}

			pVtxBuff += sizeFVF[nCntItem];	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		// ���_�o�b�t�@���A�����b�N
		pItemType->pMeshItem->UnlockVertexBuffer();
	}

	// �\���̂̏�����
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItemInfo++)
	{
		pItemInfo->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItemInfo->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItemInfo->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pItemInfo->bUse = false;
		pItemInfo->vtxMaxItem = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
		pItemInfo->vtxMinItem = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	}
	g_Item.nSetItem = 0;

	// �A�C�e���̔z�u
	//SetItem(D3DXVECTOR3(-500.0f, 15.0f, 0.0f), 0);
	//SetItem(D3DXVECTOR3(-400.0f, 15.0f, 0.0f), 1);
	//SetItem(D3DXVECTOR3(-600.0f, 15.0f, 0.0f), 2);
	//SetItem(D3DXVECTOR3(-800.0f, 15.0f, 0.0f), 3);

	return S_OK;
}

//==============================================================================
// �A�C�e���̏I������
//==============================================================================
void UninitItem(void)
{
	// ���[�J���ϐ��錾
	ItemTypeInfo *pItemType = &g_Item.typeinfo[0];

	// ���b�V���̔j��
	for (int nCntItem = 0; nCntItem < g_Item.nNumType; nCntItem++,pItemType++)
	{
		if (pItemType->pMeshItem != NULL)
		{
			pItemType->pMeshItem->Release();
			pItemType->pMeshItem = NULL;
		}

		// �}�e���A���̔j��
		if (pItemType->pBuffMatItem != NULL)
		{			 
			pItemType->pBuffMatItem->Release();
			pItemType->pBuffMatItem = NULL;
		}
	}
}

//==============================================================================
// �A�C�e���̍X�V����
//==============================================================================
void UpdateItem(void)
{
	// ���[�J���ϐ��錾
	ItemInfo *pItemInfo = &g_Item.iteminfo[0];
	Select *pSelect = GetSelect();

	// �A�C�e���̉�]
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItemInfo++)
	{
		if (pItemInfo->bUse == true)
		{// �g�p��Ԃ�
			pItemInfo->rot.y += ITEM_TURN;	// �p�x�̉��Z

			if (pItemInfo->rot.y > D3DX_PI)
			{// �p�x�̐��l�P����
				pItemInfo->rot.y -= D3DX_PI * 2.0f;
			}
		}
	}
	
	g_Item.nSetCnt++;

	if (g_Item.nSetItem < ITEM_SET_MAX && g_Item.nSetCnt % 600 == 0)
	{
		RandItem((int)pSelect->stage);
		g_Item.nSetCnt = 0;
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
	ItemInfo *pItemInfo = &g_Item.iteminfo[0];

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItemInfo++)
	{
		if (pItemInfo->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pItemInfo->mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pItemInfo->rot.y, pItemInfo->rot.x, pItemInfo->rot.z);
			D3DXMatrixMultiply(&pItemInfo->mtxWorld, &pItemInfo->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pItemInfo->pos.x, pItemInfo->pos.y, pItemInfo->pos.z);
			D3DXMatrixMultiply(&pItemInfo->mtxWorld, &pItemInfo->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pItemInfo->mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_Item.typeinfo[(int)pItemInfo->type].pBuffMatItem->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_Item.typeinfo[(int)pItemInfo->type].nNumMatItem; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, NULL);

				// ���f��(�p�[�c)�̕`��
				g_Item.typeinfo[(int)pItemInfo->type].pMeshItem->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==============================================================================
// �A�C�e���̐ݒ�
//==============================================================================
void SetItem(D3DXVECTOR3 pos,int nType)
{
	// ���[�J���ϐ��錾
	ItemInfo *pItemInfo = &g_Item.iteminfo[0];
	ItemTypeInfo *pItemType;

	// �A�C�e���̐ݒ�
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItemInfo++)
	{
		if (pItemInfo->bUse == false)
		{// �A�C�e�������g�p��
			pItemInfo->pos = pos;	// �ʒu

			pItemInfo->type = (ItemType)nType; // �A�C�e���̎��

			pItemType = &g_Item.typeinfo[(int)pItemInfo->type];

			// �e���_�ʒu
			pItemInfo->posPoint[0] = D3DXVECTOR3(pItemInfo->pos.x + pItemType->vtxMinItem.x, 0.0f, pItemInfo->pos.z + pItemType->vtxMinItem.x);
			pItemInfo->posPoint[1] = D3DXVECTOR3(pItemInfo->pos.x + pItemType->vtxMinItem.x, 0.0f, pItemInfo->pos.z + pItemType->vtxMaxItem.x);
			pItemInfo->posPoint[2] = D3DXVECTOR3(pItemInfo->pos.x + pItemType->vtxMaxItem.x, 0.0f, pItemInfo->pos.z + pItemType->vtxMaxItem.x);
			pItemInfo->posPoint[3] = D3DXVECTOR3(pItemInfo->pos.x + pItemType->vtxMaxItem.x, 0.0f, pItemInfo->pos.z + pItemType->vtxMinItem.x);

			// �S�ӂ̃x�N�g��
			pItemInfo->vecPoint[0] = pItemInfo->posPoint[1] - pItemInfo->posPoint[0];
			pItemInfo->vecPoint[1] = pItemInfo->posPoint[2] - pItemInfo->posPoint[1];
			pItemInfo->vecPoint[2] = pItemInfo->posPoint[3] - pItemInfo->posPoint[2];
			pItemInfo->vecPoint[3] = pItemInfo->posPoint[0] - pItemInfo->posPoint[3];

			// �e�̐ݒ�
			pItemInfo->nIdx = SetShadow(D3DXVECTOR3(pItemInfo->pos.x, 0.0f, pItemInfo->pos.z), 10.0f, 10.0f);

			g_Item.nSetItem++;		// �z�u�A�C�e�����̉��Z

			pItemInfo->bUse = true;	// �g�p��Ԃֈڍs

			break;
		}
	}
}

//==============================================================================
// �G�̎擾
//==============================================================================
Item *GetItem(void)
{
	return &g_Item;
}

//==============================================================================
// �����_���Ńn�C�X�R�A�A�C�e���̑I��
//==============================================================================
void RandItem(int nStage)
{
	// ���[�J���ϐ��錾
	int nRand = rand() % 100;
	int nRandPos = 0;
	D3DXVECTOR3 pos;
	
	while (g_Item.iteminfo[nRandPos].bSet == true)
	{
		nRandPos = rand() % 8;
	}

	pos = g_RandPos[nRandPos];
	g_Item.iteminfo[nRandPos].bSet = true;

	switch (nStage)
	{
	case 0:
		if (nRand < 5)
		{
			SetItem(pos, ITEMTYPE_RANCHER);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else if (nRand >= 5 && nRand < 30)
		{
			SetItem(pos, ITEMTYPE_MACHINEGUN);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else if (nRand >= 30 && nRand < 55)
		{
			SetItem(pos, ITEMTYPE_HANDGUN);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else
		{
			SetItem(pos, ITEMTYPE_KNIFE);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		break;

	case 1:
		if (nRand < 5)
		{
			SetItem(pos, ITEMTYPE_RANCHER);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else if (nRand >= 5 && nRand < 30)
		{
			SetItem(pos, ITEMTYPE_MACHINEGUN);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else if (nRand >= 30 && nRand < 55)
		{
			SetItem(pos, ITEMTYPE_HANDGUN);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else
		{
			SetItem(pos, ITEMTYPE_KNIFE);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		break;

	case 2:
		if (nRand < 5)
		{
			SetItem(pos, ITEMTYPE_RANCHER);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else if (nRand >= 5 && nRand < 30)
		{
			SetItem(pos, ITEMTYPE_MACHINEGUN);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else if (nRand >= 30 && nRand < 55)
		{
			SetItem(pos, ITEMTYPE_HANDGUN);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		else
		{
			SetItem(pos, ITEMTYPE_KNIFE);
			PlaySound(SOUND_LABEL_SE_SETITEM);
		}
		break;

	default:
		break;
	}
}

//==============================================================================
// �A�C�e���̎擾
//==============================================================================
void TouchItem(D3DXVECTOR3 *pPos, float fInRadius, float fHeight,int nCntPlayer)
{
	// ���[�J���ϐ��錾
	ItemInfo *pItemInfo = &g_Item.iteminfo[0];
	Player *pPlayer = GetPlayer();	// �v���C���[�̎擾
	D3DXVECTOR3 aVec[FOUR_POINT];	// �e���_����v���C���[�ւ̃x�N�g��
	float fItemVec[FOUR_POINT];		// ����p�ϐ�
	D3DXVECTOR3 pos = *pPos;		// �v���C���[�̈ʒu

	pPlayer += nCntPlayer;

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItemInfo++)
	{
		if (pItemInfo->bUse == true)
		{// �A�C�e���̊O�ϓ����蔻��
			ItemTypeInfo *pItemType = &g_Item.typeinfo[(int)pItemInfo->type];

			for (int nCnt = 0; nCnt < FOUR_POINT; nCnt++)
			{
				switch (nCnt)
				{
				case 0:	// ����
					aVec[nCnt] = pos + D3DXVECTOR3(fInRadius, 0.0f, 0.0f) - pItemInfo->posPoint[nCnt];
					break;

				case 1:	// ����
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, -fInRadius) - pItemInfo->posPoint[nCnt];
					break;

				case 2:	// �E��
					aVec[nCnt] = pos + D3DXVECTOR3(-fInRadius, 0.0f, 0.0f) - pItemInfo->posPoint[nCnt];
					break;

				case 3:	// ��O��
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fInRadius) - pItemInfo->posPoint[nCnt];
					break;
				}

				// ����p���l�Z�o
				fItemVec[nCnt] = (pItemInfo->vecPoint[nCnt].z * aVec[nCnt].x) - (pItemInfo->vecPoint[nCnt].x * aVec[nCnt].z);
			}

			// �A�C�e���Ƃ̐ڐG
			if (fItemVec[0] > 0.0f && fItemVec[1] > 0.0f && fItemVec[2] > 0.0f && fItemVec[3] > 0.0f && 
				pPlayer->pos.y <= (pItemInfo->pos.y + pItemType->vtxMaxItem.y) && (pPlayer->pos.y + fHeight) >= pItemInfo->pos.y)
			{// �A�C�e���̎擾
				// �G�t�F�N�g�̔���
				SetEffect(D3DXVECTOR3(pItemInfo->pos.x, pItemInfo->pos.y + 5.0f, pItemInfo->pos.z), 0.01f, D3DXCOLOR(1.0f, 0.1f, 1.0f, 1.0f), 5.0f, 0.05f, 30);
				PlaySound(SOUND_LABEL_SE_ITEM);
				Shadow *pShadow = GetShadow();	// �e�̎擾
				pShadow += pItemInfo->nIdx;
				pShadow->bUse = false;			// �e�̏���
				pItemInfo->bUse = false;		// �A�C�e���̏���
				pItemInfo->bSet = false;
				g_Item.nSetItem--;
				pPlayer->weapon = (Weapon)(pItemInfo->type + 1);
				switch (pPlayer->weapon)
				{
				case WEAPON_HANDGUN:
					pPlayer->nBullet = 15;
					break;

				case WEAPON_MACHINEGUN:
					pPlayer->nBullet = 150;
					break;

				case WEAPON_RUNCHER:
					pPlayer->nBullet = 2;
					break;

				default:
					break;
				}
				if (pPlayer->weapon == WEAPON_KNIFE)
				{
					pPlayer->sr = SHORT_KNIFE;
				}
				else
				{
					pPlayer->sr = SHORT_NONE;
				}
				break;
			}
		}
	}
}

void LoadItem(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aEqual[2] = { NULL };				// �u=�v�ǂݎ��p�ϐ�
	int nCntFile = 0;						// X�t�@�C���̐�
	int nIdx = 0;							// �p�[�c��
	bool bComment = false;					// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = { NULL };		// �e�L�X�g�ǂݎ��p�ϐ�
	//char aItem[TEXT_LENGTH] = { NULL };	// �|���S�����ǂݍ��ݗp�ϐ�
	//char aState[TEXT_LENGTH] = { NULL };	// �ڍ׏��ǂݎ��p�ϐ�

	// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];
	//char *pItem = &aItem[0];
	//char *pState = &aState[0];

	// �f�[�^�̓ǂݍ���
	pFile = fopen("data/TEXT/item.txt", "r");
	if (pFile != NULL)
	{ //�t�@�C���W�J�\
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
					if (strcmp("NUM_ITEM", pText) == 0)
					{// ���f���̐�
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &g_Item.nNumType);
					}
					else if (strcmp("ITEM_FILENAME", pText) == 0)
					{// X�t�@�C�����̓ǂݍ���
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%s", &g_Item.typeinfo[nCntFile].aFileName[0]);
						nCntFile++;
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