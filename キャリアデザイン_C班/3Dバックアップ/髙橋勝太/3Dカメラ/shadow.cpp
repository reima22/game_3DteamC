//-----------------------------------------------------------------
//
// �v���C���[�̏��� (player.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "player.h"
#include"camera.h"
#include "shadow.h"
#include "model.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define PLAYER_X		(50)									// ���S����[�܂ł܂ł̒���(x)
#define PLAYER_Y		(50)									// ���S����[�܂ł܂ł̒���(y)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;			//�e�N�X�`��
//D3DXVECTOR3 g_posShadow;							//�ʒu
//D3DXVECTOR3 g_Shadow.rot;							//����
SHADOW g_Shadow[MAX_SHADOW];
D3DXMATRIX g_mtxWorldShadow;						//���[���h�}�g���b�N�X

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitShadow(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/shadow000.jpg", &g_pTextureShadow);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//�ʒu
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//����
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�g���Ă��邩
		g_Shadow[nCntShadow].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffShadow, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 50);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 50);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 50);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 50);

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//�x�N�g���̖@��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
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
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateShadow(void)
{
}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawShadow(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//�g�p����Ă���Ƃ�
		if (g_Shadow[nCntShadow].bUse == true)
		{
			//���Z�����̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldShadow);

			//�����̔��]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);

			//�ʒu�̔��]
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxTrans);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldShadow);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureShadow);

				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			}
		}

		//�ʏ�̍����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
void SetShadow(D3DXVECTOR3 pos)
{
	SHADOW *pShadow;

	VERTEX_3D *pVtx;

	pShadow = &g_Shadow[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++, pShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			//�ʒu
			pShadow->pos = pos;

			//�g�p����
			pShadow->bUse = true;

			////���_���W
			//pVtx[0].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
			//pVtx[1].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
			//pVtx[2].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);
			//pVtx[3].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);

			break;
		}

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;
	SHADOW *pShadow;
	pShadow = &g_Shadow[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//pSpeed += nIdx;
	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
	pVtx[1].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z + SHADOW_SIZE);
	pVtx[2].pos = D3DXVECTOR3(pos.x - SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);
	pVtx[3].pos = D3DXVECTOR3(pos.x + SHADOW_SIZE, 0.0f, pos.z - SHADOW_SIZE);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}
