//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "meshfield.h"
#include "input.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define WIDTH	(2)		// ��(��)
#define DEPTH	(2)		// �s��(���s)
//#define POINT	(14)	// ���_��
//#define POLY	(12)	// �|���S����

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshfield = NULL;	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posMeshfield;							// �ʒu
D3DXVECTOR3 g_rotMeshfield;							// ����
D3DXMATRIX g_mtxWorldMeshfield;						// ���[���h�}�g���b�N�X
int g_nAllPoint;									// �����_��
int g_nPolygon;										// �|���S����
int g_nIdxPoint;									// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
float g_fWidth;		// �����̒[
float g_fDepth;		// ���s�̒[
//D3DXVECTOR3 g_movePolygon;
//D3DXVECTOR3 g_moveRot;

//==============================================================================
// ����������
//==============================================================================
HRESULT InitMeshfield(void)
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
		&g_pTextureMeshfield);

	// �ϐ��̏�����
	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nAllPoint = DEPTH * 2 * (WIDTH + 2) - 2;			// �����_��
	g_nPolygon = WIDTH * DEPTH * 2 + (4 * (DEPTH - 1));	// ���|���S����
	g_nIdxPoint = (WIDTH + 1) * (DEPTH + 1);			// �C���f�b�N�X�o�b�t�@�ł̒��_��
	g_fWidth = 100.0f;
	g_fDepth = 100.0f;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_nIdxPoint,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̊e���_���W
	//for (int nCnt = 0; nCnt < DEPTH + 1; nCnt++)
	//{// ���s��
	//	for (int nCntA = 0; nCntA < WIDTH + 1; nCntA++, nCount++)
	//	{// ����
	//		pVtx[nCount].pos = D3DXVECTOR3(-g_fWidth + ((float)nCntA * g_fWidth), 0.0f, g_fDepth - ((float)nCnt * g_fDepth));
	//	}
	//}

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	pVtx[2].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	pVtx[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	pVtx[8].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	//pVtx[9].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, 0.0f);
	//pVtx[0].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[4].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[6].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, g_posMeshfield.z + 100.0f);
	//pVtx[7].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[8].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[9].pos = D3DXVECTOR3(g_posMeshfield.x - 100.0f, 0.0f, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(0.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[11].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[12].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, g_posMeshfield.z - 100.0f);
	//pVtx[13].pos = D3DXVECTOR3(g_posMeshfield.x + 100.0f, 0.0f, 0.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	//pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
	//pVtx[9].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[10].tex = D3DXVECTOR2(1.0f, 2.0f);
	//pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[12].tex = D3DXVECTOR2(2.0f, 2.0f);
	//pVtx[13].tex = D3DXVECTOR2(2.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * g_nAllPoint,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	//for (int nCntA = 0; nCntA < DEPTH + 1; nCntA++)
	//{
	//	for (int nCnt = 0; nCnt < (WIDTH + 1) * 2; nCnt++, pIdx += 2)
	//	{
	//		pIdx[0] = pId;
	//		pIdx[1] = pIdx[0] - (WIDTH + 1);
	//	}
	//}


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

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffMeshfield->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitMeshfield(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshfield != NULL)
	{
		g_pIdxBuffMeshfield->Release();
		g_pIdxBuffMeshfield = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateMeshfield(void)
{
	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_movePolygon.z = 1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_movePolygon.z = -1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_movePolygon.x = -1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_movePolygon.x = 1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_ON) == true)
	//{
	//	g_moveRot.y = 0.05f;
	//}
	//else
	//{
	//	g_moveRot.y = 0.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_UNDER) == true)
	//{
	//	g_moveRot.y = -0.05f;
	//}
	//else
	//{
	//	g_moveRot.y = 0.0f;
	//}

	//g_posPolygon.x += g_movePolygon.x;
	//g_posPolygon.y += g_movePolygon.y;
	//g_posPolygon.z += g_movePolygon.z;
	//g_rotPolygon.x += g_moveRot.x;
	//g_rotPolygon.y += g_moveRot.y;
	//g_rotPolygon.z += g_moveRot.z;
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawMeshfield(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfield);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfield.y, g_rotMeshfield.x, g_rotMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfield.x, g_posMeshfield.y, g_posMeshfield.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfield, &g_mtxWorldMeshfield, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfield);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshfield);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfield);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						
		0,
		9,						// ���_��
		0,
		14);					// �v���~�e�B�u��

	//pDevice->DrawPrimitive(
	//	D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
	//	0,						// �`����J�n���钸�_�C���f�b�N�X
	//	g_nPolygon);			// �`�悷��v���~�e�B�u��
}