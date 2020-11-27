//==============================================================================
//
// ���b�V���ǂ̕`��kmeshwall.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "meshwall.h"
#include "input.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_MWALL	(4)
#define WIDTH_WALL	(2)		// ��(��)
#define HEIGHT_WALL	(2)		// �s��(����)
//#define POINT	(14)	// ���_��
//#define POLY	(12)	// �|���S����

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshwall = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshwall = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshwall = NULL;		// �e�N�X�`���ւ̃|�C���^
Meshwall g_aMeshwall[MAX_MWALL];
//D3DXVECTOR3 g_posMeshwall;							// �ʒu
//D3DXVECTOR3 g_rotMeshwall;							// ����
//D3DXMATRIX g_mtxWorldMeshwall;						// ���[���h�}�g���b�N�X
int g_nAllPointWall;								// �����_��
int g_nPolygonWall;									// �|���S����
int g_nIdxPointWall;								// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
//float g_fWidthWall;		// �����̒[
//float g_fDepthWall;		// ���̒[

//==============================================================================
// ����������
//==============================================================================
HRESULT InitMeshwall(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	WORD *pIdx;
	int nCount = 0;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/block000.jpg",
		&g_pTextureMeshwall);

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++)
	{
		//g_aMeshwall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshwall[nCnt].posMove = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
		//g_aMeshwall[nCnt].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_aMeshwall[nCnt].fWidth = 0.0f;
		g_aMeshwall[nCnt].fHeight = 0.0f;
	}
	g_aMeshwall[0].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	g_aMeshwall[1].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	g_aMeshwall[2].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	g_aMeshwall[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	g_aMeshwall[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_aMeshwall[1].rot = D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f);
	g_aMeshwall[2].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_aMeshwall[3].rot = D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f);


	//g_posMeshwall = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	//g_rotMeshwall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nAllPointWall = HEIGHT_WALL * 2 * (WIDTH_WALL + 2) - 2;					// �����_��
	g_nPolygonWall = WIDTH_WALL * HEIGHT_WALL * 2 + (4 * (HEIGHT_WALL - 1));	// ���|���S����
	g_nIdxPointWall = (WIDTH_WALL + 1) * (HEIGHT_WALL + 1);						// �C���f�b�N�X�o�b�t�@�ł̒��_��
	//g_fWidthWall = 100.0f;
	//g_fDepthWall = 100.0f;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_nIdxPointWall * MAX_MWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshwall,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̊e���_���W
	//for (int nCnt = 0; nCnt < HEIGHT_WALL + 1; nCnt++)
	//{// ���s��
	//	for (int nCntA = 0; nCntA < WIDTH_WALL + 1; nCntA++, nCount++)
	//	{// ����
	//		pVtx[nCount].pos = D3DXVECTOR3(-g_fWidthWall + ((float)nCntA * g_fWidthWall), 0.0f, g_fDepthWall - ((float)nCnt * g_fDepthWall));
	//	}
	//}

	for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++, pVtx += 9)
	{
		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x - 100.0f, g_aMeshwall[nCnt].pos.z + 200.0f, g_aMeshwall[nCnt].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x, g_aMeshwall[nCnt].pos.z + 200.0f, g_aMeshwall[nCnt].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x + 100.0f, g_aMeshwall[nCnt].pos.z + 200.0f, g_aMeshwall[nCnt].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x -100.0f, g_aMeshwall[nCnt].pos.z + 100.0f, g_aMeshwall[nCnt].pos.z);
		pVtx[4].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x, g_aMeshwall[nCnt].pos.z + 100.0f, g_aMeshwall[nCnt].pos.z);
		pVtx[5].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x + 100.0f, g_aMeshwall[nCnt].pos.z + 100.0f, g_aMeshwall[nCnt].pos.z);
		pVtx[6].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x - 100.0f, g_aMeshwall[nCnt].pos.z + 0.0f,	g_aMeshwall[nCnt].pos.z);
		pVtx[7].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x, g_aMeshwall[nCnt].pos.z + 0.0f,	g_aMeshwall[nCnt].pos.z);
		pVtx[8].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x + 100.0f, g_aMeshwall[nCnt].pos.z + 0.0f,	g_aMeshwall[nCnt].pos.z);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
		pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshwall->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * g_nAllPointWall * MAX_MWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshwall,
		NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshwall->Lock(0, 0, (void**)&pIdx, 0);

	//for (int nCntA = 0; nCntA < DEPTH + 1; nCntA++)
	//{
	//	for (int nCnt = 0; nCnt < (WIDTH + 1) * 2; nCnt++, pIdx += 2)
	//	{
	//		pIdx[0] = (WIDTH + 1);
	//		pIdx[1] = pIdx[0] - (WIDTH + 1);
	//	}
	//}

	for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++, pIdx += 14)
	{
		pIdx[0] = 3;
		pIdx[1] = 0;
		pIdx[2] = 4;
		pIdx[3] = 1;
		pIdx[4] = 5;
		pIdx[5] = 2;
		pIdx[6] = 2;
		pIdx[7] = 6;
		pIdx[8] = 6;
		pIdx[9] = 3;
		pIdx[10] = 7;
		pIdx[11] = 4;
		pIdx[12] = 8;
		pIdx[13] = 5;
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshwall->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitMeshwall(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshwall != NULL)
	{
		g_pVtxBuffMeshwall->Release();
		g_pVtxBuffMeshwall = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureMeshwall != NULL)
	{
		g_pTextureMeshwall->Release();
		g_pTextureMeshwall = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshwall != NULL)
	{
		g_pIdxBuffMeshwall->Release();
		g_pIdxBuffMeshwall = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateMeshwall(void)
{

}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawMeshwall(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	Meshwall *pMeshwall;
	pMeshwall = &g_aMeshwall[0];

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++, pMeshwall++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&pMeshwall->mtxWorld);

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pMeshwall->rot.y, pMeshwall->rot.x, pMeshwall->rot.z);
		D3DXMatrixMultiply(&pMeshwall->mtxWorld, &pMeshwall->mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pMeshwall->pos.x, pMeshwall->pos.y, pMeshwall->pos.z);
		D3DXMatrixMultiply(&pMeshwall->mtxWorld, &pMeshwall->mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &pMeshwall->mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshwall);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//// ���[���h�}�g���b�N�X�̏�����
		//D3DXMatrixIdentity(&g_aMeshwall[nCnt].mtxWorld);

		//// �����̔��f
		//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aMeshwall[nCnt].rot.y, g_aMeshwall[nCnt].rot.x, g_aMeshwall[nCnt].rot.z);
		//D3DXMatrixMultiply(&g_aMeshwall[nCnt].mtxWorld, &g_aMeshwall[nCnt].mtxWorld, &mtxRot);

		//// �ʒu�𔽉f
		//D3DXMatrixTranslation(&mtxTrans, g_aMeshwall[nCnt].pos.x, g_aMeshwall[nCnt].pos.y, g_aMeshwall[nCnt].pos.z);
		//D3DXMatrixMultiply(&g_aMeshwall[nCnt].mtxWorld, &g_aMeshwall[nCnt].mtxWorld, &mtxTrans);

		//// ���[���h�}�g���b�N�X�̐ݒ�
		//pDevice->SetTransform(D3DTS_WORLD, &g_aMeshwall[nCnt].mtxWorld);

		//// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		//pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));

		//// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		//pDevice->SetIndices(g_pIdxBuffMeshwall);

		//// ���_�t�H�[�}�b�g�̐ݒ�
		//pDevice->SetFVF(FVF_VERTEX_3D);

	}

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_mtxWorldMeshwall);

	//// �����̔��f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshwall.y, g_rotMeshwall.x, g_rotMeshwall.z);
	//D3DXMatrixMultiply(&g_mtxWorldMeshwall, &g_mtxWorldMeshwall, &mtxRot);

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, g_posMeshwall.x, g_posMeshwall.y, g_posMeshwall.z);
	//D3DXMatrixMultiply(&g_mtxWorldMeshwall, &g_mtxWorldMeshwall, &mtxTrans);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshwall);

	//// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));

	//// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetIndices(g_pIdxBuffMeshwall);

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshwall);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
			0,
			0,
			nCnt * 9,					// ���_��
			0,
			nCnt * 14);					// �v���~�e�B�u��
	}
	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureMeshwall);

	//// �|���S���̕`��
	//pDevice->DrawIndexedPrimitive(
	//	D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
	//	0,
	//	0,
	//	9,						// ���_��
	//	0,
	//	14);					// �v���~�e�B�u��
}