//-----------------------------------------------------------------------------
//
// �r���{�[�h�̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "billboard.h"

//�}�N��
#define POLYGON_SIZE (100)

//�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
}board;

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffbillboard = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTexturebillboard = NULL;		//�e�N�X�`��
board Billboard;
D3DXMATRIX g_mtxWorldBillboard;

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
HRESULT InitBillboard(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field001.jpg", &g_pTexturebillboard);

	Billboard.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED, &g_pVtxBuffbillboard, NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�|�C���^���擾
	g_pVtxBuffbillboard->Lock(0, 0, (void**)&pVtx, 0);

	Billboard.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(Billboard.pos.x - POLYGON_SIZE, Billboard.pos.y + POLYGON_SIZE, Billboard.pos.z);
	pVtx[1].pos = D3DXVECTOR3(Billboard.pos.x + POLYGON_SIZE, Billboard.pos.y + POLYGON_SIZE, Billboard.pos.z);
	pVtx[2].pos = D3DXVECTOR3(Billboard.pos.x - POLYGON_SIZE, Billboard.pos.y, Billboard.pos.z);
	pVtx[3].pos = D3DXVECTOR3(Billboard.pos.x + POLYGON_SIZE, Billboard.pos.y, Billboard.pos.z);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[
	Billboard.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[0].col = Billboard.col;
	pVtx[1].col = Billboard.col;
	pVtx[2].col = Billboard.col;
	pVtx[3].col = Billboard.col;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffbillboard->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitBillboard(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffbillboard != NULL)
	{
		g_pVtxBuffbillboard->Release();
		g_pVtxBuffbillboard = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTexturebillboard != NULL)
	{
		g_pTexturebillboard->Release();
		g_pTexturebillboard = NULL;
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdateBillboard(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxTrans;
	D3DXMATRIX mtxView;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//�r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//���C�e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�|���S�����J�����ɑ΂��Đ��ʂɂ���
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);	//�t�s������߂�

	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, Billboard.pos.x, Billboard.pos.y, Billboard.pos.z);

	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//���_�o�b�t�@�f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffbillboard, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturebillboard);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//���C�e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
