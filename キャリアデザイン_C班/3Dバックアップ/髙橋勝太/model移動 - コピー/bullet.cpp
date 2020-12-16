//================================================
//
//�ǂ̏���[Bullet.h]
// Author; takahashi shouta
//
//================================================
#include "Bullet.h"
#include "model.h"
#include"effect.h"

//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//�e�N�X�`�����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;//���_���
D3DXMATRIX g_mtxWorldBullet;//���[���h�}�g���b�N�X
BULLET g_Bullet[MAX_BULLET];

//====================
//�r���{�[�h�̏���������
//====================
HRESULT InitBullet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�ʒu
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//����
		g_Bullet[nCntBullet].nLife = 0;

		//�g���Ă��邩
		g_Bullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-BULLET_SIZE, BULLET_SIZE, 0);
	pVtx[1].pos = D3DXVECTOR3(BULLET_SIZE, BULLET_SIZE, 0);
	pVtx[2].pos = D3DXVECTOR3(-BULLET_SIZE, -BULLET_SIZE, 0);
	pVtx[3].pos = D3DXVECTOR3(BULLET_SIZE, -BULLET_SIZE, 0);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//==================
//�r���{�[�h�̏I������
//==================
void UninitBullet(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//==================
//�r���{�[�h�̍X�V����
//==================
void UpdateBullet(void)
{
	BULLET *pBullet;
	pBullet = &g_Bullet[0];
	MODEL *pModel;
	pModel = GetModel();
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			SetEffect(pBullet->pos, D3DXVECTOR3(0.0f, 0.0f, -0.0f), 4,2);

			//���������炷
			pBullet->nLife--;

			//�����`�F�b�N
			if (pBullet->nLife == 0)
			{
				pBullet->bUse = false;
			}
		}

		//pBullet->move.z -= 0.02;

		//�ʒu�̍X�V
		pBullet->pos.x += pBullet->move.x;
		pBullet->pos.y += pBullet->move.y;
		pBullet->pos.z += pBullet->move.z;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//====================
//�r���{�[�h�̕`�揈��
//====================
void DrawBullet(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//Z�o�b�t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�e�B���O�𖳌�����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�g�p����Ă���Ƃ�
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_mtxWorldBullet, NULL, &mtxView);//�t�s������߂�
			g_mtxWorldBullet._41 = 0.0f;
			g_mtxWorldBullet._42 = 0.0f;
			g_mtxWorldBullet._43 = 0.0f;

			//�ʒu�̔��]
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet, &g_mtxWorldBullet, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}

	//���C�e�B���O��L������
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�o�b�t�@
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nSpeed, int nLife)
{
	BULLET *pBullet;

	VERTEX_3D *pVtx;

	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pBullet = &g_Bullet[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{
			//�ʒu
			pBullet->pos = pos;

			//�ړ���
			pBullet->move = -move *nSpeed;

			pBullet->nLife = nLife;

			//�g�p����
			pBullet->bUse = true;

			break;
		}
		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-------------------------------
//�e�̏��擾
//-------------------------------
BULLET * GetBullet(void)
{
	return &g_Bullet[0];
}