//==============================================================================
//
// 3D���f���̕`��kobject.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "object.h"
#include "input.h"
#include "camera.h"
#include "player.h"
//#include "shadow.h"
#include "math.h"

// �}�N����`
#define COLLISION_PARTS	(4)	// �����蔻��̖ʂ̐�

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPD3DXMESH g_pMeshObject = NULL;			// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatObject = NULL;		// �}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatObject = 0;					// �}�e���A���̐�
//D3DXVECTOR3 g_vtxMinObject, g_vtxMaxObject;	// ���f���̊e���W�̂̍ő�l�E�ŏ��l
Object object;
D3DXVECTOR3 g_aPos[4];					// �����蔻�蒸�_���
D3DXVECTOR3 vec;
D3DXVECTOR3 g_aVec[4];					// �����蔻��x�N�g��

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
		&g_pBuffMatObject,
		NULL,
		&g_nNumMatObject,
		&g_pMeshObject);

	// ���[�J���ϐ��錾
	int nNumVtx;	// ���_��
	DWORD sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = g_pMeshObject->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshObject->GetFVF());

	// �ϐ��̏�����
	object.pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	object.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	object.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	object.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̐ݒ�
	//model.nIdx = SetShadow(D3DXVECTOR3(model.pos.x,0.0f,model.pos.z), 10.0f, 10.0f);

	// ���_�o�b�t�@�����b�N
	g_pMeshObject->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���_���W�̔�r
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

		// �e���W�̍ő�l�̔�r
		if (object.vtxMaxObject.x < vtx.x)
		{	
			object.vtxMaxObject.x = vtx.x;
		}	
		if (object.vtxMaxObject.y < vtx.y)
		{	
			object.vtxMaxObject.y = vtx.y;
		}	
		if (object.vtxMaxObject.z < vtx.z)
		{	
			object.vtxMaxObject.z = vtx.z;
		}

		// �e���W�̍ŏ��l�̔�r
		if (object.vtxMinObject.x > vtx.x)
		{	
			object.vtxMinObject.x = vtx.x;
		}	
		if (object.vtxMinObject.y > vtx.y)
		{	
			object.vtxMinObject.y = vtx.y;
		}	
		if (object.vtxMinObject.z > vtx.z)
		{	
			object.vtxMinObject.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	g_pMeshObject->UnlockVertexBuffer();

	// �I�u�W�F�N�g��`�̊e���_
	g_aPos[0] = D3DXVECTOR3(object.pos.x + object.vtxMinObject.x, 0.0f, object.pos.z + object.vtxMinObject.z);	// ����O
	g_aPos[1] = D3DXVECTOR3(object.pos.x + object.vtxMinObject.x, 0.0f, object.pos.z + object.vtxMaxObject.z);	// ����
	g_aPos[2] = D3DXVECTOR3(object.pos.x + object.vtxMaxObject.x, 0.0f, object.pos.z + object.vtxMaxObject.z);	// �E��
	g_aPos[3] = D3DXVECTOR3(object.pos.x + object.vtxMaxObject.x, 0.0f, object.pos.z + object.vtxMinObject.z);	// �E��O

	// �I�u�W�F�N�g��`�̊e�ʂ̃x�N�g��
	g_aVec[0] = g_aPos[1] - g_aPos[0];
	g_aVec[1] = g_aPos[2] - g_aPos[1];
	g_aVec[2] = g_aPos[3] - g_aPos[2];
	g_aVec[3] = g_aPos[0] - g_aPos[3];

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitObject(void)
{
	// ���b�V���̔j��
	if (g_pMeshObject != NULL)
	{		   
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}

	// �}�e���A���̔j��
	if (g_pBuffMatObject != NULL)
	{			  
		g_pBuffMatObject->Release();
		g_pBuffMatObject = NULL;
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

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&object.mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, object.rot.y, object.rot.x, object.rot.z);
	D3DXMatrixMultiply(&object.mtxWorld, &object.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, object.pos.x, object.pos.y, object.pos.z);
	D3DXMatrixMultiply(&object.mtxWorld, &object.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &object.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		g_pMeshObject->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==============================================================================
// �I�u�W�F�N�g�̎擾
//==============================================================================
Object *GetObject(void)
{
	return &object;
}

//==============================================================================
// �����蔻��
//==============================================================================
bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin)
{
	bool bLand = false;

	if (pPos->x >= pPosOld->x && pPos->x < object.pos.x)
	{ // �����̔���
		if (pPos->z + fDepthMax >= object.pos.z + object.vtxMinObject.z &&
			pPos->z + fDepthMin <= object.pos.z + object.vtxMaxObject.z &&
			pPos->x + fWidthMax >= object.pos.x + object.vtxMinObject.x &&
			pPos->x + fWidthMin <= object.pos.x + object.vtxMaxObject.x)
		{ // �u���b�N�̓����蔻��
			pPos->x = object.pos.x + object.vtxMinObject.x - fWidthMax;	// ����̍X�V

			pMove->x = 0.0f;	// ����ւ̒蒅
		}
	}
	else if (pPos->x <= pPosOld->x && pPos->x > object.pos.x)
	{ // �E���̔���
		if (pPos->z + fDepthMax >= object.pos.z + object.vtxMinObject.z &&
			pPos->z + fDepthMin <= object.pos.z + object.vtxMaxObject.z &&
			pPos->x + fWidthMax >= object.pos.x + object.vtxMinObject.x &&
			pPos->x + fWidthMin <= object.pos.x + object.vtxMaxObject.x)
		{ // �u���b�N�̓����蔻��
			pPos->x = object.pos.x + object.vtxMaxObject.x - fWidthMin;
			pMove->x = 0.0f;
		}
	}
	else if (pPos->z >= pPosOld->z && pPos->z < object.pos.z)
	{ // ��O���̔���
		if (pPos->z + fDepthMax >= object.pos.z + object.vtxMinObject.z &&
			pPos->z + fDepthMin <= object.pos.z + object.vtxMaxObject.z &&
			pPos->x + fWidthMax >= object.pos.x + object.vtxMinObject.x &&
			pPos->x + fWidthMin <= object.pos.x + object.vtxMaxObject.x)
		{ // �u���b�N�̓����蔻��
			pPos->z = object.pos.z + object.vtxMinObject.z - fDepthMax;
			pMove->z = 0.0f;
		}
	}
	else if (pPos->z <= pPosOld->z && pPos->z > object.pos.z)
	{ // �����̔���
		if (pPos->z + fDepthMax >= object.pos.z + object.vtxMinObject.z &&
			pPos->z + fDepthMin <= object.pos.z + object.vtxMaxObject.z &&
			pPos->x + fWidthMax >= object.pos.x + object.vtxMinObject.x &&
			pPos->x + fWidthMin <= object.pos.x + object.vtxMaxObject.x)
		{ // �u���b�N�̓����蔻��
			pPos->z = object.pos.z + object.vtxMaxObject.z - fDepthMin;
			pMove->z = 0.0f;
		}
	}

	return bLand;
}

//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	// ���[�J���ϐ��錾
	bool bLand = false;
	D3DXVECTOR3 aVec[COLLISION_PARTS];	// ��`���_���画��Ώۂւ̃x�N�g��
	float fPlayerVec[COLLISION_PARTS];	// �e�ʂ̃x�N�g���Ƃ̔���i�{�|�j
	D3DXVECTOR3 pos = *pPos;			// ����Ώۂ̈ʒu

	// �I�u�W�F�N�g�Ƃ̓����蔻��
	for (int nCnt = 0; nCnt < COLLISION_PARTS; nCnt++)
	{
		if (nCnt == 0)
		{// ����
			aVec[nCnt] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_aPos[nCnt];
		}
		else if (nCnt == 1)
		{// ����
			aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_aPos[nCnt];
		}
		else if (nCnt == 2)
		{// �E��
			aVec[nCnt] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_aPos[nCnt];
		}
		else if (nCnt == 3)
		{// ��O
			aVec[nCnt] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_aPos[nCnt];
		}

		//aVec[nCnt] = pos - g_aPos[nCnt];	// �ʂ̎n�_�ƑΏۂ̃x�N�g��

		// ���l���u+�v�̎��A�����蔻�肪�L��
		fPlayerVec[nCnt] = (g_aVec[nCnt].z * aVec[nCnt].x) - (g_aVec[nCnt].x * aVec[nCnt].z);	

		if (pPos->y <= object.pos.y + object.vtxMaxObject.y - fHeightMin && pPos->y > object.pos.y + object.vtxMinObject.y - fHeightMax)
		{
			if (fPlayerVec[0] > 0.0f && fPlayerVec[1] > 0.0f && fPlayerVec[2] > 0.0f && fPlayerVec[3] > 0.0f)
			{
				if (pPos->x > pPosOld->x && pPosOld->x < object.pos.x + object.vtxMinObject.x)
				{// ����	
					pPos->x = object.pos.x + object.vtxMinObject.x - fWidthMax;
					//pMove->x = 0.0f;
				}
				else if (pPos->x < pPosOld->x && pPosOld->x > object.pos.x + object.vtxMaxObject.x)
				{// �E��	
					pPos->x = object.pos.x + object.vtxMaxObject.x - fWidthMin;
					//pMove->x = 0.0f;
				}
				else if (pPos->z <= pPosOld->z && pPos->z > object.pos.z)
				{// ����
					pPos->z = object.pos.z + object.vtxMaxObject.z - fDepthMin;
					//pMove->z = 0.0f;
				}
				else if (pPos->z >= pPosOld->z && pPos->z < object.pos.z)
				{// ��O
					pPos->z = object.pos.z + object.vtxMinObject.z - fDepthMax;
					//pMove->z = 0.0f;
				}
			}
		}
	}

	return bLand;
}