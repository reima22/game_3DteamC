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
#include "bullet.h"
#include "effect.h"

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
LPDIRECT3DTEXTURE9 g_pTextureModel[5] = {};			//�e�N�X�`��
DWORD  g_nNumMatModel = 0;							//�}�e���A���̐�
MODEL g_Model;
D3DXMATRIX g_mtxWorldModel;							//���[���h�}�g���b�N�X
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

	g_Model.MinModel = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);

	g_Model.MaxModel = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);

	//model�ǂݍ���
	//D3DXLoadMeshFromX("data/MODEL/airplane000.x",D3DXMESH_SYSTEMMEM,pDevice,NULL,&g_pBuffMetModel,NULL,&g_nNumMatModel,&g_pMeshModel);
	//D3DXLoadMeshFromX("data/model/��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetModel, NULL, &g_nNumMatModel, &g_pMeshModel);
	D3DXLoadMeshFromX("data/model/�W��.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMetModel, NULL, &g_nNumMatModel, &g_pMeshModel);

	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^ 

	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	//���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)g_pBuffMetModel->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���ǂݍ���
			D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/50.png", &g_pTextureModel[0]);
		}
	}

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (g_Model.MinModel.x > vtx.x)
		{	
			g_Model.MinModel.x = vtx.x;
		}	
			
		if (g_Model.MaxModel.x < vtx.x)
		{	
			g_Model.MaxModel.x = vtx.x;
		}

		if (g_Model.MinModel.y > vtx.y)
		{	
			g_Model.MinModel.y = vtx.y;
		}	

		if (g_Model.MaxModel.y < vtx.y)
		{	
			g_Model.MaxModel.y = vtx.y;
		}	

		if (g_Model.MinModel.z > vtx.z)
		{	
			g_Model.MinModel.z = vtx.z;
		}	

		if (g_Model.MaxModel.z < vtx.z)
		{	
			g_Model.MaxModel.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y����i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();

	//�ʒu
	g_Model.pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);

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
	//if (GetKeyboardPress(DIK_LEFT) == true)
	if (GetKeyboardPress(DIK_A) == true)
	{
		g_Model.move.x += 0.5f*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5f*sinf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI * 2 / 4);

		//��ړ�
		//if (GetKeyboardPress(DIK_UP) == true)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_Model.move.x += 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z -= 0.5f*cosf(D3DX_PI + pCamera->Camera);

			
			g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI * 3 / 4);
		}

		//���ړ�
		//if (GetKeyboardPress(DIK_DOWN) == true)
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_Model.move.x -= 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z += 0.5f*cosf(D3DX_PI + pCamera->Camera);

			g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI * 1 / 4);
		}
	}

	//�E�ړ�
	//else if (GetKeyboardPress(DIK_RIGHT) == true)
	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_Model.move.x -= 0.5f*cosf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5f*sinf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera - (D3DX_PI * 2 / 4);

		//��ړ�
		//if (GetKeyboardPress(DIK_UP) == true)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_Model.move.x += 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z -= 0.5f*cosf(D3DX_PI + pCamera->Camera);

			g_Model.rotDest.y = -pCamera->Camera - (D3DX_PI * 3 / 4);
		}

		//���ړ�
		//if (GetKeyboardPress(DIK_DOWN) == true)
		if (GetKeyboardPress(DIK_S) == true)
		{
			g_Model.move.x -= 0.5f*sinf(D3DX_PI + pCamera->Camera);
			g_Model.move.z += 0.5f*cosf(D3DX_PI + pCamera->Camera);

			g_Model.rotDest.y = -pCamera->Camera - (D3DX_PI * 1 / 4);
		}
	}

	//��ړ�
	//else if (GetKeyboardPress(DIK_UP) == true)
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_Model.move.x += 0.5f*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z -= 0.5f*cosf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera + (D3DX_PI);
	}

	//���ړ�
	//else if (GetKeyboardPress(DIK_DOWN) == true)
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_Model.move.x -= 0.5f*sinf(D3DX_PI + pCamera->Camera);
		g_Model.move.z += 0.5f*cosf(D3DX_PI + pCamera->Camera);

		g_Model.rotDest.y = -pCamera->Camera;
	}

	//���f������]
	if (GetKeyboardPress(DIK_M) == true)
	{
		g_modelrot -= 0.1f;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}

	//���f���E��]
	if (GetKeyboardPress(DIK_N) == true)
	{
		g_modelrot += 0.1f;
		g_Model.rot = D3DXVECTOR3(0.0f, g_modelrot, 0.0f);
	}
	
	int nEffct;
	nEffct = rand() % 4;

	if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_D) == true|| GetKeyboardPress(DIK_W) == true || GetKeyboardPress(DIK_S) == true)
	{
		if (nEffct == 1)
		{
			SetEffect(g_Model.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20, 1);
		}
	}

	//�e�̔���
	if (GetKeyboardTrigger(DIK_B) == true)
	{
		SetBullet(D3DXVECTOR3(g_Model.pos.x, g_Model.pos.y + 10, g_Model.pos.z), D3DXVECTOR3(sinf(g_Model.rot.y), 0.0f, cosf(g_Model.rot.y)), 5, 500);
		
	}

	//��]���Z�b�g
	if (g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rot.y += D3DX_PI * 2.0f;
	}

	if (g_Model.rot.y > D3DX_PI)
	{
		g_Model.rot.y -= D3DX_PI * 2.0f;
	}
	
	// �ړI�̉�]�p�̏��
	if (g_Model.rotDest.y - g_Model.rot.y < -D3DX_PI)
	{
		g_Model.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_Model.rotDest.y - g_Model.rot.y > D3DX_PI)
	{
		g_Model.rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	g_Model.rot.y += (g_Model.rotDest.y - g_Model.rot.y) * 0.1f;

	

	//�ړ��ʂ̌���
	g_Model.move.x -= (0 + g_Model.move.x) * 0.2f;
	g_Model.move.y -= (0 + g_Model.move.y) * 0.2f;
	g_Model.move.z -= (0 + g_Model.move.z) * 0.2f;

	//�ړ��ʂ̌���
	g_Model.rotmove.x -= (0 + g_Model.rotmove.x) * 0.2f;
	g_Model.rotmove.y -= (0 + g_Model.rotmove.y) * 0.2f;
	g_Model.rotmove.z -= (0 + g_Model.rotmove.z) * 0.2f;

	//�ʒu�X�V
	g_Model.pos.x += g_Model.move.x;
	g_Model.pos.y += g_Model.move.y;
	g_Model.pos.z += g_Model.move.z;

	//�ʒu�X�V
	g_Model.rot.x += g_Model.rotmove.x;
	g_Model.rot.y += g_Model.rotmove.y;
	g_Model.rot.z += g_Model.rotmove.z;

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
		pDevice->SetTexture(0, g_pTextureModel[nCntMat]);

		//���f���p�[�c�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//---------------------------------------------
//�f�[�^�̎󂯓n��
//---------------------------------------------
MODEL *GetModel(void)
{
	return &g_Model;
}