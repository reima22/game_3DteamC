//-----------------------------------------------------------------------------
//
// �|���S���̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "shadow.h"

//�}�N��
#define SHADOW_SIZE (15)
#define MAX_SHADOW (50)

//�\����
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	bool bUse;
}Shadow;

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;		//�e�N�X�`��
D3DXCOLOR Shadowcol;
D3DXVECTOR3 g_posShadow;
D3DXVECTOR3 g_rotShadow;
D3DXMATRIX g_mtxWorldShadow;
Shadow g_aShadow[MAX_SHADOW];

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
HRESULT InitShadow(void)
{
	//���[�J���ϐ�
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	g_posShadow = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	g_rotShadow = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	Shadowcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_posShadow.x - SHADOW_SIZE, g_posShadow.y, g_posShadow.z + SHADOW_SIZE);
	pVtx[1].pos = D3DXVECTOR3(g_posShadow.x + SHADOW_SIZE, g_posShadow.y, g_posShadow.z + SHADOW_SIZE);
	pVtx[2].pos = D3DXVECTOR3(g_posShadow.x - SHADOW_SIZE, g_posShadow.y, g_posShadow.z - SHADOW_SIZE);
	pVtx[3].pos = D3DXVECTOR3(g_posShadow.x + SHADOW_SIZE, g_posShadow.y, g_posShadow.z - SHADOW_SIZE);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[
	Shadowcol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.65f);
	pVtx[0].col = Shadowcol;
	pVtx[1].col = Shadowcol;
	pVtx[2].col = Shadowcol;
	pVtx[3].col = Shadowcol;

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return S_OK;

}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitShadow(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void UpdateShadow(void)
{

}

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posShadow.x, g_posShadow.y, g_posShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	//���_�o�b�t�@�f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
