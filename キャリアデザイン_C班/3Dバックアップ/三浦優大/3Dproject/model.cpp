//================================================
//
//���f������[model.h]
// Author; miura yuudai
//
//================================================

#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"

//=====================
//�O���[�o���ϐ�
//=====================
//���b�V���i���_���j�ւ̃|�C���^
LPD3DXMESH g_pMeshModel = NULL;

//�}�e���A���i�ގ����j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;

DWORD g_nNumMatModel = 0;//�}�e���A���̐�
MODEL g_PosModel;//�ʒu
D3DXMATRIX g_mtxWolrdModel;//���[���h�}�g���b�N�X
float g_model;

//====================
//���f���̏���������
//====================
void InitModel(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//x�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/car002.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	//�ϐ�������
	g_PosModel.Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosModel.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosModel.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_PosModel.rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_model = 0.0f;
}
//=======================
//���f���̏I������
//=======================
void UninitModel(void)
{
	//���_�̊J��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�ގ��̊J��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}
//=======================
//���f���̍X�V����
//=======================
void UpdateModel(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	//SetShadow(g_PosModel.Pos, 20, 20);

	if (GetKeyboardPress(DIK_RIGHT) == true)//�v���C���[�̉�]
	{
		g_PosModel.rot.y = -1.57f;
		g_PosModel.move.x -= cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z -= sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}
	if (GetKeyboardPress(DIK_LEFT) == true)//�v���C���[�̉�]
	{
		g_PosModel.rot.y = 1.57f;
		g_PosModel.move.x += cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z += sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}
	if (GetKeyboardPress(DIK_DOWN) == true)//�v���C���[�̉�]
	{
		g_PosModel.move.x -= sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z += cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}
	if (GetKeyboardPress(DIK_UP) == true)//�v���C���[�̉�]
	{
		g_PosModel.move.x += sinf(D3DX_PI + pCamera->rot.y) * 0.5f;
		g_PosModel.move.z -= cosf(D3DX_PI + pCamera->rot.y) * 0.5f;
	}

	if (GetKeyboardPress(DIK_K) == true)//�v���C���[�̉�]
	{
		g_model += 0.1f;
		g_PosModel.rot.y = g_model;
	}

	//��]�p�x���Z�b�g
	if (g_PosModel.rot.y >= D3DX_PI)
	{
		g_PosModel.rot.y = -D3DX_PI;
	}

	/*else if (g_PosModel.rot.y <= -D3DX_PI)
	{
		g_PosModel.rot.y = D3DX_PI;
	}*/
	
	//�ʒu�X�V
	g_PosModel.Pos.x += g_PosModel.move.x;
	g_PosModel.Pos.z += g_PosModel.move.z;
	g_PosModel.rot.y += g_PosModel.rotmove.y;

	// �ړ��ʂ̌���
	g_PosModel.move.x += (0.0f - g_PosModel.move.x) *0.3f;
	g_PosModel.move.z += (0.0f - g_PosModel.move.z) *0.3f;
	g_PosModel.rotmove.y  += (0.0f - g_PosModel.rotmove.y) *0.3f;
}
//=======================
//���f���̕`�揈��
//=======================
void DrawModel(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//�}�e���A���ւ̃|�C���^
	D3DXMATERIAL *pMat;

	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWolrdModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PosModel.rot.y, g_PosModel.rot.x, g_PosModel.rot.z);

	D3DXMatrixMultiply(&g_mtxWolrdModel, &g_mtxWolrdModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_PosModel.Pos.x, g_PosModel.Pos.y, g_PosModel.Pos.z);

	D3DXMatrixMultiply(&g_mtxWolrdModel, &g_mtxWolrdModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWolrdModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
MODEL *GetModel(void)
{
	return &g_PosModel;
}
