//==============================================================================
//
// �`���[�g���A����ʂ̕`��ktutorial.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "tutorial.h"
#include "input.h"
#include "fade.h"
#include "gamepad.h"

// �}�N����`
#define TUTORIAL_NUM	(2)	// �`���[�g���A���̐�

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTutorial[2] = {};		// �`���[�g���A����ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;	// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posTutorial[TUTORIAL_NUM];			// �`���[�g���A����ʂ̈ʒu
D3DXCOLOR col;

//==============================================================================
// �`���[�g���A����ʂ̏���������
//==============================================================================
HRESULT InitTutorial(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/tutorial001.jpg",
		&g_pTextureTutorial[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/tutorial000.jpg",
		&g_pTextureTutorial[1]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * TUTORIAL_NUM,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL)))
	{
		return E_FAIL;
	}

	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < TUTORIAL_NUM; nCnt++,pVtx += 4)
	{
		// ���U���g��ʂ̒��S���W
		g_posTutorial[nCnt] = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);

		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posTutorial[nCnt].x - SCREEN_CENTERX, g_posTutorial[nCnt].y + SCREEN_CENTERY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTutorial[nCnt].x - SCREEN_CENTERX, g_posTutorial[nCnt].y - SCREEN_CENTERY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTutorial[nCnt].x + SCREEN_CENTERX, g_posTutorial[nCnt].y + SCREEN_CENTERY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTutorial[nCnt].x + SCREEN_CENTERX, g_posTutorial[nCnt].y - SCREEN_CENTERY, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();

	return S_OK;
}

//==============================================================================
// �`���[�g���A����ʂ̏I������
//==============================================================================
void UninitTutorial(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < TUTORIAL_NUM; nCnt++)
	{
		if (g_pTextureTutorial[nCnt] != NULL)
		{
			g_pTextureTutorial[nCnt]->Release();
			g_pTextureTutorial[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �`���[�g���A����ʂ̍X�V����
//==============================================================================
void UpdateTutorial(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	FADE fade;

	// �t�F�[�h�̎擾
	fade = GetFade();

	// �`���[�g���A����ʂ̑J��
	if (col.a == 1.0f && fade != FADE_IN)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{
			col.a = 0.0f;
		}
	}
	else if (fade == FADE_NONE && col.a == 0.0f)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{
			SetFade(FADE_OUT, MODE_GAME);
		}
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�J���[�̐ݒ�
	pVtx[4].col = col;
	pVtx[5].col = col;
	pVtx[6].col = col;
	pVtx[7].col = col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

//==============================================================================
// �`���[�g���A����ʂ̕`�揈��
//==============================================================================
void DrawTutorial(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffTutorial,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[nCnt]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}