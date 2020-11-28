//================================================
//
// �J��������[light.h]
// Author; miura yuudai
//
//================================================

#include "light.h"

//==================
//�O���[�o���ϐ�
//==================
D3DLIGHT9 g_light[3];//���C�g�̏��

//=====================================
//����������
//=====================================
void InitLight(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�ݒ�p�����x�N�g��
	D3DXVECTOR3 VecDir;
	D3DXVECTOR3 VecDir1;
	D3DXVECTOR3 VecDir2;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���C�g���N���A�ɂ���
	ZeroMemory(&g_light[0], sizeof(D3DLIGHT9));
	ZeroMemory(&g_light[1], sizeof(D3DLIGHT9));
	ZeroMemory(&g_light[2], sizeof(D3DLIGHT9));

	//���C�g�̎��
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	VecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	VecDir1 = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	VecDir2 = D3DXVECTOR3(0.2f, -0.8f, -0.4f);

	D3DXVec3Normalize(&VecDir, &VecDir);//���K��
	D3DXVec3Normalize(&VecDir1, &VecDir1);//���K��
	D3DXVec3Normalize(&VecDir2, &VecDir2);//���K��

	g_light[0].Direction = VecDir;
	g_light[1].Direction = VecDir1;
	g_light[2].Direction = VecDir2;

	//���C�g�̐ݒ�
	pDevice->SetLight(0, &g_light[0]);
	pDevice->SetLight(0, &g_light[1]);
	pDevice->SetLight(0, &g_light[2]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);


}

//=====================================
//�I������
//=====================================
void UninitLight(void)
{

}

//=====================================
//�X�V����
//=====================================
void UpdateLight(void)
{

}