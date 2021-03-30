//==============================================================================
//
// �Q�[���J�n�����̕`��kstart.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "start.h"
#include "fade.h"
#include "sound.h"

// �}�N����`
#define START_POLY	(4)

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureStart[START_POLY] = {};			// �X�R�A�e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStart = NULL;		// �X�R�A�o�b�t�@�ւ̃|�C���^
Start start[START_POLY];
int g_nStartCnt;
//int g_nTimeCnt;

//==============================================================================
// �X�R�A�̏���������
//==============================================================================
HRESULT InitStart(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	//int nStage = GetStage();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/three.png",
		&g_pTextureStart[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/two.png",
		&g_pTextureStart[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/one.png",
		&g_pTextureStart[2]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/go.png",
		&g_pTextureStart[3]);

	// ���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * START_POLY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStart,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	g_nStartCnt = 0;
	//g_nTimeCnt = 3;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < START_POLY; nCnt++)
	{
		start[nCnt].pos = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);
		start[nCnt].bUse = false;

		//�X�R�A�̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(start[nCnt].pos.x - 60.0f, start[nCnt].pos.y + 60.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(start[nCnt].pos.x - 60.0f, start[nCnt].pos.y - 60.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(start[nCnt].pos.x + 60.0f, start[nCnt].pos.y + 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(start[nCnt].pos.x + 60.0f, start[nCnt].pos.y - 60.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;	// ���_�|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStart->Unlock();

	return S_OK;
}

//==============================================================================
// �X�R�A�̏I������
//==============================================================================
void UninitStart(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffStart != NULL)
	{
		g_pVtxBuffStart->Release();
		g_pVtxBuffStart = NULL;
	}

	for (int nCnt = 0; nCnt < START_POLY; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureStart[nCnt] != NULL)
		{
			g_pTextureStart[nCnt]->Release();
			g_pTextureStart[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �X�R�A�̍X�V����
//==============================================================================
void UpdateStart(void)
{
	// ���[�J���ϐ��錾
	FADE fade = GetFade();

	if (fade == FADE_NONE)
	{
		if (g_nStartCnt < 240)
		{
			g_nStartCnt++;
		}

		if (g_nStartCnt == 1)
		{
			start[0].bUse = true;
			start[1].bUse = false;
			start[2].bUse = false;
			start[3].bUse = false;
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
		}
		else if (g_nStartCnt == 60)
		{
			start[0].bUse = false;
			start[1].bUse = true;
			start[2].bUse = false;
			start[3].bUse = false;
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
		}
		else if (g_nStartCnt == 120)
		{
			start[0].bUse = false;
			start[1].bUse = false;
			start[2].bUse = true;
			start[3].bUse = false;
			PlaySound(SOUND_LABEL_SE_COUNTDOWN);
		}
		else if (g_nStartCnt == 180)
		{
			start[0].bUse = false;
			start[1].bUse = false;
			start[2].bUse = false;
			start[3].bUse = true;
			PlaySound(SOUND_LABEL_SE_GAMESTART);
		}
		else if (g_nStartCnt == 240)
		{
			start[3].bUse = false;
		}
	}
}

//==============================================================================
// �X�R�A�̕`�揈��
//==============================================================================
void DrawStart(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	//Select *pSelect = GetSelect();

	// �ϐ��̎󂯓n��
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStart, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntTexture = 0; nCntTexture < START_POLY; nCntTexture++)
	{
		pDevice->SetTexture(0, g_pTextureStart[nCntTexture]);

		if (start[nCntTexture].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,
				nCntTexture * 4,
				2);
		}
	}
}

int GetCount(void)
{
	return g_nStartCnt;
}