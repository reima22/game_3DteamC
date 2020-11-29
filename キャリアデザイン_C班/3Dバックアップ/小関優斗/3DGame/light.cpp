//-----------------------------------------------------------------------------
//
// ���C�g�̏���
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "light.h"

//�}�N����`
#define MAX_LIGHT (3)

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
D3DLIGHT9 g_light[MAX_LIGHT];

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//�f�o�C�X�|�C���^
	D3DXVECTOR3 VecDir[MAX_LIGHT];			//�ݒ�p�����x�N�g��

	//�f�o�C�X�擾
	pDevice = GetDevice();
	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		//���C�g���N���A����
		ZeroMemory(&g_light[nCount], sizeof(D3DLIGHT9));
	}

	//���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 0.65f);
	g_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 0.15f);

	//���C�g�̕�����ݒ�
	VecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	VecDir[1] = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	VecDir[2] = D3DXVECTOR3(0.9f, -0.1f, 0.4f);

	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		D3DXVec3Normalize(&VecDir[nCount], &VecDir[nCount]);	//���K��
		g_light[nCount].Direction = VecDir[nCount];
		//���C�g�̐ݒ�
		pDevice->SetLight(nCount, &g_light[nCount]);
		//���C�g��L��������
		pDevice->LightEnable(nCount, TRUE);
	}

	
}

//-----------------------------------------------------------------------------
//�I������
//-----------------------------------------------------------------------------
void UninitLight(void)
{

}

//-----------------------------------------------------------------------------
//�X�V����
//-----------------------------------------------------------------------------
void UpdateLight(void)
{

}