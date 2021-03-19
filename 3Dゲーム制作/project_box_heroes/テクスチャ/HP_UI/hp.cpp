//-----------------------------------------------------------------
//
// �^�C�g���̏��� (hp.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "hp.h"
#include "input.h"
#include "fade.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAX_UI			(4)									// �ő吔

#define PLAYER_X		(850.0f)							// ���S��
#define PLAYER_Y		(100.0f)							// ���S�̍���

#define PLAYER_BAR_X	(850.0f)							// ���S�̍���
#define PLAYER_BAR_Y	(100.0f)							// ���S�̍���

#define PLAYER2_X		(850.0f)							// ���S��
#define PLAYER2_Y		(100.0f)							// ���S�̍���

#define PLAYER2_BAR_X	(850.0f)							// ���S�̍���
#define PLAYER2_BAR_Y	(100.0f)							// ���S�̍���

//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHp = NULL;
LPDIRECT3DTEXTURE9 g_pTextureHp[MAX_UI] = {};
D3DXVECTOR3 g_posPlayer;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posPlayerBar;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posPlayer2;						// �^�C�g�����S�̒��S���W
D3DXVECTOR3 g_posPlayer2Bar;					// �^�C�g�����S�̒��S���W
int g_PlayerBar = 0;
int g_Player2Bar = 0;


//-----------------------------------------------------------------
// �^�C�g���̏���������
//-----------------------------------------------------------------
HRESULT InitHp(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	g_posPlayer = D3DXVECTOR3(450.0f, 100.0f, 0.0f);
	g_posPlayerBar = D3DXVECTOR3(450.0f, 100.0f, 0.0f);
	g_posPlayer2 = D3DXVECTOR3(SCREEN_WIDTH - 450.0f, 100.0f, 0.0f);
	g_posPlayer2Bar = D3DXVECTOR3(SCREEN_WIDTH - 450.0f, 100.0f, 0.0f);

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP��.png", &g_pTextureHp[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP�� �o�[.png", &g_pTextureHp[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP��.png", &g_pTextureHp[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/HP�� �o�[.png", &g_pTextureHp[3]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_UI, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffHp,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHp = 0; nCntHp < MAX_UI; nCntHp++)
	{
		// ���_���W�̐ݒ�
		//SetVertexHp(nCntHp);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�			
		pVtx[0].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255,255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255,255, 255);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���̍X�V
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHp->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------
// �^�C�g���̏I������
//-----------------------------------------------------------------
void UninitHp(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffHp != NULL)
	{
		g_pVtxBuffHp->Release();
		g_pVtxBuffHp = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		if (g_pTextureHp[nCntTexture] != NULL)
		{
			g_pTextureHp[nCntTexture]->Release();
			g_pTextureHp[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// �^�C�g���̍X�V����
//-----------------------------------------------------------------
void UpdateHp(void)
{
	for (int nCntHp = 0; nCntHp < MAX_UI; nCntHp++)
	{
		// ���_���W�̐ݒ�
		SetVertexHp(nCntHp);
	}


	if (GetKeyboardPress(DIK_I) == true)
	{
		g_PlayerBar += 5;
	}

	if (GetKeyboardPress(DIK_K) == true)
	{
		g_Player2Bar+= 5;
	}
}

//-----------------------------------------------------------------
// �^�C�g���̕`�揈��
//-----------------------------------------------------------------
void DrawHp(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHp, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < MAX_UI; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureHp[nCntTexture]);
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// �^�C�g����ʂɓ\��e�N�X�`���̎w��
//-----------------------------------------------------------------
void SetVertexHp(int nCntHp)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	//��
	if (nCntHp == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(g_posPlayer.x - (PLAYER_X / 2), g_posPlayer.y + (PLAYER_Y / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posPlayer.x - (PLAYER_X / 2), g_posPlayer.y - (PLAYER_Y / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posPlayer.x + (PLAYER_X / 2), g_posPlayer.y + (PLAYER_Y / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posPlayer.x + (PLAYER_X / 2), g_posPlayer.y - (PLAYER_Y / 2), 0.0f);
	}

	//�o�[
	if (nCntHp == 1)
	{
		pVtx[4].pos = D3DXVECTOR3(g_posPlayerBar.x - (PLAYER_BAR_X / 2), g_posPlayerBar.y + (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posPlayerBar.x - (PLAYER_BAR_X / 2), g_posPlayerBar.y - (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posPlayerBar.x + (PLAYER_BAR_X / 2) - (g_PlayerBar), g_posPlayerBar.y + (PLAYER_BAR_Y / 2), 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posPlayerBar.x + (PLAYER_BAR_X / 2) - (g_PlayerBar), g_posPlayerBar.y - (PLAYER_BAR_Y / 2), 0.0f);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f * ((850.0f - g_PlayerBar) / 850.0f), 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f * ((850.0f - g_PlayerBar) / 850.0f), 0.0f);
	}

	//��
	if (nCntHp == 2)
	{
		pVtx[8].pos = D3DXVECTOR3(g_posPlayer2.x - (PLAYER2_X / 2), g_posPlayer2.y + (PLAYER2_Y / 2), 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posPlayer2.x - (PLAYER2_X / 2), g_posPlayer2.y - (PLAYER2_Y / 2), 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posPlayer2.x + (PLAYER2_X / 2), g_posPlayer2.y + (PLAYER2_Y / 2), 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posPlayer2.x + (PLAYER2_X / 2), g_posPlayer2.y - (PLAYER2_Y / 2), 0.0f);
	}

	//�ԃo�[
	if (nCntHp == 3)
	{
		pVtx[12].pos = D3DXVECTOR3(g_posPlayer2Bar.x - (PLAYER2_BAR_X / 2) + (g_Player2Bar), g_posPlayer2Bar.y + (PLAYER2_BAR_Y / 2), 0.0f);
		pVtx[13].pos = D3DXVECTOR3(g_posPlayer2Bar.x - (PLAYER2_BAR_X / 2) + (g_Player2Bar), g_posPlayer2Bar.y - (PLAYER2_BAR_Y / 2), 0.0f);
		pVtx[14].pos = D3DXVECTOR3(g_posPlayer2Bar.x + (PLAYER2_BAR_X / 2), g_posPlayer2Bar.y + (PLAYER2_BAR_Y / 2), 0.0f);
		pVtx[15].pos = D3DXVECTOR3(g_posPlayer2Bar.x + (PLAYER2_BAR_X / 2), g_posPlayer2Bar.y - (PLAYER2_BAR_Y / 2), 0.0f);

		pVtx[12].tex = D3DXVECTOR2(1.0f * ((850.0f - g_Player2Bar) / 850.0f), 1.0f);
		pVtx[13].tex = D3DXVECTOR2(1.0f * ((850.0f - g_Player2Bar) / 850.0f), 0.0f);
		pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[15].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHp->Unlock();
}