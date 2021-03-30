//==============================================================================
//
// ���b�V���\���̋O�Ղ̕`��kmeshorbit.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "meshorbit.h"
#include "player.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshOrbit = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshOrbit = NULL;
MeshOrbit g_MeshOrbit;

//==============================================================================
// ���b�V���\���̋O�Ղ̏���������
//==============================================================================
HRESULT InitMeshOrbit(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;
	Player *pPlayer = GetPlayer();
	
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/gradation000.jpg",
		&g_pTextureMeshOrbit);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MESHPOINT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_MeshOrbit.pVtxBuff,
		NULL);

	g_MeshOrbit.aCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_MeshOrbit.aCol[1] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	g_MeshOrbit.pMtxParent = &pPlayer->mtxWorld;

	g_MeshOrbit.aOffset[0] = pPlayer->aModel[0].pos;
	g_MeshOrbit.aOffset[1] = pPlayer->aModel[1].pos;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_MeshOrbit.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < (MESHPOINT / 2); nCnt++)
	{
		//pVtx[0].pos = g_MeshOrbit.aPosPoint[nCnt * 2];
		//pVtx[1].pos = g_MeshOrbit.aPosPoint[nCnt * 2 + 1];

		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx[0].col = g_MeshOrbit.aCol[0];
		pVtx[1].col = g_MeshOrbit.aCol[1];

		pVtx[0].tex = D3DXVECTOR2(1.0f * nCnt, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f * nCnt, 1.0f);

		pVtx += 2;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_MeshOrbit.pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * MESHPOINT,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshOrbit,
		NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshOrbit->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0; nCnt < MESHPOINT; nCnt++)
	{
		pIdx[0] = (MESHPOINT / 2) + nCnt;
		pIdx[1] = pIdx[0] - (MESHPOINT / 2);
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshOrbit->Unlock();

	return S_OK;
}

//==============================================================================
// ���b�V���\���̋O�Ղ̏I������
//==============================================================================
void UninitMeshOrbit(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_MeshOrbit.pVtxBuff != NULL)
	{
		g_MeshOrbit.pVtxBuff->Release();
		g_MeshOrbit.pVtxBuff = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureMeshOrbit != NULL)
	{
		g_pTextureMeshOrbit->Release();
		g_pTextureMeshOrbit = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshOrbit != NULL)
	{
		g_pIdxBuffMeshOrbit->Release();
		g_pIdxBuffMeshOrbit = NULL;
	}
}

//==============================================================================
// ���b�V���\���̋O�Ղ̍X�V����
//==============================================================================
void UpdateMeshOrbit(void)
{

}

