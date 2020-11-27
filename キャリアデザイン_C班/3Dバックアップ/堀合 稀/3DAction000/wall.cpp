//==============================================================================
//
// �ǂ̕`��kwall.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "wall.h"
#include "input.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;		// �e�N�X�`���ւ̃|�C���^
//D3DXVECTOR3 g_posWall;							// �ʒu
//D3DXVECTOR3 g_rotWall;							// ����
//D3DXMATRIX g_mtxWorldWall;						// ���[���h�}�g���b�N�X
Wall g_aWall[MAX_WALL];							// �ǂ̍\����

//==============================================================================
// ����������
//==============================================================================
HRESULT InitWall(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/block001.jpg",
		&g_pTextureWall);

	// �ϐ��̏�����
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].posMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].fWidth = 0.0f;
		g_aWall[nCntWall].fHeight = 0.0f;
		g_aWall[nCntWall].bUse = false;
	}
	//g_posWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++, pVtx += 4)
	{
		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	//// �|���S���̊e���_���W
	//pVtx[0].pos = D3DXVECTOR3(g_posWall.x - 100.0f, g_posWall.y , 100.0f);
	//pVtx[1].pos = D3DXVECTOR3(g_posWall.x - 100.0f, g_posWall.y + 50.0f, 100.0f);
	//pVtx[2].pos = D3DXVECTOR3(g_posWall.x + 100.0f, g_posWall.y , 100.0f);
	//pVtx[3].pos = D3DXVECTOR3(g_posWall.x + 100.0f, g_posWall.y + 50.0f, 100.0f);

	//// �@���x�N�g���̐ݒ�
	//pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	//pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//// �e���_�J���[�̐ݒ�
	//pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//// �e�N�X�`�����_���̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(2.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(2.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitWall(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateWall(void)
{
	// ���[�J���ϐ��錾
	Wall *pWall;
	pWall = &g_aWall[0];
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++, pVtx += 4)
	{
		if (pWall->bUse == true)
		{
			// �|���S���̊e���_���W
			pVtx[0].pos = D3DXVECTOR3(
				pWall->posMove.x - pWall->fWidth, 
				pWall->posMove.y,
				pWall->posMove.z);
			pVtx[1].pos = D3DXVECTOR3(
				pWall->posMove.x - pWall->fWidth, 
				pWall->posMove.y + pWall->fHeight, 
				pWall->posMove.z);
			pVtx[2].pos = D3DXVECTOR3(
				pWall->posMove.x + pWall->fWidth, 
				pWall->posMove.y,
				pWall->posMove.z);
			pVtx[3].pos = D3DXVECTOR3(
				pWall->posMove.x + pWall->fWidth, 
				pWall->posMove.y + pWall->fHeight, 
				pWall->posMove.z);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, pWall->fHeight / WALL_HEIGHT);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(pWall->fWidth / WALL_WIDTH, pWall->fHeight / WALL_HEIGHT);
			pVtx[3].tex = D3DXVECTOR2(pWall->fWidth / WALL_WIDTH, 0.0f);
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawWall(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot[MAX_WALL], mtxTrans[MAX_WALL];	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			// �����̔��f
			D3DXMatrixRotationYawPitchRoll(
				&mtxRot[nCntWall],
				g_aWall[nCntWall].rot.y,
				g_aWall[nCntWall].rot.x,
				g_aWall[nCntWall].rot.z);

			D3DXMatrixMultiply(
				&g_aWall[nCntWall].mtxWorld,
				&g_aWall[nCntWall].mtxWorld,
				&mtxRot[nCntWall]);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(
				&mtxTrans[nCntWall],
				g_aWall[nCntWall].pos.x,
				g_aWall[nCntWall].pos.y,
				g_aWall[nCntWall].pos.z);

			D3DXMatrixMultiply(
				&g_aWall[nCntWall].mtxWorld,
				&g_aWall[nCntWall].mtxWorld,
				&mtxTrans[nCntWall]);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);
		}	
	}

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_mtxWorldWall);

	//// �����̔��f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotWall.y, g_rotWall.x, g_rotWall.z);
	//D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxRot);

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, g_posWall.x, g_posWall.y, g_posWall.z);
	//D3DXMatrixMultiply(&g_mtxWorldWall, &g_mtxWorldWall, &mtxTrans);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldWall);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCntWall * 4,			// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureWall);

	//// �|���S���̕`��
	//pDevice->DrawPrimitive(
	//	D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
	//	0,						// �`����J�n���钸�_�C���f�b�N�X
	//	2);						// �`�悷��v���~�e�B�u��
}

//==============================================================================
// �ǂ̐ݒ�
//==============================================================================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	// ���[�J���ϐ��錾
	Wall *pWall;
	pWall = &g_aWall[0];
	VERTEX_3D *pVtx;

	// �ǂ̐ݒ�
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pWall++)
	{
		if (pWall->bUse == false)
		{
			pWall->posMove = pos;		// �ʒu

			pWall->rot = rot;			// ����

			pWall->fWidth = fWidth;		// ��

			pWall->fHeight = fHeight;	// ����

			pWall->bUse = true;			// �g�p���

			break;
		}
	}
}