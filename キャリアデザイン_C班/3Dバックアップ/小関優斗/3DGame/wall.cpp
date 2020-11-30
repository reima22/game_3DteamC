//-----------------------------------------------------------------------------
//
// �ǂ̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "wall.h"

//�}�N��
#define POLYGON_SIZE (100)
#define MAX_WALL (3)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		//�e�N�X�`��
Wall g_aWall[MAX_WALL];
D3DXMATRIX g_mtxWorldWall;

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
HRESULT InitWall(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field001.jpg", &g_pTextureWall);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aWall[nCntWall].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
								D3DPOOL_MANAGED, &g_pVtxBuffWall, NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{

		g_aWall[0].pos = (D3DXVECTOR3(0.0f, 0.0f, 50.0f));

		g_aWall[1].pos = (D3DXVECTOR3(0.0f, 0.0f, 50.0f));

		g_aWall[2].pos = (D3DXVECTOR3(0.0f, 0.0f, 50.0f));

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - POLYGON_SIZE, g_aWall[nCntWall].pos.y + POLYGON_SIZE, g_aWall[nCntWall].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + POLYGON_SIZE, g_aWall[nCntWall].pos.y + POLYGON_SIZE, g_aWall[nCntWall].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x - POLYGON_SIZE, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aWall[nCntWall].pos.x + POLYGON_SIZE, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[
		g_aWall[nCntWall].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[0].col = g_aWall[nCntWall].col;
		pVtx[1].col = g_aWall[nCntWall].col;
		pVtx[2].col = g_aWall[nCntWall].col;
		pVtx[3].col = g_aWall[nCntWall].col;

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitWall(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdateWall(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_mtxWorldWall);

		//�������f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);

		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);

		D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

		//���_�o�b�t�@�f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
	}
}
