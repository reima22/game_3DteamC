//-----------------------------------------------------------------------------
//
// ���b�V���t�B�[���h�̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "meshfild.h"
#include "input.h"

//�}�N��
#define WALL_SIZE (100)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshwall = NULL;	//���_���
LPDIRECT3DINDEXBUFFER9 g_pIndxBuffMeshwall = NULL;	//
LPDIRECT3DTEXTURE9 g_pTextureMeshwall = NULL;		//�e�N�X�`��
D3DXVECTOR3 g_posMeshwall;
D3DXVECTOR3 g_rotMeshwall;
D3DXMATRIX g_mtxWorldMeshwall;

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
HRESULT InitMeshwall(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field000.jpg", &g_pTextureMeshwall);

	g_posMeshwall = (D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	g_rotMeshwall = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED, &g_pVtxBuffMeshwall, NULL);

	//�C���f�b�N�X�o�b�t�@����
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndxBuffMeshwall, NULL);

	WORD * pIndx;

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�|�C���^���擾
	g_pVtxBuffMeshwall->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_posMeshwall.x - WALL_SIZE, g_posMeshwall.y + WALL_SIZE * 2, g_posMeshwall.z );
	pVtx[1].pos = D3DXVECTOR3(g_posMeshwall.x, g_posMeshwall.y + WALL_SIZE * 2, g_posMeshwall.z);
	pVtx[2].pos = D3DXVECTOR3(g_posMeshwall.x + WALL_SIZE, g_posMeshwall.y + WALL_SIZE * 2, g_posMeshwall.z);
	pVtx[3].pos = D3DXVECTOR3(g_posMeshwall.x - WALL_SIZE, g_posMeshwall.y + WALL_SIZE, g_posMeshwall.z);
	pVtx[4].pos = D3DXVECTOR3(g_posMeshwall.x, g_posMeshwall.y + WALL_SIZE, g_posMeshwall.z);
	pVtx[5].pos = D3DXVECTOR3(g_posMeshwall.x + WALL_SIZE, g_posMeshwall.y + WALL_SIZE, g_posMeshwall.z);
	pVtx[6].pos = D3DXVECTOR3(g_posMeshwall.x - WALL_SIZE, g_posMeshwall.y, g_posMeshwall.z);
	pVtx[7].pos = D3DXVECTOR3(g_posMeshwall.x, g_posMeshwall.y, g_posMeshwall.z);
	pVtx[8].pos = D3DXVECTOR3(g_posMeshwall.x + WALL_SIZE, g_posMeshwall.y, g_posMeshwall.z);

	//�C���f�b�N�X�o�b�t�@�����b�N���ԍ��|�C���^�ւ̂��|�C���^���擾
	g_pIndxBuffMeshwall->Lock(0, 0, (void**)&pIndx, 0);

	//for��������+1

	//�ԍ��f�[�^�̐ݒ�

		pIndx[0] = 3;
		pIndx[1] = 0;
		pIndx[2] = 4;
		pIndx[3] = 1;
		pIndx[4] = 5;
		pIndx[5] = 2;
		pIndx[6] = 2;
		pIndx[7] = 6;
		pIndx[8] = 6;
		pIndx[9] = 3;
		pIndx[10] = 7;
		pIndx[11] = 4;
		pIndx[12] = 8;
		pIndx[13] = 5;

	//���_�o�b�t�@���A�����b�N����
	g_pIndxBuffMeshwall->Unlock();

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[4].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[5].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[6].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[7].col = D3DXCOLOR(255, 255, 255, 255);
	pVtx[8].col = D3DXCOLOR(255, 255, 255, 255);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshwall->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitMeshwall(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffMeshwall != NULL)
	{
		g_pVtxBuffMeshwall->Release();
		g_pVtxBuffMeshwall = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureMeshwall != NULL)
	{
		g_pTextureMeshwall->Release();
		g_pTextureMeshwall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�J��
	if (g_pIndxBuffMeshwall != NULL)
	{
		g_pIndxBuffMeshwall->Release();
		g_pIndxBuffMeshwall = NULL;
	}

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdateMeshwall(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawMeshwall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldMeshwall);

	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshwall.y, g_rotMeshwall.x, g_rotMeshwall.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshwall, &g_mtxWorldMeshwall, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posMeshwall.x, g_posMeshwall.y, g_posMeshwall.z);

	D3DXMatrixMultiply(&g_mtxWorldMeshwall, &g_mtxWorldMeshwall, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshwall);

	//���_�o�b�t�@�f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshwall, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIndxBuffMeshwall);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshwall);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 14, 0, 12);
}