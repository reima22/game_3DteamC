//================================================
//
//�ǂ̏���[wall.h]
// Author; miura yuudai
//
//================================================
#include "wall.h"


//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTexturewall = NULL;//�e�N�X�`�����
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffwall = NULL;//�C���f�b�N�X�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffwall = NULL;//���_���
Wall g_poswall[256];//�ʒu
D3DXMATRIX g_mtxWorldwall;//���[���h�}�g���b�N�X


//====================
//�|���S���̏���������
//====================
HRESULT InitWall(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field003.jpg", &g_pTexturewall);

	for (int nCntwall = 0; nCntwall < 256; nCntwall++)
	{
		//�ϐ�������
		g_poswall[nCntwall].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_poswall[nCntwall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_poswall[nCntwall].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9 * 256,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffwall,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntwall = 0; nCntwall < 256; nCntwall++)
	{
		for (int nCntwall = 0; nCntwall < 9; nCntwall++)
		{
			//�@���x�N�g���̐ݒ�
			pVtx[nCntwall].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			//���_�J���[�̐ݒ�
			pVtx[nCntwall].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		//���_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;//4���_���Ƃ��炷
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffwall->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14 * 256,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffwall,
		NULL);

	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pIdxBuffwall->Lock(0, 0, (void**)&pIdx, 0);

	//�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffwall->Unlock();

	return S_OK;
}

//==================
//�v���C���[�̏I������
//==================
void UninitWall(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturewall != NULL)
	{
		g_pTexturewall->Release();
		g_pTexturewall = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffwall != NULL)
	{
		g_pVtxBuffwall->Release();
		g_pVtxBuffwall = NULL;
	}
	
	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffwall != NULL)
	{
		g_pIdxBuffwall->Release();
		g_pIdxBuffwall = NULL;
	}
}
//==================
//�v���C���[�̍X�V����
//==================
void UpdateWall(void)
{

}

//====================
//�v���C���[�̕`�揈��
//====================
void DrawWall(void)
{
	Wall *pWall;
	pWall = &g_poswall[0];

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntwall = 0; nCntwall < 256; nCntwall++, pWall++)
	{
		if (pWall->bUse == true)//�e���g�p���Ă��邩�ǂ���
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_mtxWorldwall);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_poswall[nCntwall].rot.y, g_poswall[nCntwall].rot.x, g_poswall[nCntwall].rot.z);

			D3DXMatrixMultiply(&g_mtxWorldwall, &g_mtxWorldwall, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_poswall[nCntwall].Pos.x, g_poswall[nCntwall].Pos.y, g_poswall[nCntwall].Pos.z);

			D3DXMatrixMultiply(&g_mtxWorldwall, &g_mtxWorldwall, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldwall);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffwall, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetIndices(g_pIdxBuffwall);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexturewall);

			//�|���S���̕`��
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);
		}
	}
}
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Wall *pWall;
	pWall = &g_poswall[0];

	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffwall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntwall = 0; nCntwall < 256; nCntwall++, pWall++)
	{
		if (g_poswall[nCntwall].bUse == false)//�e���g�p���Ă��邩�ǂ���
		{
			//�ʒu�ݒ�
			g_poswall[nCntwall].Pos = pos;

			g_poswall[nCntwall].rot = rot;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x - 50, g_poswall[nCntwall].Pos.y + 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[1].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 50, g_poswall[nCntwall].Pos.y + 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[2].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 150, g_poswall[nCntwall].Pos.y + 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[3].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x - 50, g_poswall[nCntwall].Pos.y - 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[4].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 50, g_poswall[nCntwall].Pos.y - 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[5].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 150, g_poswall[nCntwall].Pos.y - 50, g_poswall[nCntwall].Pos.z + 0);
			pVtx[6].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x - 50, g_poswall[nCntwall].Pos.y - 150, g_poswall[nCntwall].Pos.z + 0);
			pVtx[7].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 50, g_poswall[nCntwall].Pos.y - 150, g_poswall[nCntwall].Pos.z + 0);
			pVtx[8].pos = D3DXVECTOR3(g_poswall[nCntwall].Pos.x + 150, g_poswall[nCntwall].Pos.y - 150, g_poswall[nCntwall].Pos.z + 0);

			//�e�̎g�p
			g_poswall[nCntwall].bUse = true;
			break;
		}
		pVtx += 4;//4���_���Ƃ��炷
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffwall->Unlock();
}