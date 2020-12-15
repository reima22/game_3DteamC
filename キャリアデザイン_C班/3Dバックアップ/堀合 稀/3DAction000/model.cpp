//==============================================================================
//
// 3D���f���̕`��kmodel.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "math.h"

// �}�N����`
#define MODEL_MOVE	(1.0f)
#define MODEL_TURN	(0.1f)

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPD3DXMESH g_pMeshModel = NULL;			// ���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;	// �}�e���A��(�ގ����)�ւ̃|�C���^
DWORD g_nNumMatModel = 0;				// �}�e���A���̐�
Model model;
//D3DXVECTOR3 g_posModel;				// �ʒu
//D3DXVECTOR3 g_rotModel;				// ����
//D3DXMATRIX g_mtxWorldModel;			// ���[���h�}�g���b�N�X
//D3DXVECTOR3 g_moveModelX;				// X���̈ړ���
//D3DXVECTOR3 g_moveModelZ;				// Z���̈ړ���
int g_nIdx;

//==============================================================================
// ����������
//==============================================================================
HRESULT InitModel(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		"data/MODEL/01_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_nNumMatModel,
		&g_pMeshModel);

	// �ϐ��̏�����
	model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �e�̐ݒ�
	model.nIdx = SetShadow(D3DXVECTOR3(model.pos.x,0.0f,model.pos.z), 10.0f, 10.0f);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void UninitModel(void)
{
	// ���b�V���̔j��
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	// �}�e���A���̔j��
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateModel(void)
{
	// �J�����̎擾
	Camera camera = GetCamera();
	double dSqrt = sqrt(2);		// 2�̕�����

	// �ʒu�̃��Z�b�g
	if (GetKeyboardTrigger(KEYINFO_OK) == true)
	{
		model.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		model.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		model.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		model.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �e�̔���
	if (GetKeyboardPress(KEYINFO_SHOT) == true)
	{
		SetBullet(
			D3DXVECTOR3(model.pos.x, model.pos.y + 7.0f, model.pos.z),
			D3DXVECTOR3(sinf(D3DX_PI - model.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - model.rot.y) * 5.0f),
			100);
	}

	// �ړ��ʂ̉��Z
	model.pos += model.move;

	// �e�̒Ǐ]
	SetPositionShadow(model.nIdx,D3DXVECTOR3(model.pos.x,0.0f,model.pos.z));

	// ���f���̈ړ�
	if (GetKeyboardPress(KEYINFO_BACK_MODEL) == true)
	{
		if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
		{// �������
			model.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * MODEL_MOVE;
			model.move.z += sinf(camera.rot.y + D3DX_PI / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
			//model.rotDest.y += (camera.rot.y + (D3DX_PI * 3 / 4) - model.rot.y) * MODEL_TURN;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
		{// �E�����
			model.move.x += cosf(camera.rot.y - D3DX_PI / 4) * MODEL_MOVE;
			model.move.z -= sinf(camera.rot.y - D3DX_PI / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y - (D3DX_PI * 3 / 4);
			//model.rotDest.y += (camera.rot.y - (D3DX_PI * 3 / 4) - model.rot.y) * MODEL_TURN;
		}
		else
		{// �����
			model.move.x += sinf(camera.rot.y) * MODEL_MOVE;
			model.move.z += cosf(camera.rot.y) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + D3DX_PI;
			//if (model.rot.y <= D3DX_PI && model.rot.y >= 0.0f && model.rot.y != D3DX_PI &&model.rot.y != -D3DX_PI)
			//{
			//	model.rotDest.y += (camera.rot.y + D3DX_PI) * MODEL_TURN;
			//}
			//if (model.rot.y >= -D3DX_PI && model.rot.y < 0.0f && model.rot.y != D3DX_PI &&model.rot.y != -D3DX_PI)
			//{
			//	model.rotDest.y -= (camera.rot.y + D3DX_PI) * MODEL_TURN;
			//}
		}
	}
	else if (GetKeyboardPress(KEYINFO_FORE_MODEL) == true)
	{
		if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
		{// ��������
			model.move.x += cosf(D3DX_PI + camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.move.z -= sinf(D3DX_PI + camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + D3DX_PI / 4;
			//model.rotDest.y += (camera.rot.y + D3DX_PI / 4 - model.rot.y) * MODEL_TURN;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
		{// �E������
			model.move.x -= cosf(D3DX_PI - camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.move.z += sinf(D3DX_PI - camera.rot.y * 3 / 4) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y + D3DX_PI / -4;
			//model.rotDest.y += (camera.rot.y + D3DX_PI / -4 - model.rot.y) * MODEL_TURN;
		}
		else
		{// ������
			model.move.x += sinf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
			model.move.z += cosf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
			model.rotDest.y = camera.rot.y;
			//model.rotDest.y += (camera.rot.y - model.rot.y) * 0.1f;
		}
		//model.moveZ.x = sinf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//model.moveZ.z = cosf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//model.rot.y = camera.rot.y;
		//if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
		//{
		//	model.moveX.x = cosf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//	model.moveX.z = sinf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
		//	model.rot.y = camera.rot.y + D3DX_PI / 4;
		//	//model.moveX.x /= dSqrt;
		//	//model.moveX.z /= dSqrt;
		//	//model.moveZ.x /= dSqrt;
		//	//model.moveZ.z /= dSqrt;
		//}
		//else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
		//{
		//	model.moveX.x = cosf(-camera.rot.y) * MODEL_MOVE;
		//	model.moveX.z = sinf(-camera.rot.y) * MODEL_MOVE;
		//	model.rot.y = camera.rot.y + D3DX_PI / -4;
		//	//model.moveX.x /= dSqrt;
		//	//model.moveX.z /= dSqrt;
		//	//model.moveZ.x /= dSqrt;
		//	//model.moveZ.z /= dSqrt;
		//}
	}
	else if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
	{// ������
		model.move.x -= cosf(camera.rot.y) * MODEL_MOVE;
		model.move.z += sinf(camera.rot.y) * MODEL_MOVE;
		model.rotDest.y = camera.rot.y + (D3DX_PI / 2);
		//model.rotDest.y += (camera.rot.y + (D3DX_PI / 2) - model.rot.y) * MODEL_TURN;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
	{// �E����
		model.move.x += cosf(camera.rot.y) * MODEL_MOVE;
		model.move.z -= sinf(camera.rot.y) * MODEL_MOVE;
		model.rotDest.y = camera.rot.y + (D3DX_PI / -2);
		//if (model.rot.y < D3DX_PI && model.rot.y > D3DX_PI / 2)
		//{
		//	model.rotDest.y -= (camera.rot.y + (D3DX_PI / -2) - model.rot.y) * MODEL_TURN;

		//}
		//else
		//{
		//	model.rotDest.y += (camera.rot.y + (D3DX_PI / -2) - model.rot.y) * MODEL_TURN;
		//}
		
	}

	// ���f���̏㏸�E���~
	if (GetKeyboardPress(KEYINFO_UP_MODEL) == true)
	{
		model.move.y = 2;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_MODEL) == true)
	{
		model.move.y = -2;
	}
	else
	{
		model.move.y = 0;
	}

	// ���f���̐���
	if (GetKeyboardPress(KEYINFO_TURN_LEFT_MODEL) == true)
	{
		model.rotDest.y += D3DX_PI / 18;
	}
	if (GetKeyboardPress(KEYINFO_TURN_RIGHT_MODEL) == true)
	{
		model.rotDest.y -= D3DX_PI / 18;
	}

	// �ړI�̉�]�p�̏��
	if (model.rotDest.y - model.rot.y < -D3DX_PI)
	{
		model.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (model.rotDest.y - model.rot.y > D3DX_PI)
	{
		model.rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	model.rot.y += (model.rotDest.y - model.rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (model.rot.y < -D3DX_PI)
	{
		model.rot.y += D3DX_PI * 2.0f;
	}
	else if (model.rot.y > D3DX_PI)
	{
		model.rot.y -= D3DX_PI * 2.0f;
	}

	// ������̌�������
	model.move.x += (0.0f - model.move.x) * SPEEDDOWN;
	model.move.z += (0.0f - model.move.z) * SPEEDDOWN;
}

//==============================================================================
// �`�揈��
//==============================================================================
void DrawModel(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&model.mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, model.rot.y, model.rot.x, model.rot.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, model.pos.x, model.pos.y, model.pos.z);
	D3DXMatrixMultiply(&model.mtxWorld, &model.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &model.mtxWorld);

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_mtxWorldModel);

	//// �����̔��f
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	//D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

// ���f���̎擾
Model *GetModel(void)
{
	return &model;
}