//==============================================================================
// ���b�V���\���̋O�Ղ̕`�揈��
//==============================================================================
void DrawMeshOrbit(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	Player *pPlayer = GetPlayer();
	VERTEX_3D *pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	for (int nCnt = 0; nCnt < MESH_MAIN; nCnt++)
	{
		// �}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_MeshOrbit.aMtxWorldPoint[nCnt]);

		// �I�t�Z�b�g�̃��[���h�}�g���b�N�X�Z�o
		D3DXMatrixTranslation(
			&mtxTrans,
			g_MeshOrbit.aOffset[nCnt].x,
			g_MeshOrbit.aOffset[nCnt].y,
			g_MeshOrbit.aOffset[nCnt].z);

		D3DXMatrixMultiply(
			&g_MeshOrbit.aMtxWorldPoint[nCnt],
			&g_MeshOrbit.aMtxWorldPoint[nCnt],
			&mtxTrans);

		// �e�̃}�g���b�N�X�Ɗ|�����킹��
		D3DXMatrixMultiply(
			&g_MeshOrbit.aMtxWorldPoint[nCnt],
			&g_MeshOrbit.aMtxWorldPoint[nCnt],
			g_MeshOrbit.pMtxParent);
	}

	// ���_���W�ƒ��_�J���[�����炷
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_MeshOrbit.pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntOrbit = (MESHPOINT / 2 - 1); nCntOrbit >= 0; nCntOrbit--, pVtx += 2)
	{
		if (nCntOrbit == (MESHPOINT / 2))
		{
			g_MeshOrbit.aPosPoint[nCntOrbit * 2] = g_MeshOrbit.aOffset[0];
			g_MeshOrbit.aPosPoint[nCntOrbit * 2 - 1] = g_MeshOrbit.aOffset[1];
		}
		else
		{
			g_MeshOrbit.aPosPoint[nCntOrbit * 2] = g_MeshOrbit.aPosPoint[nCntOrbit * 2 + 2];
			g_MeshOrbit.aPosPoint[nCntOrbit * 2 - 1] = g_MeshOrbit.aPosPoint[nCntOrbit * 2 + 1];
		}

		pVtx[0].pos = g_MeshOrbit.aPosPoint[nCntOrbit * 2];
		pVtx[1].pos = g_MeshOrbit.aPosPoint[nCntOrbit * 2 - 1];	
	}

	// ���_�o�b�t�@���A�����b�N����
	g_MeshOrbit.pVtxBuff->Unlock();

	//for (int nCnt = 2; nCnt < MESHPOINT; nCnt += 2)
	//{
	//	// ���l�����炷
	//	g_MeshOrbit.aPosPoint[nCnt] = pos[0];
	//	g_MeshOrbit.aPosPoint[nCnt + 1] = pos[1];
	//	g_MeshOrbit.aColPoint[nCnt] = col[0];
	//	g_MeshOrbit.aColPoint[nCnt + 1] = col[1];
	//	// �ϐ��̕ۑ�
	//	pos[0] = g_MeshOrbit.aPosPoint[nCnt];
	//	pos[1] = g_MeshOrbit.aPosPoint[nCnt + 1];
	//	col[0] = g_MeshOrbit.aColPoint[nCnt];
	//	col[1] = g_MeshOrbit.aColPoint[nCnt + 1];
	//}

	// �ŐV�̒��_���W�ƒ��_�J���[����
	g_MeshOrbit.aPosPoint[0].x = g_MeshOrbit.aMtxWorldPoint[0]._41;
	g_MeshOrbit.aPosPoint[0].y = g_MeshOrbit.aMtxWorldPoint[0]._42;
	g_MeshOrbit.aPosPoint[0].z = g_MeshOrbit.aMtxWorldPoint[0]._43;
			   	
	g_MeshOrbit.aPosPoint[1].x = g_MeshOrbit.aMtxWorldPoint[1]._41;
	g_MeshOrbit.aPosPoint[1].y = g_MeshOrbit.aMtxWorldPoint[1]._42;
	g_MeshOrbit.aPosPoint[1].z = g_MeshOrbit.aMtxWorldPoint[1]._43;

	g_MeshOrbit.aColPoint[0] = g_MeshOrbit.aCol[0];
	g_MeshOrbit.aColPoint[1] = g_MeshOrbit.aCol[1];

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(
	//	&mtxTrans, 
	//	g_MeshOrbit.pos.x, 
	//	g_MeshOrbit.pos.y,
	//	g_MeshOrbit.pos.z);

	//D3DXMatrixMultiply(
	//	g_MeshOrbit.pMtxParent,
	//	g_MeshOrbit.pMtxParent,
	//	&mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, g_MeshOrbit.pMtxParent);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_MeshOrbit.pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshOrbit);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshOrbit);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,
		0,
		MESHPOINT,				// ���_��
		0,
		MESHPOINT - 2);		// �v���~�e�B�u��

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//==============================================================================
// ���b�V���\���̋O�Ղ̐ݒ�
//==============================================================================
void SetMeshOrbit(D3DXVECTOR3 pos0, D3DXVECTOR3 pos1, D3DXCOLOR col0, D3DXCOLOR col1)
{
	g_MeshOrbit.aOffset[0] = pos0;
	g_MeshOrbit.aOffset[1] = pos1;
}

MeshOrbit GetOrbit(void)
{
	return g_MeshOrbit;
}