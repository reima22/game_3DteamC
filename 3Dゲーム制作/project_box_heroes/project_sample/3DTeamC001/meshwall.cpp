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
#define WALL_POINT_MAX	(65535)		// ���_���̍ő�
#define WALL_IDX_MAX	(65535)		// �C���f�b�N�X�o�b�t�@�̍ő�m�ې�
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
int g_nAllPointWall;								// �����_��
int g_nPolygonWall;									// �|���S����
int g_nIdxPointWall;								// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�

//int g_nWidthWall = WIDTH_WALL + 1;			// �����̒��_��
//int g_nHeightWall = HEIGHT_WALL + 1;		// �����̒��_��

//==============================================================================
// ����������
//==============================================================================
HRESULT InitMeshwall(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	//WORD *pIdx;
	int nCount = 0;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/block001.jpg",
		&g_pTextureMeshwall);

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++)
	{
		g_aMeshwall[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshwall[nCnt].posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshwall[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aMeshwall[nCnt].fWidth = 0.0f;
		g_aMeshwall[nCnt].fHeight = 0.0f;
		g_aMeshwall[nCnt].fWidthMax = 0.0f;
		g_aMeshwall[nCnt].fHeightMax = 0.0f;
		g_aMeshwall[nCnt].nAllPoint = 0;
		g_aMeshwall[nCnt].nPolygon = 0;
		g_aMeshwall[nCnt].nIdxPoint = 0;
		g_aMeshwall[nCnt].nWidth = 0;
		g_aMeshwall[nCnt].nHeight = 0;
		g_aMeshwall[nCnt].bUse = false;
	}

	//g_nAllPointWall = HEIGHT_WALL * 2 * (WIDTH_WALL + 2) - 2;					// �H�鑍���_��
	//g_nPolygonWall = WIDTH_WALL * HEIGHT_WALL * 2 + (4 * (HEIGHT_WALL - 1));	// �`�悷��|���S����
	//g_nIdxPointWall = (WIDTH_WALL + 1) * (HEIGHT_WALL + 1);						// �C���f�b�N�X�o�b�t�@�ł̑����_��

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * WALL_IDX_MAX * MAX_MWALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshwall,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	// ����������
	for (int nCntWall = 0; nCntWall < MAX_MWALL; nCntWall++)
	{
		for (int nCnt = 0; nCnt < g_aMeshwall[nCntWall].nHeight - 1; nCnt++)
		{
			for (int nCntA = 0; nCntA < g_aMeshwall[nCntWall].nWidth - 1; nCntA++,pVtx++)
			{
				// �|���S���̊e���_���W
				pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				// �@���x�N�g���̐ݒ�
				pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// �e���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����_���̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			}
		}
	}



	//for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++, pVtx += 9)
	//{
	//	// �|���S���̊e���_���W
	//	pVtx[0].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x - 100.0f, g_aMeshwall[nCnt].pos.y + 200.0f, g_aMeshwall[nCnt].pos.z);
	//	pVtx[1].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x, g_aMeshwall[nCnt].pos.y + 200.0f, g_aMeshwall[nCnt].pos.z);
	//	pVtx[2].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x + 100.0f, g_aMeshwall[nCnt].pos.y + 200.0f, g_aMeshwall[nCnt].pos.z);
	//	pVtx[3].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x -100.0f, g_aMeshwall[nCnt].pos.y + 100.0f, g_aMeshwall[nCnt].pos.z);
	//	pVtx[4].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x, g_aMeshwall[nCnt].pos.y + 100.0f, g_aMeshwall[nCnt].pos.z);
	//	pVtx[5].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x + 100.0f, g_aMeshwall[nCnt].pos.y + 100.0f, g_aMeshwall[nCnt].pos.z);
	//	pVtx[6].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x - 100.0f, g_aMeshwall[nCnt].pos.y, g_aMeshwall[nCnt].pos.z);
	//	pVtx[7].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x, g_aMeshwall[nCnt].pos.y,	g_aMeshwall[nCnt].pos.z);
	//	pVtx[8].pos = D3DXVECTOR3(g_aMeshwall[nCnt].pos.x + 100.0f, g_aMeshwall[nCnt].pos.y, g_aMeshwall[nCnt].pos.z);

	//	// �@���x�N�g���̐ݒ�
	//	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//	pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//	// �e���_�J���[�̐ݒ�
	//	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	// �e�N�X�`�����_���̐ݒ�
	//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//	pVtx[2].tex = D3DXVECTOR2(2.0f, 0.0f);
	//	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//	pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//	pVtx[5].tex = D3DXVECTOR2(2.0f, 1.0f);
	//	pVtx[6].tex = D3DXVECTOR2(0.0f, 2.0f);
	//	pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f);
	//	pVtx[8].tex = D3DXVECTOR2(2.0f, 2.0f);
	//}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshwall->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * WALL_POINT_MAX * MAX_MWALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshwall,
		NULL);

	// �ǂ̐ݒ�
	SetMeshwall(D3DXVECTOR3(0.0f, 100.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 20, 4);
	//SetMeshwall(D3DXVECTOR3(0.0f, 50.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 50.0f, 50.0f, 8, 2);
	SetMeshwall(D3DXVECTOR3(500.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2.0f, 0.0f), 50.0f, 50.0f, 20, 4);
	SetMeshwall(D3DXVECTOR3(0.0f, 100.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 50.0f, 50.0f, 20, 4);
	SetMeshwall(D3DXVECTOR3(-500.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2.0f, 0.0f), 50.0f, 50.0f, 20, 4);

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
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	WORD *pIdx;
	D3DXVECTOR3 p[100];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshwall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntMax = 0; nCntMax < MAX_MWALL; nCntMax++)
	{
		if (g_aMeshwall[nCntMax].bUse == true)
		{
			for (int nCntWall = 0; nCntWall < g_aMeshwall[nCntMax].nHeightPoint; nCntWall++)
			{
				for (int nCnt = 0; nCnt < g_aMeshwall[nCntMax].nWidthPoint; nCnt++, pVtx++)
				{
					// �|���S���̊e���_���W
					//pVtx[0].pos = D3DXVECTOR3(
					//	g_aMeshwall[nCntMax].pos.x - g_aMeshwall[nCntMax].fWidth + g_aMeshwall[nCntMax].fWidth * nCnt * 2 / WIDTH_WALL,
					//	g_aMeshwall[nCntMax].pos.y + g_aMeshwall[nCntMax].fHeight * 2 - g_aMeshwall[nCntMax].fHeight * nCntWall * 2 / HEIGHT_WALL,
					//	g_aMeshwall[nCntMax].pos.z);
					pVtx[0].pos = D3DXVECTOR3(
						-g_aMeshwall[nCntMax].fWidthMax / 2.0f + (float)nCnt * g_aMeshwall[nCntMax].fWidth,
						g_aMeshwall[nCntMax].fHeightMax / 2.0f - (float)nCntWall * g_aMeshwall[nCntMax].fHeight,
						0.0f);

					// �@���x�N�g���̐ݒ�
					pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

					// �e���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					// �e�N�X�`�����_���̐ݒ�
					pVtx[0].tex = D3DXVECTOR2(1.0f * nCnt, 1.0f * nCntWall);
				}
			}
		}

		for (int nCntA = 0; nCntA < g_aMeshwall[nCntMax].nHeight; nCntA++)
		{
			for (int nCnt = 0; nCnt < (g_aMeshwall[nCntMax].nWidthPoint + 1); nCnt++)
			{
				if (nCnt != 0 && nCnt == g_aMeshwall[nCntMax].nWidthPoint && nCntA != g_aMeshwall[nCntMax].nHeight - 1)
				{// �E�[����܂�Ԃ���
					pIdx[0] = pIdx[-1];
					pIdx[1] = pIdx[-2] + 1;
				}
				else if (nCntA == g_aMeshwall[nCntMax].nHeight - 1 && nCnt == g_aMeshwall[nCntMax].nWidthPoint)
				{// �I�����ɖ�������
					break;
				}
				else
				{// �ʏ�z�u
					pIdx[0] = g_aMeshwall[nCntMax].nWidthPoint + (g_aMeshwall[nCntMax].nWidthPoint * nCntA) + nCnt;
					pIdx[1] = pIdx[0] - (g_aMeshwall[nCntMax].nWidthPoint);
				}
				pIdx += 2;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshwall->Unlock();

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshwall->Unlock();


	//// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);
	//// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	//g_pIdxBuffMeshwall->Lock(0, 0, (void**)&pIdx, 0);
	////int a[120];
	//D3DXVECTOR3 b[1000];
	//int nMax = 0;
	//for (int nCnt = 0; nCnt < 4; nCnt++)
	//{
	//	nMax += g_aMeshwall[nCnt].nAllPoint;
	//}
	//for (int nCnt = 0; nCnt < nMax; nCnt++/*,pIdx++*/,pVtx++)
	//{
	//	b[nCnt] = pVtx[0].pos;
	//	//a[nCnt] = pIdx[0];
	//}
	//// ���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffMeshwall->Unlock();
	//// �C���f�b�N�X�o�b�t�@���A�����b�N����
	//g_pIdxBuffMeshwall->Unlock();
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawMeshwall(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X


	// �f�o�C�X�̎擾
	pDevice = GetDevice();



	for (int nCnt = 0; nCnt < MAX_MWALL; nCnt++)
	{
		if (g_aMeshwall[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aMeshwall[nCnt].mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(
				&mtxRot,
				g_aMeshwall[nCnt].rot.y,
				g_aMeshwall[nCnt].rot.x,
				g_aMeshwall[nCnt].rot.z);

			D3DXMatrixMultiply(
				&g_aMeshwall[nCnt].mtxWorld,
				&g_aMeshwall[nCnt].mtxWorld,
				&mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(
				&mtxTrans,
				g_aMeshwall[nCnt].pos.x,
				g_aMeshwall[nCnt].pos.y,
				g_aMeshwall[nCnt].pos.z);

			D3DXMatrixMultiply(
				&g_aMeshwall[nCnt].mtxWorld,
				&g_aMeshwall[nCnt].mtxWorld,
				&mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aMeshwall[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));

			// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffMeshwall);

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMeshwall);

			// �|���S���̕`��
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
				0,
				0,
				g_aMeshwall[nCnt].nIdxPoint/*g_nIdxPointWall*/,				// ���_��
				0,
				g_aMeshwall[nCnt].nPolygon/*g_nPolygonWall*/);			// �v���~�e�B�u��
		}
	}
}

//==============================================================================
//	���b�V���ǂ̐ݒ�
//==============================================================================
void SetMeshwall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight,int nWidth,int nHeight)
{
	// ���[�J���ϐ��錾
	Meshwall *pMeshwall;
	pMeshwall = &g_aMeshwall[0];
	//VERTEX_3D *pVtx;

	// �ǂ̐ݒ�
	for (int nCntWall = 0; nCntWall < MAX_MWALL; nCntWall++, pMeshwall++)
	{
		if (pMeshwall->bUse == false)
		{
			pMeshwall->pos = pos;				// �ʒu

			pMeshwall->rot = rot;				// ����

			pMeshwall->fWidth = fWidth;			// ��

			pMeshwall->fHeight = fHeight;		// ����

			pMeshwall->nWidth = nWidth;			// ��̐�

			pMeshwall->nHeight = nHeight;		// �s�̐�

			pMeshwall->nWidthPoint = nWidth + 1;		// ���̒��_��

			pMeshwall->nHeightPoint = nHeight + 1;		// �����̒��_��

			pMeshwall->fWidthMax = pMeshwall->fWidth * (float)nWidth;

			pMeshwall->fHeightMax = pMeshwall->fHeight * (float)nHeight;

			pMeshwall->nAllPoint = nHeight * 2 * (nWidth + 2) - 2;
			pMeshwall->nPolygon = nWidth * nHeight * 2 + (4 * (nHeight - 1));
			pMeshwall->nIdxPoint = (nWidth + 1) * (nHeight + 1);

			pMeshwall->bUse = true;			// �g�p���

			break;
		}
	}
}

void CollisionWall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 move, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{

}