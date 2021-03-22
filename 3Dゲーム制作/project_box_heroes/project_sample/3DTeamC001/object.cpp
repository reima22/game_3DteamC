//==============================================================================
//
// 3D���f���̕`��kobject.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "object.h"
#include "input.h"
#include "gamepad.h"
#include "camera.h"
#include "player.h"
#include "shadow.h"
#include "item.h"
#include "math.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_apTextureObject[MAX_TEX_OBJECT] = {};	// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshObject[OBJECTTYPE_MAX] = {};				// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject[OBJECTTYPE_MAX] = {};			// �}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatObject[OBJECTTYPE_MAX] = {};					// �}�e���A���̐�
Object object[MAX_OBJECT];
Type type[OBJECTTYPE_MAX];

//D3DXVECTOR3 g_aPos[4];					// �����蔻�蒸�_���
//D3DXVECTOR3 vec;
//D3DXVECTOR3 g_aVec[4];					// �����蔻��x�N�g
//D3DXVECTOR3 g_posModel;				// �ʒu
//D3DXVECTOR3 g_rotModel;				// ����
//D3DXMATRIX g_mtxWorldModel;			// ���[���h�}�g���b�N�X
//D3DXVECTOR3 g_moveModelX;				// X���̈ړ���
//D3DXVECTOR3 g_moveModelZ;				// Z���̈ړ���
//int g_nIdx;

