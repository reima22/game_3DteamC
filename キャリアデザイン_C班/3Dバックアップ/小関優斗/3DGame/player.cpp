//-----------------------------------------------------------------------------
//
// ���f���`��̏���
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "player.h"
#include "input.h"
#include "camera.h"
#include "Bullet.h"
#include "shadow.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define MOVE_MODEL_SPEED (1.0f)
#define MODEL_ROT_SPEED (0.2f)
#define MODEL_ROT_SPEED2 (0.5f)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
Player g_Player;
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxPlayer; //���f���̍ŏ��l �ő�l
LPDIRECT3DTEXTURE9 g_aTexturePlayer = NULL;	//�e�N�X�`����
int nCntBullet;
bool g_Key;

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------

//���[�J���ϐ�
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�t�@�C���ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/00_body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].nNumMat, &g_Player.aModel[0].pMesh);
	D3DXLoadMeshFromX("data/MODEL/01_head.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].nNumMat, &g_Player.aModel[1].pMesh);
	D3DXLoadMeshFromX("data/MODEL/02_armR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].nNumMat, &g_Player.aModel[2].pMesh);
	D3DXLoadMeshFromX("data/MODEL/03_armR2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].nNumMat, &g_Player.aModel[3].pMesh);
	D3DXLoadMeshFromX("data/MODEL/04_handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].nNumMat, &g_Player.aModel[4].pMesh);
	D3DXLoadMeshFromX("data/MODEL/05_armL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].nNumMat, &g_Player.aModel[5].pMesh);
	D3DXLoadMeshFromX("data/MODEL/06_armL2.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].nNumMat, &g_Player.aModel[6].pMesh);
	D3DXLoadMeshFromX("data/MODEL/07_handL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].nNumMat, &g_Player.aModel[7].pMesh);
	D3DXLoadMeshFromX("data/MODEL/08_legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].nNumMat, &g_Player.aModel[8].pMesh);
	D3DXLoadMeshFromX("data/MODEL/09_shinR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].nNumMat, &g_Player.aModel[9].pMesh);
	D3DXLoadMeshFromX("data/MODEL/10_footR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].nNumMat, &g_Player.aModel[10].pMesh);
	D3DXLoadMeshFromX("data/MODEL/11_legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].nNumMat, &g_Player.aModel[11].pMesh);
	D3DXLoadMeshFromX("data/MODEL/12_shinL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].nNumMat, &g_Player.aModel[12].pMesh);
	D3DXLoadMeshFromX("data/MODEL/13_footL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].nNumMat, &g_Player.aModel[13].pMesh);

	//g_Player.nNumModel = 13;

	D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^
	int nNumVtx;		//���_��
	DWORD sizeFVF;		//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^

	g_vtxMinPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMaxPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//�}�e���A�����ɑ΂���|�C���^�擾
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{

		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		//���_�o�b�t�@�����b�N
		g_Player.aModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntMat = 0; nCntMat < g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			nNumVtx = g_Player.aModel[nCntModel].pMesh->GetNumVertices();

			//���_�t�H�[�}�b�g�̃T�C�Y���擾
			sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[nCntModel].pMesh->GetFVF());

			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				//�t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				D3DXCreateTextureFromFile(pDevice, NULL, &g_aTexturePlayer);
			}
		}

		//���_�o�b�t�@���A�����b�N
		g_Player.aModel[nCntModel].pMesh->UnlockVertexBuffer();
	}

	//for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	//{
	//	D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//���_���W�̑��

	//												//���_�̍ŏ��l�@�ő�l�𔲂��o��
	//	if (g_vtxMinPlayer.x > vtx.x)
	//	{
	//		g_vtxMinPlayer.x = vtx.x;
	//	}
	//	if (g_vtxMaxPlayer.x < vtx.x)
	//	{
	//		g_vtxMaxPlayer.x = vtx.x;
	//	}

	//	if (g_vtxMinPlayer.y > vtx.y)
	//	{
	//		g_vtxMinPlayer.y = vtx.y;
	//	}
	//	if (g_vtxMaxPlayer.y < vtx.y)
	//	{
	//		g_vtxMaxPlayer.y = vtx.y;
	//	}

	//	if (g_vtxMinPlayer.z > vtx.z)
	//	{
	//		g_vtxMinPlayer.z = vtx.z;
	//	}
	//	if (g_vtxMaxPlayer.z < vtx.z)
	//	{
	//		g_vtxMaxPlayer.z = vtx.z;
	//	}

	//	pVtxBuff += sizeFVF;	//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^�T�C�Y��i�߂�
	//}

	//�e���f���̃C���f�b�N�X�ݒ�

	//��
	g_Player.aModel[0].nIdxModelParent = -1;					//�e(�Ȃ�)
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 16.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//��
	g_Player.aModel[1].nIdxModelParent = 0;						//�e(��)
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����


	//�E�r
	g_Player.aModel[2].nIdxModelParent = 0;						//�e(��)
	g_Player.aModel[2].pos = D3DXVECTOR3(-7.0f, 10.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//�E�r�Q
	g_Player.aModel[3].nIdxModelParent = 2;						//�e(�E�r)
	g_Player.aModel[3].pos = D3DXVECTOR3(-6.6f, 0.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//�E��
	g_Player.aModel[4].nIdxModelParent = 3;						//�e(�E�r�Q)
	g_Player.aModel[4].pos = D3DXVECTOR3(-7.0f, 0.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//���r
	g_Player.aModel[5].nIdxModelParent = 0;						//�e(��)
	g_Player.aModel[5].pos = D3DXVECTOR3(7.0f, 10.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//���r�Q
	g_Player.aModel[6].nIdxModelParent = 5;						//�e(���r)
	g_Player.aModel[6].pos = D3DXVECTOR3(6.6f, 0.0f, 0.0f);		//�I�t�Z�b�g
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//����
	g_Player.aModel[7].nIdxModelParent = 6;						//�e(���r�Q)
	g_Player.aModel[7].pos = D3DXVECTOR3(7.0f, 0.0f, 0.0f);		//�I�t�Z�b�g
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//�E��
	g_Player.aModel[8].nIdxModelParent = 0;						//�e(��)
	g_Player.aModel[8].pos = D3DXVECTOR3(-3.0f, 0.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����



	//�E��
	g_Player.aModel[9].nIdxModelParent = 8;						//�e(�E��)
	g_Player.aModel[9].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����

	//�E��
	g_Player.aModel[10].nIdxModelParent = 9;					//�e(�E��)
	g_Player.aModel[10].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	//����
	g_Player.aModel[11].nIdxModelParent = 0;					//�e(��)
	g_Player.aModel[11].pos = D3DXVECTOR3(3.0f, 0.0f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	//����
	g_Player.aModel[12].nIdxModelParent = 11;					//�e(�E��)
	g_Player.aModel[12].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//�I�t�Z�b�g
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	//����
	g_Player.aModel[13].nIdxModelParent = 12;					//�e(�E��)
	g_Player.aModel[13].pos = D3DXVECTOR3(0.0f, -6.4f, 0.0f);	//�I�t�Z�b�g	
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����

	//�ʒu������
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//����������
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	nCntBullet = 0;

	g_Key = false;

	return S_OK;
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		//���b�V���̔j��
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
	//�e�N�X�`���̊J��
	if (g_aTexturePlayer != NULL)
	{
		g_aTexturePlayer->Release();
		g_aTexturePlayer = NULL;
	}
}

//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{

	Camera *pCamera;
	pCamera = GetCamera();

	//���f���ړ��E
	if (GetKeyboardPress(DIK_D) == true)
	{
		if (g_Key == false)
		{
			g_Player.rotDest.y = pCamera->rot.y - (D3DX_PI / 2);
			g_Player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}

	}

	//���f���ړ���						 
	if (GetKeyboardPress(DIK_A) == true)
	{
		if (g_Key == false)
		{
			g_Player.rotDest.y = pCamera->rot.y + (D3DX_PI / 2);
			g_Player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
	}

	//���f���ړ���						 
	if (GetKeyboardPress(DIK_W) == true)
	{
		//���f���ړ��E��
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y - ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//���f���ړ�����						 
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y + ((D3DX_PI / 4) + (D3DX_PI / 2));
			g_Player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Player.rotDest.y = pCamera->rot.y + D3DX_PI;
		}
		g_Player.move.x += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Player.move.z += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;

		g_Key = true;
	}

	//���f���ړ���O						
	if (GetKeyboardPress(DIK_S) == true)
	{

		//���f���ړ��E��O
		if (GetKeyboardPress(DIK_D) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y - (D3DX_PI / 4);
			g_Player.move.x += cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		//���f���ړ�����O					 
		else if (GetKeyboardPress(DIK_A) == true)
		{
			g_Player.rotDest.y = pCamera->rot.y + (D3DX_PI / 4);
			g_Player.move.x -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
			g_Player.move.z += sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		}
		else
		{
			g_Player.rotDest.y = pCamera->rot.y;
		}
		g_Player.move.x -= sinf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Player.move.z -= cosf(pCamera->rot.y) * MOVE_MODEL_SPEED;
		g_Key = true;
	}

	if (GetKeyboardRelease(DIK_S) == true || GetKeyboardRelease(DIK_W) == true)
	{
		g_Key = false;
	}

	//���f���E��]
	if (GetKeyboardPress(DIK_RSHIFT) == true)
	{
		g_Player.rotDest.y += D3DX_PI / 18;
	}

	//���f������]
	if (GetKeyboardPress(DIK_LSHIFT) == true)
	{
		g_Player.rotDest.y -= D3DX_PI / 18;
	}

	/*if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
	g_Model.move.y = 24;
	}*/

	//�e�̔���
	if (GetKeyboardPress(DIK_K) == true)
	{
		nCntBullet++;
		if ((nCntBullet % 1) == 0)
		{
			SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + 20, g_Player.pos.z), D3DXVECTOR3(-sinf(g_Player.rot.y), 0.0f, -cosf(g_Player.rot.y)), 100);
		}
	}

	if (g_Player.rotDest.y - g_Player.rot.y > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.rotDest.y - g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}

	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;
	g_Player.move.x += (0 - g_Player.move.x) * 0.2f;
	g_Player.move.z += (0 - g_Player.move.z) * 0.2f;

	//g_Model.move.y -= 1.7f;

	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	//if (g_Model.pos.y <= 0)
	//{
	//	g_Model.move.y = 0;
	//	g_Model.pos.y = 0;
	//}

	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.rot.y < -D3DX_PI)
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//�ʒu������
		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ړ��ʏ�����
		g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�ړI�̌���
		g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	SetPositionShadow(-1, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));

	//���[�V�����̏���
	if (g_Player.MotionType == MOTIONTYPE_NUTRAL)
	{
		g_Player.bLoopMotion = true;

		g_Player.aMotionInfo[0].aKeyInfo[0].Frame = 40;

		if ((g_Player.nCounterMotion % g_Player.aMotionInfo[0].aKeyInfo[0].Frame) == 0)
		{
			g_Player.nKey++;
		}
		if (g_Player.nKey == 0)
		{
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosX = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosZ = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotX = -0.03;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotZ = 0.0;
		}

		if (g_Player.nKey == 1)
		{
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosX = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].PosZ = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotX = -0.03;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotY = 0.0;
			g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].RotZ = 0.0;
		}



	}

}

//-----------------------------------------------------------------------------
//�`�揈��
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);

	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel; //�p�[�c�p�v�Z�p�}�g���b�N�X
		D3DXMATRIX mtxParent;
		//�e�p�[�c�̃��[���h�}�g���b�N�X
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		//�������f
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);

		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);

		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//�e�p�[�c�̐e�}�g���b�N�X�̐ݒ�
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_Player.mtxWorld;
		}

		//�Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X��ݒ�
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		//�e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);


		//�}�e���A���ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			//�}�e���A���ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���ݒ�
			pDevice->SetTexture(0, g_aTexturePlayer);
		
			//���f����(�p�[�c)�̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
	
}

Player *GetPlayer(void)
{
	return &g_Player;
}