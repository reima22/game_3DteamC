//-----------------------------------------------------------------------------
//
// ���f���`��̏���
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "model.h"
#include "input.h"
#include "camera.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define MOVE_MODEL_SPEED (3.0f)
#define MODEL_ROT_SPEED (0.05f)
#define MODEL_ROT_SPEED2 (0.5f)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;			//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;	//�}�e���A���i�ގ����j�ւ̃|�C���^
DWORD g_NumMatModel = 0;				//�}�e���A���̐�
Model g_Model;							//���f�����
D3DXMATRIX g_mtxWorldModel;				//���[���h�}�g���b�N�X

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------

//���[�J���ϐ�
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXLoadMeshFromX("data/MODEL/car001.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatModel, NULL, &g_NumMatModel, &g_pMeshModel);

	//�ʒu������
	g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//����������
	g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitModel(void)
{

	//���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}

	////�e�N�X�`���̊J��
	//if (g_pTexturePolygon != NULL)
	//{
	//	g_pTexturePolygon->Release();
	//	g_pTexturePolygon = NULL;
	//}


}

//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void UpdateModel(void)
{
	
	Camera *pCamera;
	pCamera = GetCamera();

	if (g_Model.PurposeRot.y > D3DX_PI)
	{
		g_Model.PurposeRot.y -= D3DX_PI * 2.0f;
	}
	if (g_Model.PurposeRot.y < -D3DX_PI)
	{
		g_Model.PurposeRot.y += D3DX_PI * 2.0f;
	}
	if (g_Model.rot.y > D3DX_PI)
	{
		g_Model.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rot.y += D3DX_PI * 2.0f;
	}

	//���f���ړ��E
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Model.PurposeRot.y -= cosf(pCamera->rot.y - g_Model.PurposeRot.y) * MODEL_ROT_SPEED2;
		g_Model.pos.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.pos.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;


	}

	//���f���ړ���						 
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_Model.PurposeRot.y += cosf(pCamera->rot.y - g_Model.PurposeRot.y) * MODEL_ROT_SPEED2;
		g_Model.pos.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.pos.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
	}

	//���f���ړ���						 
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Model.PurposeRot.y -= sinf(pCamera->rot.y - g_Model.PurposeRot.y) * MODEL_ROT_SPEED2;
		g_Model.pos.x += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.pos.z += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
	}

	//���f���ړ���O						
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Model.PurposeRot.y += sinf(pCamera->rot.y - g_Model.PurposeRot.y) * MODEL_ROT_SPEED2;
		g_Model.pos.x -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.pos.z -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
	}

	//���f���E��]
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_Model.PurposeRot.y += MODEL_ROT_SPEED;
		g_Model.rot.y += sinf(g_Model.PurposeRot.y - g_Model.rot.y) * 0.5f;
	}

	//���f������]
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Model.PurposeRot.y -= MODEL_ROT_SPEED;
		g_Model.rot.y += sinf(g_Model.PurposeRot.y - g_Model.rot.y) * 0.5f;
	}

	g_Model.rot.y += sinf(g_Model.PurposeRot.y - g_Model.rot.y) * 0.5f;

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//�ʒu������
		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//����������
		g_Model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


		g_Model.PurposeRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	}
	
}

//-----------------------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------------------
void DrawModel(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;		
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.rot.y, g_Model.rot.x, g_Model.rot.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Model.pos.x, g_Model.pos.y, g_Model.pos.z);

	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_NumMatModel; nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		
		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, NULL);

		//���f����(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}
	
	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);

}

//���f���̏��擾
Model *GetModel(void)
{
	return &g_Model;
}