//================================================
//
//�e�̏���[Syadow.h]
// Author; miura yuudai
//
//================================================
#include "Shadow.h"
#include "model.h"


//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;//���_���
SHADOW g_posbaseShadow[256];//�ʒu
D3DXVECTOR3 g_rotShadow;//����
D3DXMATRIX g_mtxWorldShadow;//���[���h�}�g���b�N�X


//====================
//�e�̏���������
//====================
HRESULT InitShadow(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		//�ϐ�������
		g_posbaseShadow[nCntShadow].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z + 20);
		pVtx[1].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z + 20);
		pVtx[2].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z - 20);
		pVtx[3].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + 20, 0.0, g_posbaseShadow[nCntShadow].Pos.z - 20);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 95);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 95);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 95);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 95);

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//==================
//�e�̏I������
//==================
void UninitShadow(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}
//==================
//�e�̍X�V����
//==================
void UpdateShadow(void)
{
	MODEL *pModel;
	pModel = GetModel();
	SetShadow(pModel->Pos, 20, 20);
}

//====================
//�e�̕`�揈��
//====================
void DrawShadow(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	SHADOW *pShadow;
	pShadow = &g_posbaseShadow[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldShadow);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++)
	{
		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_posbaseShadow[nCntShadow].Pos.x, g_posbaseShadow[nCntShadow].Pos.y, g_posbaseShadow[nCntShadow].Pos.z);
	}

	D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}
void SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	VERTEX_3D *pVtx;

	SHADOW *pShadow;
	pShadow = &g_posbaseShadow[0];

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < 256; nCntShadow++,pShadow++)
	{
		if (g_posbaseShadow[nCntShadow].bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			g_posbaseShadow[nCntShadow].Pos = pos;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z + fDepth);//2D��0.0�Œ�
			pVtx[1].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z + fDepth);
			pVtx[2].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x - fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z - fDepth);
			pVtx[3].pos = D3DXVECTOR3(g_posbaseShadow[nCntShadow].Pos.x + fWidth, 0.0f, g_posbaseShadow[nCntShadow].Pos.z - fDepth);

			//�e�̎g�p
			g_posbaseShadow[nCntShadow].bUse = true;
			break;
		}
		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffShadow->Unlock();
}
