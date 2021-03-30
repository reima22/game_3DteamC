//-----------------------------------------------------------------
//
// HP�o�[�̏��� (hp.cpp)
// Author:shouta takahashi
//
//-----------------------------------------------------------------

//------------------------
//�C���N���[�h�t�@�C��
//------------------------
#include "hp.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "select.h"



//-----------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHp = NULL;
LPDIRECT3DTEXTURE9 g_pTextureHpBlue[MAX_TEX_UI] = {};
LPDIRECT3DTEXTURE9 g_pTextureHpRed[MAX_TEX_UI] = {};
HP g_Hp[PLAYER_MAX];

//-----------------------------------------------------------------
// HP�o�[�̏���������
//-----------------------------------------------------------------
HRESULT InitHp(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_blue_00.png", &g_pTextureHpBlue[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_blue_01.png", &g_pTextureHpBlue[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_blue_02.png", &g_pTextureHpBlue[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_bar_blue.png", &g_pTextureHpBlue[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_red_00.png", &g_pTextureHpRed[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_red_01.png", &g_pTextureHpRed[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_red_02.png", &g_pTextureHpRed[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hp/hp_bar_red.png", &g_pTextureHpRed[3]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TEX_UI, // �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffHp,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	for (int nHp = 0; nHp < PLAYER_MAX; nHp++)
	{
		g_Hp[nHp].posFrame = D3DXVECTOR3(SCREEN_WIDTH / 4.0f, 50.0f, 0.0f);
		g_Hp[nHp].posBar = D3DXVECTOR3(SCREEN_WIDTH / 4.0f, 50.0f, 0.0f);
		if (nHp != 0)
		{
			g_Hp[nHp].posFrame.x *= 3.0f;
			g_Hp[nHp].posBar.x *= 3.0f;
		}
		g_Hp[nHp].fBar = 20.0f;
		g_Hp[nHp].hp = (HP_Player)nHp;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHp = 0; nCntHp < MAX_TEX_UI; nCntHp++)
	{
		// ���_���W�̐ݒ�
		//SetVertexHp(nCntHp);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�			
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
// HP�o�[�̏I������
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
	for (int nCntTexture = 0; nCntTexture < MAX_TEX_UI; nCntTexture++)
	{
		if (g_pTextureHpBlue[nCntTexture] != NULL)
		{
			g_pTextureHpBlue[nCntTexture]->Release();
			g_pTextureHpBlue[nCntTexture] = NULL;
		}

		if (g_pTextureHpRed[nCntTexture] != NULL)
		{
			g_pTextureHpRed[nCntTexture]->Release();
			g_pTextureHpRed[nCntTexture] = NULL;
		}
	}
}

//-----------------------------------------------------------------
// HP�o�[�̍X�V����
//-----------------------------------------------------------------
void UpdateHp(void)
{
	Player *pPlayer = GetPlayer();

	for (int nCntHp = 0; nCntHp < PLAYER_MAX; nCntHp++)
	{
		// ���_���W�̐ݒ�
		SetVertexHp(nCntHp);

		if (GetKeyboardTrigger(KEYINFO_JUMP) == true)
		{
			CalcuHp(0, 5.0f,false);
		}

		if (GetKeyboardTrigger(KEYINFO_CANCEL) == true)
		{
			CalcuHp(0, 5.0f, true);
		}

		if (g_Hp[nCntHp].fBar >= HP_LIMIT)
		{
			pPlayer->state = PLAYERSTATE_CLEAR;
		}
	}
}

//-----------------------------------------------------------------
// HP�o�[�̕`�揈��
//-----------------------------------------------------------------
void DrawHp(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	Select *pSelect = GetSelect();

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHp, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < MAX_TEX_UI; nCntTexture++)
	{
		// �e�N�X�`���̐ݒ�
		switch (nCntTexture)
		{
		case 0:
			if (pSelect->chara[0] == CHARA_0)
			{
				pDevice->SetTexture(0, g_pTextureHpBlue[0]);
			}
			else if (pSelect->chara[0] == CHARA_1)
			{
				pDevice->SetTexture(0, g_pTextureHpBlue[1]);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureHpBlue[2]);
			}
			break;

		case 1:
			pDevice->SetTexture(0, g_pTextureHpBlue[3]);
			break;

		case 2:
			if (pSelect->chara[1] == CHARA_0)
			{
				pDevice->SetTexture(0, g_pTextureHpRed[0]);
			}
			else if (pSelect->chara[1] == CHARA_1)
			{
				pDevice->SetTexture(0, g_pTextureHpRed[1]);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureHpRed[2]);
			}			
			break;

		case 3:
			pDevice->SetTexture(0, g_pTextureHpRed[3]);
			break;

		default:
			break;
		}
		
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTexture * 4, 2);
	}
}

