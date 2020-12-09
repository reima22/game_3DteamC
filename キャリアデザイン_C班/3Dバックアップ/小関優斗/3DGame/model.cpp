//-----------------------------------------------------------------------------
//
// ���f���`��̏���
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "model.h"
#include "input.h"
#include "camera.h"
#include "Bullet.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define MOVE_MODEL_SPEED (1.0f)
#define MODEL_ROT_SPEED (0.2f)
#define MODEL_ROT_SPEED2 (0.5f)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPD3DXMESH g_pMeshModel = NULL;			//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;	//�}�e���A���i�ގ����j�ւ̃|�C���^
DWORD g_NumMatModel = 0;				//�}�e���A���̐�
Model g_Model;							//���f�����
D3DXMATRIX g_mtxWorldModel;				//���[���h�}�g���b�N�X
int nCntBullet;
bool g_Key;

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

	nCntBullet = 0;

	g_Key = false;
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

	//���f���ړ��E
	if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		if (g_Key == false)
		{
			g_Model.rotDest.y = pCamera->rot.y - (D3DX_PI / 2);
			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}

	}

	//���f���ړ���						 
	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		if (g_Key == false)
		{
			g_Model.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
	}

	//���f���ړ���						 
	if (GetKeyboardPress(DIK_UP) == true)
	{
		//���f���ړ��E��
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y - ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//���f���ړ�����						 
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y + ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Model.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
		g_Model.move.x += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.move.z += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;

		g_Key = true;
	}

	//���f���ړ���O						
	if (GetKeyboardPress(DIK_DOWN) == true)
	{
	
		//���f���ړ��E��O
		if (GetKeyboardPress(DIK_RIGHT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y - (D3DX_PI / 4);
			g_Model.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//���f���ړ�����O					 
		else if (GetKeyboardPress(DIK_LEFT) == true)
		{
			g_Model.rotDest.y = pCamera->rot.y + (D3DX_PI / 4);
			g_Model.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Model.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Model.rotDest.y = pCamera->rot.y;
		}
		g_Model.move.x -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Model.move.z -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Key = true;
	}

	if (GetKeyboardRelease(DIK_DOWN) == true || GetKeyboardRelease(DIK_UP) == true)
	{
		g_Key = false;
	}

	//���f���E��]
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_Model.rotDest.y += D3DX_PI / 18;
	}

	//���f������]
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Model.rotDest.y -= D3DX_PI / 18;
	}
	

	if (GetKeyboardPress(DIK_K) == true)
	{
		nCntBullet++;
		if ((nCntBullet % 1) == 0)
		{
			SetBullet(g_Model.pos, D3DXVECTOR3(-sinf(g_Model.rot.y), 0.0f, -cosf(g_Model.rot.y)), 100);
		}
	}

	if (g_Model.rotDest.y - g_Model.rot.y > D3DX_PI)
	{
		g_Model.rotDest.y -= D3DX_PI * 2.0f;
	}
	if (g_Model.rotDest.y - g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rotDest.y += D3DX_PI * 2.0f;
	}

	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.z += g_Model.move.z;
	g_Model.move.x += (0 - g_Model.move.x) * 0.2f;
	g_Model.move.z += (0 - g_Model.move.z) * 0.2f;

	g_Model.rot.y += (g_Model.rotDest.y - g_Model.rot.y) * 0.1f;

	if (g_Model.rot.y > D3DX_PI)
	{
		g_Model.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rot.y += D3DX_PI * 2.0f;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//�ʒu������
		g_Model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ړ��ʏ�����
		g_Model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ړI�̌���
		g_Model.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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