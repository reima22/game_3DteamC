//==============================================================================
//
// �e�̕`��kshadow.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "shadow.h"
#include "input.h"
#include "model.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			// �e�N�X�`���ւ̃|�C���^
Shadow g_aShadow[MAX_SHADOW];						// �e�̍\����

//==============================================================================
// ����������
//==============================================================================
HRESULT InitShadow(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/shadow000.jpg",
		&g_pTextureShadow);

	// �ϐ��̏�����
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aShadow[nCntShadow].fWidth = 0.0f;
		g_aShadow[nCntShadow].fDepth = 0.0f;
		g_aShadow[nCntShadow].bUse = false;
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++,pVtx += 4)
	{
		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f,0.85f);
		pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f,0.85f);
		pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f,0.85f);
		pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f,0.85f);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitShadow(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateShadow(void)
{

}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawShadow(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���Z�����̐���
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aShadow[nCnt].mtxWorld);

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCnt].rot.y, g_aShadow[nCnt].rot.x, g_aShadow[nCnt].rot.z);
		D3DXMatrixMultiply(&g_aShadow[nCnt].mtxWorld, &g_aShadow[nCnt].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCnt].pos.x, g_aShadow[nCnt].pos.y, g_aShadow[nCnt].pos.z);
		D3DXMatrixMultiply(&g_aShadow[nCnt].mtxWorld, &g_aShadow[nCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCnt].mtxWorld);
	}

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_mtxWorldShadow);

	//// �����̔��f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotShadow.y, g_rotShadow.x, g_rotShadow.z);
	//D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, g_posShadow.x, g_posShadow.y, g_posShadow.z);
	//D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureShadow);

	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}

	//// �|���S���̕`��
	//pDevice->DrawPrimitive(
	//	D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
	//	0,						// �`����J�n���钸�_�C���f�b�N�X
	//	2);						// �`�悷��v���~�e�B�u��

	// �ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
}

//==============================================================================
// �e�̐ݒ�
//==============================================================================
int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	// ���[�J���ϐ��錾
	Shadow *pShadow;
	pShadow = &g_aShadow[0];
	int nIdx = -1;

	// �e�̐ݒ�
	for (int nCnt = 0; nCnt < MAX_SHADOW; nCnt++,pShadow++)
	{
		if (pShadow->bUse == false)
		{
			pShadow->pos = pos;			// �ʒu�̐ݒ�

			pShadow->fWidth = fWidth;	// ���̐ݒ�

			pShadow->fDepth = fDepth;	// ���s�̐ݒ�

			pShadow->bUse = true;		// �g�p��Ԃւ̈ڍs

			nIdx = nCnt;				// �C���f�b�N�X�ւ̑��

			break;
		}
	}

	return nIdx;	// nIdx�ԖڂƂ��ĕԂ�
}

//==============================================================================
// �e�̒Ǐ]
//==============================================================================
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	Shadow *pShadow;
	pShadow = &g_aShadow[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	// �|�C���^�̈ړ�
	pVtx += nIdx * 4;
	pShadow += nIdx;

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(pos.x - pShadow->fWidth, 0.0f, pos.z - pShadow->fDepth);
	pVtx[1].pos = D3DXVECTOR3(pos.x - pShadow->fWidth, 0.0f, pos.z + pShadow->fDepth);
	pVtx[2].pos = D3DXVECTOR3(pos.x + pShadow->fWidth, 0.0f, pos.z - pShadow->fDepth);
	pVtx[3].pos = D3DXVECTOR3(pos.x + pShadow->fWidth, 0.0f, pos.z + pShadow->fDepth);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}