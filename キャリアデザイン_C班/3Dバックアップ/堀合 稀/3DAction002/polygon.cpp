//==============================================================================
//
// 3D�|���S���̕`��kpolygon.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "polygon.h"
#include "input.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;		// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posPolygon;							// �ʒu
D3DXVECTOR3 g_rotPolygon;							// ����
D3DXMATRIX g_mtxWorldPolygon;						// ���[���h�}�g���b�N�X
D3DXVECTOR3 g_movePolygon;
D3DXVECTOR3 g_moveRot;

//==============================================================================
// ����������
//==============================================================================
HRESULT InitPolygon(void)
{
	// ���[�J���ϐ��錾
	//VERTEX_2D *pVtx;
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/block000.jpg",
		&g_pTexturePolygon);

	// �ϐ��̏�����
	g_posPolygon = D3DXVECTOR3(0.0f, -40.0f, 0.0f);
	g_rotPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_movePolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(g_posPolygon.x - 100.0f, 0.0f, g_posPolygon.z - 100.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posPolygon.x - 100.0f, 0.0f, g_posPolygon.z + 100.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posPolygon.x + 100.0f, 0.0f, g_posPolygon.z - 100.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posPolygon.x + 100.0f, 0.0f, g_posPolygon.z + 100.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitPolygon(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdatePolygon(void)
{
	//if (GetKeyboardPress(KEYINFO_UP) == true)
	//{
	//	g_movePolygon.z = 1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_DOWN) == true)
	//{
	//	g_movePolygon.z = -1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_LEFT) == true)
	//{
	//	g_movePolygon.x = -1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	//{
	//	g_movePolygon.x = 1.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_ON) == true)
	//{
	//	g_moveRot.y = 0.05f;
	//}
	//else
	//{
	//	g_moveRot.y = 0.0f;
	//}

	//if (GetKeyboardPress(KEYINFO_UNDER) == true)
	//{
	//	g_moveRot.y = -0.05f;
	//}
	//else
	//{
	//	g_moveRot.y = 0.0f;
	//}

	//g_posPolygon.x += g_movePolygon.x;
	//g_posPolygon.y += g_movePolygon.y;
	//g_posPolygon.z += g_movePolygon.z;
	//g_rotPolygon.x += g_moveRot.x;
	//g_rotPolygon.y += g_moveRot.y;
	//g_rotPolygon.z += g_moveRot.z;
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawPolygon(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePolygon);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}