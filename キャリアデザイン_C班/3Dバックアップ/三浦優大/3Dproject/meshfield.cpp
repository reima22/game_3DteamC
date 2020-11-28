//================================================
//
//�v���C���[����[Meshfeild.h]
// Author; miura yuudai
//
//================================================
#include "meshfield.h"


//==============
//�O���[�o���ϐ�
//==============
LPDIRECT3DTEXTURE9 g_pTexturemeshfield = NULL;//�e�N�X�`�����
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;//�C���f�b�N�X�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffmeshfield = NULL;//���_���
MESHFIELD g_posmeshfield;//�ʒu
D3DXVECTOR3 g_rotmeshfield;//����
D3DXMATRIX g_mtxWorldmeshfield;//���[���h�}�g���b�N�X
float g_field;


//====================
//�|���S���̏���������
//====================
HRESULT InitMeshfield(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/field004.jpg", &g_pTexturemeshfield);

	//�ϐ�������
	g_posmeshfield.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotmeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 9,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffmeshfield,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffmeshfield->Lock(0, 0, (void**)&pVtx, 0);


	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-50, 0, 50);
	pVtx[1].pos = D3DXVECTOR3(50, 0, 50);
	pVtx[2].pos = D3DXVECTOR3(150, 0, 50);
	pVtx[3].pos = D3DXVECTOR3(-50, 0, -50);
	pVtx[4].pos = D3DXVECTOR3(50, 0, -50);
	pVtx[5].pos = D3DXVECTOR3(150, 0, -50);
	pVtx[6].pos = D3DXVECTOR3(-50, 0, -150);
	pVtx[7].pos = D3DXVECTOR3(50, 0, -150);
	pVtx[8].pos = D3DXVECTOR3(150, 0, -150);

	for (int nCntfield = 0; nCntfield < 9; nCntfield++)
	{
		//�@���x�N�g���̐ݒ�
		pVtx[nCntfield].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntfield].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(3.0f, 2.0f);
	pVtx[1].tex = D3DXVECTOR2(3.0f, 3.0f);
	pVtx[2].tex = D3DXVECTOR2(3.0f, 2.0f);
	pVtx[3].tex = D3DXVECTOR2(2.0f, 2.0f);
	pVtx[4].tex = D3DXVECTOR2(2.0f, 3.0f);
	pVtx[5].tex = D3DXVECTOR2(2.0f, 2.0f);
	pVtx[6].tex = D3DXVECTOR2(2.0f, 3.0f);
	pVtx[7].tex = D3DXVECTOR2(3.0f, 3.0f);
	pVtx[8].tex = D3DXVECTOR2(3.0f, 2.0f);


	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffmeshfield->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
	D3DUSAGE_WRITEONLY,
	D3DFMT_INDEX16,
	D3DPOOL_MANAGED,
	&g_pIdxBuffMeshField,
	NULL);

	WORD *pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();
	return S_OK;
}

//==================
//�v���C���[�̏I������
//==================
void UninitMeshfield(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturemeshfield != NULL)
	{
		g_pTexturemeshfield->Release();
		g_pTexturemeshfield = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffmeshfield != NULL)
	{
		g_pVtxBuffmeshfield->Release();
		g_pVtxBuffmeshfield = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}
//==================
//�v���C���[�̍X�V����
//==================
void UpdateMeshfield(void)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���̃|�C���^���擾
	g_pVtxBuffmeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx[2].pos.y += 0.1f;
	//pVtx[11].pos.y += 0.1f;

	D3DXVECTOR3 vec;
	float fAngle;
	D3DXVECTOR3 move;

	vec = pVtx[2].pos - pVtx[1].pos;//���ݒn����ړI�n�ւ̃x�N�g��
	fAngle = atan2f(vec.x, vec.y);//�x�N�g���̊p�x�����߂�
	move.x = cosf(fAngle) * 1.0f;//�ړ��ʂ����߂�
	move.y = cosf(fAngle) * 1.0f;//�ړ��ʂ����߂�

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffmeshfield->Unlock();
}

//====================
//�v���C���[�̕`�揈��
//====================
void DrawMeshfield(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldmeshfield);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotmeshfield.y, g_rotmeshfield.x, g_rotmeshfield.z);

	D3DXMatrixMultiply(&g_mtxWorldmeshfield, &g_mtxWorldmeshfield, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posmeshfield.Pos.x, g_posmeshfield.Pos.y, g_posmeshfield.Pos.z);

	D3DXMatrixMultiply(&g_mtxWorldmeshfield, &g_mtxWorldmeshfield, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldmeshfield);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffmeshfield, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshField);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturemeshfield);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 14);

}