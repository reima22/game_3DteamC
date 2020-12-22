//-----------------------------------------------------------------------------
//
// �|���S���̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "shadow.h"

//�}�N��
#define MAX_SHADOW (50)

//�\����
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXCOLOR col;
	float fWidth;
	float fDepth;
	bool bUse;
}Shadow;

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;		//�e�N�X�`��
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

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_aShadow[nCntShadow].pos = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aShadow[nCntShadow].rot = (D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		g_aShadow[nCntShadow].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aShadow[nCntShadow].bUse = false;
		g_aShadow[nCntShadow].fWidth = 1.0;
		g_aShadow[nCntShadow].fDepth = 1.0;
	}	

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
								D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - g_aShadow[nCntShadow].fWidth, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z + g_aShadow[nCntShadow].fDepth);
		pVtx[1].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + g_aShadow[nCntShadow].fWidth, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z + g_aShadow[nCntShadow].fDepth);
		pVtx[2].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x - g_aShadow[nCntShadow].fWidth, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z - g_aShadow[nCntShadow].fDepth);
		pVtx[3].pos = D3DXVECTOR3(g_aShadow[nCntShadow].pos.x + g_aShadow[nCntShadow].fWidth, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z - g_aShadow[nCntShadow].fDepth);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		g_aShadow[nCntShadow].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.85f);
		pVtx[0].col = g_aShadow[nCntShadow].col;
		pVtx[1].col = g_aShadow[nCntShadow].col;
		pVtx[2].col = g_aShadow[nCntShadow].col;
		pVtx[3].col = g_aShadow[nCntShadow].col;

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
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

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == true)
		{

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCntShadow].mtxWorld);

			// �����𔽉f
			/*g_aShadow[nCntShadow].mtxWorld._11 = g_aShadow[nCntShadow].fWidth;
			g_aShadow[nCntShadow].mtxWorld._33 = g_aShadow[nCntShadow].fDepth;*/

			//�������f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCntShadow].rot.y, g_aShadow[nCntShadow].rot.x, g_aShadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCntShadow].pos.x, g_aShadow[nCntShadow].pos.y, g_aShadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_aShadow[nCntShadow].mtxWorld, &g_aShadow[nCntShadow].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCntShadow].mtxWorld);

			//���_�o�b�t�@�f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	
	int nIndx = -1;

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_aShadow[nCntShadow].bUse == false)
		{
			g_aShadow[nCntShadow].pos = pos;

			g_aShadow[nCntShadow].fWidth = fWidth;

			g_aShadow[nCntShadow].fDepth = fDepth;

			g_aShadow[nCntShadow].bUse = true;

			nIndx = nCntShadow;

			break;
		}
	}
	return nIndx;
}

void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{
	g_aShadow[nIdx].pos = pos;
}