//-----------------------------------------------------------------
// HP�o�[�̒��_���W�X�V
//-----------------------------------------------------------------
void SetVertexHp(int nCntHp)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nCntHp * 4;

	if (nCntHp == 0)
	{// ��
		pVtx[0].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x - UI_HARF_W, g_Hp[nCntHp].posFrame.y + UI_HARF_H, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x - UI_HARF_W, g_Hp[nCntHp].posFrame.y - UI_HARF_H, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x + UI_HARF_W, g_Hp[nCntHp].posFrame.y + UI_HARF_H, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x + UI_HARF_W, g_Hp[nCntHp].posFrame.y - UI_HARF_H, 0.0f);

		pVtx[4].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x - UI_HARF_W, g_Hp[nCntHp].posBar.y + UI_HARF_H, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x - UI_HARF_W, g_Hp[nCntHp].posBar.y - UI_HARF_H, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x + UI_HARF_W - (g_Hp[nCntHp].fBar), g_Hp[nCntHp].posBar.y + UI_HARF_H, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x + UI_HARF_W - (g_Hp[nCntHp].fBar), g_Hp[nCntHp].posBar.y - UI_HARF_H, 0.0f);

		pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f * ((UI_WIDTH - g_Hp[nCntHp].fBar) / UI_WIDTH), 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f * ((UI_WIDTH - g_Hp[nCntHp].fBar) / UI_WIDTH), 0.0f);
	}
	else if (nCntHp == 1)
	{// ��
		pVtx[4].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x - UI_HARF_W, g_Hp[nCntHp].posFrame.y + UI_HARF_H, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x - UI_HARF_W, g_Hp[nCntHp].posFrame.y - UI_HARF_H, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x + UI_HARF_W, g_Hp[nCntHp].posFrame.y + UI_HARF_H, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_Hp[nCntHp].posFrame.x + UI_HARF_W, g_Hp[nCntHp].posFrame.y - UI_HARF_H, 0.0f);

		pVtx[8].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x - UI_HARF_W + (g_Hp[nCntHp].fBar), g_Hp[nCntHp].posBar.y + UI_HARF_H, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x - UI_HARF_W + (g_Hp[nCntHp].fBar), g_Hp[nCntHp].posBar.y - UI_HARF_H, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x + UI_HARF_W, g_Hp[nCntHp].posBar.y + UI_HARF_H, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_Hp[nCntHp].posBar.x + UI_HARF_W, g_Hp[nCntHp].posBar.y - UI_HARF_H, 0.0f);

		pVtx[8].tex = D3DXVECTOR2(1.0f * ((UI_WIDTH - g_Hp[nCntHp].fBar) / UI_WIDTH), 1.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f * ((UI_WIDTH - g_Hp[nCntHp].fBar) / UI_WIDTH), 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHp->Unlock();
}

// �o�[�̌��Z�̍X�V
void CalcuHp(int nHp,float fValue, bool bPlus)
{
	if (bPlus == true)
	{
		g_Hp[nHp].fBar -= fValue;
	}
	else
	{
		g_Hp[nHp].fBar += fValue;
	}
}

HP *GetHp(void)
{
	return &g_Hp[0];
}