//==============================================================================
// ����������
//==============================================================================
HRESULT InitObject(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data/MODEL/baloon01.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject[OBJECTTYPE_BALOON],
		NULL,
		&g_nNumMatObject[OBJECTTYPE_BALOON],
		&g_pMeshObject[OBJECTTYPE_BALOON]);

	D3DXLoadMeshFromX(
		"data/MODEL/block.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject[OBJECTTYPE_BLOCK],
		NULL,
		&g_nNumMatObject[OBJECTTYPE_BLOCK],
		&g_pMeshObject[OBJECTTYPE_BLOCK]);

	// ���[�J���ϐ��錾
	int nNumVtx[OBJECTTYPE_MAX];	// ���_��
	DWORD sizeFVF[OBJECTTYPE_MAX];	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATERIAL *pMat;		// �}�e���A���ւ̃|�C���^

	// �}�e���A�����ɑ΂���|�C���^���擾
	for (int nCnt = 0; nCnt < OBJECTTYPE_MAX; nCnt++,pMat++)
	{
		pMat = (D3DXMATERIAL*)g_pBuffMatObject[nCnt]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject[nCnt]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(
					pDevice,
					pMat[nCntMat].pTextureFilename,
					&g_apTextureObject[nCntMat]);
			}
		}
	}

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		object[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		object[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		object[nCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		object[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		object[nCnt].bUse = false;
		object[nCnt].nType = 0;
	}

	for (int nCnt = 0; nCnt < OBJECTTYPE_MAX; nCnt++)
	{
		// ���_�����擾
		nNumVtx[nCnt] = g_pMeshObject[nCnt]->GetNumVertices();

		// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
		sizeFVF[nCnt] = D3DXGetFVFVertexSize(g_pMeshObject[nCnt]->GetFVF());

		// ���_�o�b�t�@�����b�N
		g_pMeshObject[nCnt]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		// ���_���W�̔�r
		for (int nCntVtx = 0; nCntVtx < (int)nNumVtx[nCnt]; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

														// �e���W�̍ő�l�̔�r
			if (type[nCnt].vtxMaxObject.x < vtx.x)
			{
				type[nCnt].vtxMaxObject.x = vtx.x;
			}
			if (type[nCnt].vtxMaxObject.y < vtx.y)
			{
				type[nCnt].vtxMaxObject.y = vtx.y;
			}
			if (type[nCnt].vtxMaxObject.z < vtx.z)
			{
				type[nCnt].vtxMaxObject.z = vtx.z;
			}

			// �e���W�̍ŏ��l�̔�r
			if (type[nCnt].vtxMinObject.x > vtx.x)
			{
				type[nCnt].vtxMinObject.x = vtx.x;
			}
			if (type[nCnt].vtxMinObject.y > vtx.y)
			{
				type[nCnt].vtxMinObject.y = vtx.y;
			}
			if (type[nCnt].vtxMinObject.z > vtx.z)
			{
				type[nCnt].vtxMinObject.z = vtx.z;
			}

			pVtxBuff += sizeFVF[nCnt];	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		// ���_�o�b�t�@���A�����b�N
		g_pMeshObject[nCnt]->UnlockVertexBuffer();
	}

	// ���D
	SetObject(D3DXVECTOR3(300.0f, 0.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-300.0f, 0.0f, 0.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(0.0f, 0.0f, 300.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(0.0f, 0.0f, -300.0f), 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �u���b�N
	SetObject(D3DXVECTOR3(200.0f, 0.0f, 200.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-200.0f, 0.0f, 200.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(200.0f, 0.0f, -200.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetObject(D3DXVECTOR3(-200.0f, 0.0f, -200.0f), 1, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitObject(void)
{
	for (int nCnt = 0; nCnt < OBJECTTYPE_MAX; nCnt++)
	{
		// ���b�V���̔j��
		if (g_pMeshObject[nCnt] != NULL)
		{				
			g_pMeshObject[nCnt]->Release();
			g_pMeshObject[nCnt] = NULL;
		}

		// �}�e���A���̔j��
		if (g_pBuffMatObject[nCnt] != NULL)
		{
			g_pBuffMatObject[nCnt]->Release();
			g_pBuffMatObject[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateObject(void)
{
	// ���[�J���ϐ��錾
	//Player *player = GetPlayer();
	D3DXVECTOR3 pos[2];
	D3DXVECTOR3 vecA;
	D3DXVECTOR3 vecB;
	float a;
	//aVec[];
	pos[0] = D3DXVECTOR3(-100.0f,0.0f,-50.0f);
	pos[1] = D3DXVECTOR3(100.0f,0.0f,-50.0f);
	vecA = pos[1] - pos[0];
	vecB = D3DXVECTOR3(0.0f,0.0f,50.0f) - pos[0];
	a = (vecA.z * vecB.x) - (vecA.x * vecB.z);

	/* �x�N�g��vecA�ɑ΂��ē_�����ɂ���Ƃ��ua�v�̓}�C�i�X������*/
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawObject(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^
	Object *pObject = &object[0];


	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++,pObject++)
	{
		if (pObject->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pObject->mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pObject->rot.y, pObject->rot.x, pObject->rot.z);
			D3DXMatrixMultiply(&pObject->mtxWorld, &pObject->mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pObject->pos.x, pObject->pos.y, pObject->pos.z);
			D3DXMatrixMultiply(&pObject->mtxWorld, &pObject->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pObject->mtxWorld);

			// ���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatObject[pObject->nType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject[pObject->nType]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				if (pObject->nType == 0)
				{
					pDevice->SetTexture(0, NULL);
				}
				else
				{
					pDevice->SetTexture(0, g_apTextureObject[nCntMat]);
				}

				// ���f��(�p�[�c)�̕`��
				g_pMeshObject[pObject->nType]->DrawSubset(nCntMat);
			}

			// �ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//==============================================================================
// �I�u�W�F�N�g�̎擾
//==============================================================================
Object *GetObject(void)
{
	return &object[0];
}

//==============================================================================
// �I�u�W�F�N�g�ݒ�
//==============================================================================
void SetObject(D3DXVECTOR3 pos, int nType,D3DXVECTOR3 rot)
{
	// ���[�J���ϐ��錾
	Object *pObject = &object[0];

	// �I�u�W�F�N�g���̐ݒ�
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++, pObject++)
	{
		if (pObject->bUse == false)
		{
			pObject->pos = pos;		// �ʒu
			pObject->rot = rot;

			SetItem(D3DXVECTOR3(pos.x, 100.0f, pos.z));

			pObject->nType = nType;	// ���

			pObject->vtxMinObject = type[nType].vtxMinObject;
			pObject->vtxMaxObject = type[nType].vtxMaxObject;

			// ���_�ʒu
			pObject->aPos[0] = D3DXVECTOR3(pObject->pos.x + type[nType].vtxMinObject.x ,pObject->pos.y ,pObject->pos.z + type[nType].vtxMinObject.z);
			pObject->aPos[1] = D3DXVECTOR3(pObject->pos.x + type[nType].vtxMinObject.x ,pObject->pos.y ,pObject->pos.z + type[nType].vtxMaxObject.z);
			pObject->aPos[2] = D3DXVECTOR3(pObject->pos.x + type[nType].vtxMaxObject.x ,pObject->pos.y ,pObject->pos.z + type[nType].vtxMaxObject.z);
			pObject->aPos[3] = D3DXVECTOR3(pObject->pos.x + type[nType].vtxMaxObject.x ,pObject->pos.y ,pObject->pos.z + type[nType].vtxMinObject.z);

			// �l�Ӄx�N�g��
			pObject->aVec[0] = pObject->aPos[1] - pObject->aPos[0];
			pObject->aVec[1] = pObject->aPos[2] - pObject->aPos[1];
			pObject->aVec[2] = pObject->aPos[3] - pObject->aPos[2];
			pObject->aVec[3] = pObject->aPos[0] - pObject->aPos[3];

			// �e�̐ݒ�
			switch (nType)
			{
			case 0:
				pObject->nIdx = SetShadow(D3DXVECTOR3(pObject->pos.x, 0.0f, pObject->pos.z), 10.0f, 10.0f);	// �e�̐ݒ�
				break;

			case 1:
				pObject->nIdx = SetShadow(D3DXVECTOR3(pObject->pos.x, 0.0f, pObject->pos.z), 80.0f, 80.0f);	// �e�̐ݒ�
				break;
			
			default:
				break;
			}

			pObject->bUse = true;

			break;
		}
	}
}

//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fInRadius ,float fHeight,int nCntPlayer)
{
	// ���[�J���ϐ��錾
	bool bLand;
	D3DXVECTOR3 aVec[COLLISION_PARTS];	// ��`���_���画��Ώۂւ̃x�N�g��
	D3DXVECTOR3 pos = *pPos;			// ����Ώۂ̈ʒu
	Player *pPlayer = GetPlayer();
	Object *pObject = &object[0];
	
	pPlayer += nCntPlayer;

	if (pPlayer->bOnBlock == false)
	{
		bLand = false;
	}
	else
	{
		bLand = true;
	}

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++, pObject++)
	{
		if (pObject->bUse == true)
		{
			// �I�u�W�F�N�g�Ƃ̓����蔻��
			for (int nCnt = 0; nCnt < COLLISION_PARTS; nCnt++)
			{
				if (nCnt == 0)
				{// ����
					aVec[nCnt] = pos + D3DXVECTOR3(fInRadius, 0.0f, 0.0f) - pObject->aPos[nCnt];
				}
				else if (nCnt == 1)
				{// ����
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, -fInRadius) - pObject->aPos[nCnt];
				}
				else if (nCnt == 2)
				{// �E��
					aVec[nCnt] = pos + D3DXVECTOR3(-fInRadius, 0.0f, 0.0f) - pObject->aPos[nCnt];
				}
				else if (nCnt == 3)
				{// ��O
					aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fInRadius) - pObject->aPos[nCnt];
				}

				// ���l���u+�v�̎��A�����蔻�肪�L��
				pObject->fPlayerVec[nCnt] = (pObject->aVec[nCnt].z * aVec[nCnt].x) - (pObject->aVec[nCnt].x * aVec[nCnt].z);
			}

			// �����蔻��
			if (pObject->fPlayerVec[0] > 0.0f && pObject->fPlayerVec[1] > 0.0f && pObject->fPlayerVec[2] > 0.0f && pObject->fPlayerVec[3] > 0.0f)
			{
				SetPositionShadow(pPlayer->nIdx, D3DXVECTOR3(pPlayer->pos.x, pObject->pos.y + pObject->vtxMaxObject.y, pPlayer->pos.z));
				if (pPos->y <= (pObject->pos.y + pObject->vtxMaxObject.y) && pPos->y > pObject->pos.y + pObject->vtxMinObject.y - fHeight)
				{
					if (pPos->y <= (pObject->pos.y + pObject->vtxMaxObject.y) &&
						pPosOld->y >= pObject->pos.y + pObject->vtxMaxObject.y)
					{// �㑤
						if (pPos->y < pObject->pos.y + pObject->vtxMaxObject.y)
						{
							pPlayer->nKey = 0;
							pPlayer->nCounterMotion = 0;
							pPlayer->motionType = MOTIONTYPE_LANDING;
						}
						pPos->y = pObject->pos.y + pObject->vtxMaxObject.y;
						bLand = true;
						if (GetKeyboardTrigger(KEYINFO_JUMP) == true || BuDo(KEYINFO::KEYINFO_OK,nCntPlayer) == true)
						{
							bLand = false;
						}
					}
					else if (pPos->x > pPosOld->x && pPosOld->x < pObject->pos.x + pObject->vtxMinObject.x)
					{// ����	
						pPos->x = pObject->pos.x + pObject->vtxMinObject.x - fInRadius;
						SetPositionShadow(pPlayer->nIdx, D3DXVECTOR3(pPlayer->pos.x, 0.0f, pPlayer->pos.z));
					}
					else if (pPos->x < pPosOld->x && pPosOld->x > pObject->pos.x + pObject->vtxMaxObject.x)
					{// �E��	
						pPos->x = pObject->pos.x + pObject->vtxMaxObject.x + fInRadius;
						SetPositionShadow(pPlayer->nIdx, D3DXVECTOR3(pPlayer->pos.x, 0.0f, pPlayer->pos.z));
					}
					else if (pPos->z <= pPosOld->z && pPos->z > pObject->pos.z)
					{// ����
						pPos->z = pObject->pos.z + pObject->vtxMaxObject.z + fInRadius;
						SetPositionShadow(pPlayer->nIdx, D3DXVECTOR3(pPlayer->pos.x, 0.0f, pPlayer->pos.z));
					}
					else if (pPos->z >= pPosOld->z && pPos->z < pObject->pos.z)
					{// ��O
						pPos->z = pObject->pos.z + pObject->vtxMinObject.z - fInRadius;
						SetPositionShadow(pPlayer->nIdx, D3DXVECTOR3(pPlayer->pos.x, 0.0f, pPlayer->pos.z));
					}

					break;
				}
			}
			else if (pObject->fPlayerVec[0] < 0.0f || pObject->fPlayerVec[1] < 0.0f || pObject->fPlayerVec[2] < 0.0f || pObject->fPlayerVec[3] < 0.0f)
			{
				if (pPlayer->bOnBlock == true && pos.y > 0.0f)
				{
					bLand = false;
				}
			}
			
		}
	}
	return bLand;
}