//-----------------------------------------------------------------
//
// �v���C���[�̏��� (player.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "light.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
D3DLIGHT9 g_light[3];		//���C�g���

//-----------------------------------------------------------------------------
// �|���S���̏���������
//-----------------------------------------------------------------------------
void Initlight(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	D3DXVECTOR3 vecDir;			//�ݒ�p�����x�N�g��

	pDevice = GetDevice();

	for (int nCntShadow = 0; nCntShadow < MAX_LIGHT; nCntShadow++)
	{
		//���C�g���N���A�ɂ���
		ZeroMemory(&g_light[nCntShadow], sizeof(D3DLIGHT9));

		//���C�g�̎��
		g_light[nCntShadow].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U���̐ݒ�
		g_light[nCntShadow].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//���C�g�̕�����ݒ�
		vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		D3DXVec3Normalize(&vecDir, &vecDir); //���K��
		g_light[nCntShadow].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(0, &g_light[nCntShadow]);


	}

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);

	//���C�g��L���ɂ���
	pDevice->LightEnable(1, TRUE);

	//���C�g��L���ɂ���
	pDevice->LightEnable(3, TRUE);
}

//-----------------------------------------------------------------------------
// �|���S���̏I������
//-----------------------------------------------------------------------------
void Uninitlight(void)
{
}

//-----------------------------------------------------------------------------
// �|���S���̍X�V����
//-----------------------------------------------------------------------------
void Updatelight(void)
{
}

