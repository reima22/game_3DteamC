//-----------------------------------------------------------------
//
// �v���C���[�̏��� (model.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "object.h"
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
LPD3DXMESH g_pMeshObject = NULL;	//���_���
LPD3DXBUFFER g_pBuffMetObject = NULL;
DWORD  g_nNumMatObject = 0;						//�}�e���A���̐�
OBJECT g_Object;
D3DXMATRIX g_mtxWorldObject;						//���[���h�}�g���b�N�X
float g_objectrot;

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
HRESULT InitObject(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//model�ǂݍ���
	//D3DXLoadMeshFromX("data/model/airplane000.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetObject, NULL, &g_nNumMatObject, &g_pMeshObject);
	D3DXLoadMeshFromX("data/model/��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetObject, NULL, &g_nNumMatObject, &g_pMeshObject);

	//�ʒu
	g_Object.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�̏����ʒu
	//SetShadow(D3DXVECTOR3(g_Object.pos.x, 0.0f, g_Object.pos.z));
	//�e�̏����ʒu
	SetShadow(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//����
	g_Object.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void UninitObject(void)
{
	//�}�e���A���̊J��
	if (g_pBuffMetObject != NULL)
	{
		g_pBuffMetObject->Release();
		g_pBuffMetObject = NULL;
	}

	//���b�V���̊J��
	if (g_pMeshObject != NULL)
	{
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void UpdateObject(void)
{
	SetPositionShadow(1,D3DXVECTOR3(g_Object.pos.x, 0.0f, g_Object.pos.z));
}

//-----------------------------------------------------------------------------
// �|���S���̕`�揈��
//-----------------------------------------------------------------------------
void DrawObject(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldObject);

	//�����̔��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object.rot.y, g_Object.rot.x, g_Object.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxRot);

	//�ʒu�̔��]
	D3DXMatrixTranslation(&mtxTrans, g_Object.pos.x, g_Object.pos.y, g_Object.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldObject, &g_mtxWorldObject, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldObject);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)g_pBuffMetObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatObject; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f���p�[�c�̕`��
		g_pMeshObject->DrawSubset(nCntMat);
	}

	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

OBJECT *GetObject(void)
{
	return &g_Object;
}