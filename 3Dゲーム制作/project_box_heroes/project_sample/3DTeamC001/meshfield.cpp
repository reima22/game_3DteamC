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
#define WIDTHNUM	(10)		// ��(��)
#define DEPTHNUM	(10)		// �s��(���s)
#define WIDTH		(100.0f)		// ���̑傫��
#define DEPTH		(100.0f)		// ���s�̑傫��
#define POINT_MAX	(65535)		// ���_���̍ő�
#define IDX_MAX		(65535)		// �C���f�b�N�X�o�b�t�@�̍ő�m�ې�
#define FIELD_MAX	(32)		// �t�B�[���h�̍ő吔

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
float g_fWidth = WIDTH;								// �����̒[
float g_fDepth = DEPTH;								// ���s�̒[
int g_nWidth = WIDTHNUM + 1;						// �����̒��_��
int g_nDepth = DEPTHNUM + 1;						// ���s�̒��_��

//MeshField g_aField[FIELD_MAX];	// �t�B�[���h�̍\����
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

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/field000.jpg",
		&g_pTextureMeshfield);

	// �ϐ��̏�����
	g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nAllPoint = DEPTHNUM * 2 * (WIDTHNUM + 2) - 2;				// �����_��
	g_nPolygon = WIDTHNUM * DEPTHNUM * 2 + (4 * (DEPTHNUM - 1));	// ���|���S����
	g_nIdxPoint = g_nWidth * g_nDepth;								// �C���f�b�N�X�o�b�t�@�ł̒��_��

	float fWidthMax = g_fWidth * (float)WIDTHNUM;
	float fDepthMax = g_fDepth * (float)DEPTHNUM;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_nIdxPoint * FIELD_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < g_nDepth; nCnt++)
	{// ���s��
		for (int nCntA = 0; nCntA < g_nWidth; nCntA++)
		{// ����
			// �|���S���̊e���_���W
			pVtx[0].pos = D3DXVECTOR3(
				-fWidthMax / 2.0f + (float)nCntA * g_fWidth, 
				g_posMeshfield.y, 
				fDepthMax / 2.0f - (float)nCnt * g_fDepth);

			//pVtx[0].pos = D3DXVECTOR3(-g_fWidth + (float)nCntA * fWidthPart, g_posMeshfield.y, g_fDepth - (float)nCnt * fDepthPart);

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntA, 1.0f * nCnt);

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * g_nAllPoint * FIELD_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshfield,
		NULL);

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffMeshfield->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntA = 0; nCntA < DEPTHNUM; nCntA++)
	{
		for (int nCnt = 0; nCnt < g_nWidth + 1; nCnt++, pIdx += 2)
		{
			if (nCnt != 0 && nCnt == g_nWidth && nCntA != DEPTHNUM - 1)
			{// �E�[����܂�Ԃ���
				pIdx[0] = pIdx[-1];
				pIdx[1] = pIdx[-2] + 1;
			}
			else if (nCntA == DEPTHNUM - 1 && nCnt == g_nWidth)
			{// �I�����ɖ�������
				break;
			}
			else
			{// �ʏ�z�u
				pIdx[0] = g_nWidth + (g_nWidth * nCntA) + nCnt;
				pIdx[1] = pIdx[0] - g_nWidth;
			}
		}
	}

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

}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawMeshfield(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	//MeshField *pField;
	//pField = &g_aField[0];

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	//{
	//	if (pField->bUse == true)
	//	{
	//		// ���[���h�}�g���b�N�X�̏�����
	//		D3DXMatrixIdentity(&pField->mtxWorld);
	//		// �����̔��f
	//		D3DXMatrixRotationYawPitchRoll(&mtxRot, pField->rot.y, pField->rot.x, pField->rot.z);
	//		D3DXMatrixMultiply(&pField->mtxWorld, &pField->mtxWorld, &mtxRot);
	//		// �ʒu�𔽉f
	//		D3DXMatrixTranslation(&mtxTrans, pField->pos.x, pField->pos.y, pField->pos.z);
	//		D3DXMatrixMultiply(&pField->mtxWorld, &pField->mtxWorld, &mtxTrans);
	//		// ���[���h�}�g���b�N�X�̐ݒ�
	//		pDevice->SetTransform(D3DTS_WORLD, &pField->mtxWorld);
	//		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//		pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));
	//		// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//		pDevice->SetIndices(g_pIdxBuffMeshfield);
	//		// ���_�t�H�[�}�b�g�̐ݒ�
	//		pDevice->SetFVF(FVF_VERTEX_3D);
	//		// �e�N�X�`���̐ݒ�
	//		pDevice->SetTexture(0, g_pTextureMeshfield);
	//		// �|���S���̕`��
	//		pDevice->DrawIndexedPrimitive(
	//			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
	//			0,
	//			0,
	//			pField->nIdxPoint,			// ���_��
	//			0,
	//			pField->nPolygon);			// �v���~�e�B�u��
	//	}
	//}

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
		g_nIdxPoint,			// ���_��
		0,
		g_nPolygon);			// �v���~�e�B�u��
}

//==============================================================================
// �t�B�[���h�̐ݒ�
//==============================================================================
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nWidth, int nDepth, float fWidth, float fDepth)
{
	//MeshField *pField;
	//pField = &g_aField[0];

	//// �t�B�[���h�̐ݒ�
	//for (int nCnt = 0; nCnt < FIELD_MAX; nCnt++, pField++)
	//{
	//	if (pField->bUse == false)
	//	{
	//		pField->pos = pos;
	//		pField->rot = rot;
	//		pField->nWidth = nWidth + 1;
	//		pField->nDepth = nDepth + 1;
	//		pField->fWidth = fWidth;
	//		pField->fDepth = fDepth;
	//		pField->fWidthMax = fWidth * (float)nWidth;
	//		pField->fDepthMax = fDepth * (float)nDepth;
	//		pField->bUse = true;
	//		break;
	//	}
	//}
}