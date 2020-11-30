//-----------------------------------------------------------------
//
// �v���C���[�̏��� (model.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "model.h"
#include"camera.h"
#include "shadow.h"
#include "input.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define PLAYER_X		(50)									// ���S����[�܂ł܂ł̒���(x)
#define PLAYER_Y		(50)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;	//���_���
LPD3DXBUFFER g_pBuffMetModel = NULL;
DWORD  g_nNumMatModel = 0;						//�}�e���A���̐�
MODEL g_Model;
D3DXMATRIX g_mtxWorldModel;						//���[���h�}�g���b�N�X
float g_modelrot;

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitModel(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//model�ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/airplane000.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMetModel,NULL,&g_nNumMatModel,&g_pMeshModel);
	//D3DXLoadMeshFromX("data/MODEL/��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	//�ʒu
	g_Model.pos = D3DXVECTOR3(0.0f, 15.0f, -30.0f);

	//�e�̏����ʒu
	SetShadow(D3DXVECTOR3(g_Model.pos.x, 0.0f, g_Model.pos.z));

	//����
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitModel(void)
{
	//�}�e���A���̊J��
	if (g_pBuffMetModel != NULL)
	{
		g_pBuffMetModel->Release();
		g_pBuffMetModel = NULL;
	}

	//���b�V���̊J��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateModel(void)
{
	CAMERA  *pCamera;
	pCamera = GetCamera();

	//���f���̈ړ�
	//���ړ�
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Model.move.x += 0.5*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5*sinf(D3DX_PI + pCamera->Camera);
	}
	//�E�ړ�
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Model.move.x -= 0.5*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5*sinf(D3DX_PI + pCamera->Camera);
	}

	//��ړ�
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Model.move.x += 0.5*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5*cosf(D3DX_PI + pCamera->Camera);
	}

	//���ړ�
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Model.move.x -= 0.5*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5*cosf(D3DX_PI + pCamera->Camera);
	}

	//���f������]
	if (GetKeyboardPress(DIK_M) == true)
	{
		g_modelrot -= 0.1;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}

	//���f���E��]
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_modelrot += 0.1;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}

	//�ʒu�X�V
	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.y += g_Model.move.y;
	g_Model.pos.z += g_Model.move.z;
	
	//�ړ��ʂ̌���
	g_Model.move.x -= (0 + g_Model.move.x) * 0.2f;
	g_Model.move.y -= (0 + g_Model.move.y) * 0.2f;
	g_Model.move.z -= (0 + g_Model.move.z) * 0.2f;

	//�e�̈ʒu�X�V
	SetPositionShadow(0, D3DXVECTOR3(g_Model.pos.x, 0.0f, g_Model.pos.z));
}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawModel(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�����̔��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�̔��]
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)g_pBuffMetModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

MODEL *GetModel(void)
{
	return &g_Model;
}