//==============================================================================
//
// ���C�g�̐ݒ�klight.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "light.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
//D3DLIGHT9 g_light;
D3DLIGHT9 g_aLight[3];

//==============================================================================
// ����������
//==============================================================================
void InitLight(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	D3DXVECTOR3 vecDir;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		// ���C�g���N���A����
		ZeroMemory(&g_aLight[nCnt], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		g_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		g_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���C�g�̕�����ݒ�
		if (nCnt == 0)
		{
			vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
		}
		else if (nCnt == 1)
		{
			vecDir = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
		}
		else if (nCnt == 2)
		{
			vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		}
		D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
		g_aLight[nCnt].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &g_aLight[nCnt]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}



	//// ���C�g���N���A����
	//ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//// ���C�g�̎�ނ�ݒ�
	//g_light.Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g�̊g�U����ݒ�
	//g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ���C�g�̕�����ݒ�
	//vecDir = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	//g_light.Direction = vecDir;

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(0, &g_light);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(0, TRUE);


	//// ���C�g���N���A����
	//ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//// ���C�g�̎�ނ�ݒ�
	//g_light.Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g�̊g�U����ݒ�
	//g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ���C�g�̕�����ݒ�
	//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	//g_light.Direction = vecDir;

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(0, &g_light);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(0, TRUE);

	//// ���C�g���N���A����
	//ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//// ���C�g�̎�ނ�ݒ�
	//g_light.Type = D3DLIGHT_DIRECTIONAL;

	//// ���C�g�̊g�U����ݒ�
	//g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// ���C�g�̕�����ݒ�
	//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	//D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	//g_light.Direction = vecDir;

	//// ���C�g��ݒ肷��
	//pDevice->SetLight(0, &g_light);

	//// ���C�g��L���ɂ���
	//pDevice->LightEnable(0, TRUE);
}

//==============================================================================
// �I������
//==============================================================================
void UninitLight(void)
{

}

//==============================================================================
// �X�V����
//==============================================================================
void UpdateLight(void)
{

}