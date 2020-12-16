//-----------------------------------------------------------------
//
// �v���C���[�̏��� (player.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "meshfild.h"
#include"camera.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define MESHFILD_X		(2)		// ���S����[�܂ł܂ł̒���(x)
#define MESHFILD_Y		(2)		// ���S����[�܂ł܂ł̒���(y)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfild = NULL;	//���_���
LPDIRECT3DINDEXBUFFER9 g_pldxBuffMeshFild = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfild = NULL;		//�e�N�X�`��
D3DXVECTOR3 g_posMeshfild;							//�ʒu
D3DXVECTOR3 g_rotMeshfild;							//����
D3DXMATRIX g_mtxWorldMeshfild;						//���[���h�}�g���b�N�X
MESHFILD g_Meshfild[MAX_MESHFILD];
int g_nMeshfildDate;

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitMeshfild(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureMeshfild);
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/item_03.png", &g_pTextureMeshfild);

	//�ʒu
	g_posMeshfild = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//����
	g_rotMeshfild = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


	//���_�o�b�t�@�̐���
	//if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshfild, NULL)))
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (MESHFILD_X + 1) *(MESHFILD_Y + 1), D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffMeshfild, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMeshfild->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
	{
		pVtx[nCntX].pos = D3DXVECTOR3(-50.0f + nCntX*50.0f, 0.0f, 50.0f);

		for (int nCntY = 0; nCntY < MESHFILD_Y; nCntY++)
		{
			//pVtx[nCntX + MESHFILD_X + 1].pos = D3DXVECTOR3(-50.0f + nCntX*50.0f, 0.0f, 0.0f - nCntY*50.0f);
			pVtx[nCntX + MESHFILD_X + 1 + (nCntY * 3)].pos = D3DXVECTOR3(-50.0f + nCntX*50.0f, 0.0f, 0.0f - nCntY*50.0f);
		}
	}

	////���_���W�̐ݒ�
	//pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	//pVtx[2].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	//pVtx[4].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 50.0f);
	//pVtx[6].pos = D3DXVECTOR3(100.0f, 0.0f, 50.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[8].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	//pVtx[9].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[10].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	//pVtx[11].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	//pVtx[12].pos = D3DXVECTOR3(100.0f, 0.0f, -50.0f);
	//pVtx[13].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);

	/*pVtx[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 50.0f);
	pVtx[2].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[3].pos = D3DXVECTOR3(-50.0f, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);
	pVtx[8].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);*/



	////���_�J���[�̐ݒ�
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	for (int nCntMeshfild = 0; nCntMeshfild < (MESHFILD_X + 1) *(MESHFILD_Y + 1); nCntMeshfild++)
	{
		pVtx[nCntMeshfild].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}


	////���_�̏��̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);

	for (int nCntMeshfild = 0; nCntMeshfild < (MESHFILD_X + 1) *(MESHFILD_Y + 1); nCntMeshfild++)
	{
		pVtx[nCntMeshfild].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	////���_�̏��̐ݒ�
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	////pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);

	////���_�̏��̐ݒ�
	//pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);

	//�x�N�g���̖@��
	/*pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);*/

	for (int nCntMeshfild = 0; nCntMeshfild < (MESHFILD_X + 1) *(MESHFILD_Y + 1); nCntMeshfild++)
	{
		pVtx[nCntMeshfild].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfild->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pldxBuffMeshFild, NULL);

	WORD *pldx;			//�C���f�b�N�X���ւ̔ԍ�

	//�C���f�b�N�X�o�b�t�@�����b�N
	g_pldxBuffMeshFild->Lock(0, 0, (void**)&pldx, 0);

	////�ԍ��f�[�^
	//pldx[0] = 3;
	//pldx[1] = 0;
	//pldx[2] = 4;
	//pldx[3] = 1;
	//pldx[4] = 5;
	//pldx[5] = 2;
	//pldx[6] = 2;
	//pldx[7] = 6;
	//pldx[8] = 6;
	//pldx[9] = 3;
	//pldx[10] = 7;
	//pldx[11] = 4;
	//pldx[12] = 8;
	//pldx[13] = 5;

	/*for (int nCntY = 0; nCntY < MESHFILD_Y + 1; nCntY++)
	{
		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			pldx[0 + nCntX * 2] = 0 + nCntX + MESHFILD_X + 1;
		}
	}*/

	for (int nCntY = 0; nCntY < MESHFILD_Y + 1; nCntY++)
	{

		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			pldx[nCntY + 1 + nCntX * 2] = 0 + nCntX;
		}

		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			pldx[nCntY + nCntX * 2] = 0 + nCntX + MESHFILD_X + 1;
		}

		for (int nCntX = 0; nCntX < MESHFILD_X + 1; nCntX++)
		{
			//pldx[nCntY + 3 + nCntX * 2] = 0 + nCntX + MESHFILD_X*2;
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pldxBuffMeshFild->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitMeshfild(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffMeshfild != NULL)
	{
		g_pVtxBuffMeshfild->Release();
		g_pVtxBuffMeshfild = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pldxBuffMeshFild != NULL)
	{
		g_pldxBuffMeshFild->Release();
		g_pldxBuffMeshFild = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureMeshfild != NULL)
	{
		g_pTextureMeshfild->Release();
		g_pTextureMeshfild = NULL;
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateMeshfild(void)
{

}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawMeshfild(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshfild);

	//�����̔��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshfild.y, g_rotMeshfild.x, g_rotMeshfild.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfild, &g_mtxWorldMeshfild, &mtxRot);

	//�ʒu�̔��]
	D3DXMatrixTranslation(&mtxTrans, g_posMeshfild.x, g_posMeshfild.y, g_posMeshfild.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshfild, &g_mtxWorldMeshfild, &mtxTrans);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfild, 0, sizeof(VERTEX_3D));

	//���_�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pldxBuffMeshFild);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshfild);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshfild);

	//�|���S���̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 30);
}