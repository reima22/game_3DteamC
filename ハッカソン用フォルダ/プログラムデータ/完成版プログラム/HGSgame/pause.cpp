//==============================================================================
//
// �|�[�Y���j���[�̕`��kpause.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "pause.h"
#include "input.h"
#include "sound.h"
#include "gamepad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define PAUSE_POLYGON	(5)			// �|�[�Y��ʂ̎g�p����|���S����
#define PAUSETEXT		(3)			// �|�[�Y��ʂ̑I������
#define PAUSE_WINDOWX	(160)		// �|�[�Y���j���[�̕�
#define PAUSE_WINDOWY	(160)		// �|�[�Y���j���[�̍���
#define PAUSE_SIZEX		(140)		// �|�[�Y�e�L�X�g�̕�
#define PAUSE_SIZEY		(40)		// �|�[�Y�e�L�X�g�̍���
#define PAUSETEXT_POSY	(260)		// �|�[�Y�e�L�X�g1�s�ڂ̍���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSE_POLYGON] = {};	// �|�[�Y�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;			// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posBackScreen;							// �|�[�Y�w�i�̈ʒu
D3DXVECTOR3 g_posWindow;								// �|�[�Y�E�B���h�E�̈ʒu
D3DXVECTOR3 g_posText[PAUSETEXT];						// �|�[�Y�e�L�X�g�̈ʒu
float g_fContinue;										// �R���e�j���[�e�L�X�g�̃e�N�X�`���ʒu
float g_fRetry;											// ���g���C�e�L�X�g�̃e�N�X�`���ʒu
float g_fQuit;											// ��蒼���e�L�X�g�̃e�N�X�`���ʒu
PAUSE_MENU PauseMenu;									// �|�[�Y�̏��

//==============================================================================
// �|�[�Y���j���[�̏���������
//==============================================================================
HRESULT InitPause(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/pause_BS.png",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/continue.png",
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/retry.png",
		&g_pTexturePause[2]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/quit.png",
		&g_pTexturePause[3]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * 5,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	g_fContinue = 0.0f;
	g_fRetry = 0.5f;
	g_fQuit = 0.5f;

	PauseMenu = PAUSE_MENU_CONTINUE;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// ���[�U�[�C���^�[�t�F�[�X�̒��S���W
	g_posBackScreen = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(g_posBackScreen.x - (SCREEN_WIDTH / 2), g_posBackScreen.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posBackScreen.x - (SCREEN_WIDTH / 2), g_posBackScreen.y - (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posBackScreen.x + (SCREEN_WIDTH / 2), g_posBackScreen.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posBackScreen.x + (SCREEN_WIDTH / 2), g_posBackScreen.y - (SCREEN_HEIGHT / 2), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// ���[�U�[�C���^�[�t�F�[�X�̒��S���W
	g_posWindow = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	// �|���S���̊e���_���W
	pVtx[4].pos = D3DXVECTOR3(g_posWindow.x - PAUSE_WINDOWX, g_posWindow.y + PAUSE_WINDOWY, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posWindow.x - PAUSE_WINDOWX, g_posWindow.y - PAUSE_WINDOWY, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posWindow.x + PAUSE_WINDOWX, g_posWindow.y + PAUSE_WINDOWY, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_posWindow.x + PAUSE_WINDOWX, g_posWindow.y - PAUSE_WINDOWY, 0.0f);

	// rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[5].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[6].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[7].tex = D3DXVECTOR2(1.0, 0.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 3; nCnt++, pVtx += 4)
	{
		// ���[�U�[�C���^�[�t�F�[�X�̒��S���W
		g_posText[nCnt] = D3DXVECTOR3(SCREEN_WIDTH / 2, PAUSETEXT_POSY + (nCnt * 100.0f), 0.0f);

		// �|���S���̊e���_���W
		pVtx[8].pos = D3DXVECTOR3(g_posText[nCnt].x - PAUSE_SIZEX, g_posText[nCnt].y + PAUSE_SIZEY, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posText[nCnt].x - PAUSE_SIZEX, g_posText[nCnt].y - PAUSE_SIZEY, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posText[nCnt].x + PAUSE_SIZEX, g_posText[nCnt].y + PAUSE_SIZEY, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posText[nCnt].x + PAUSE_SIZEX, g_posText[nCnt].y - PAUSE_SIZEY, 0.0f);

		// rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_���W�̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0, 0.5);
		pVtx[9].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[10].tex = D3DXVECTOR2(1.0, 0.5);
		pVtx[11].tex = D3DXVECTOR2(1.0, 0.0);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//==============================================================================
// �|�[�Y���j���[�̏I������
//==============================================================================
void UninitPause(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < PAUSE_POLYGON; nCnt++)
	{
		if (g_pTexturePause[nCnt] != NULL)
		{
			g_pTexturePause[nCnt]->Release();
			g_pTexturePause[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �|�[�Y���j���[�̍X�V����
//==============================================================================
void UpdatePause(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// �|�[�Y����Q�[�����s
	if (GetKeyboardTrigger(KEYINFO_PAUSE) == true || IsButtonDown(KEYINFO::KEYINFO_PAUSE) == true)
	{
		if (PauseMenu != PAUSE_MENU_CONTINUE)
		{
			PauseMenu = PAUSE_MENU_CONTINUE;
		}
	}

	// �I�����
	if (GetKeyboardTrigger(KEYINFO_DOWN) == true || IsButtonDown(KEYINFO::KEYINFO_DOWN) == true)
	{
		// ���̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);

		if (PauseMenu == PAUSE_MENU_CONTINUE)
		{ // �J�[�\�����uCONTINUE�v�̎�
			PauseMenu = PAUSE_MENU_RETRY;
		}
		else if (PauseMenu == PAUSE_MENU_RETRY)
		{ // �J�[�\�����uRETRY�v�̎�
			PauseMenu = PAUSE_MENU_QUIT;
		}
		else if (PauseMenu == PAUSE_MENU_QUIT)
		{ // �J�[�\�����uQUIT�v�̎�
			PauseMenu = PAUSE_MENU_CONTINUE;
		}
	}
	else if (GetKeyboardTrigger(KEYINFO_UP) == true || IsButtonDown(KEYINFO::KEYINFO_UP) == true)
	{
		// ���̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);

		if (PauseMenu == PAUSE_MENU_CONTINUE)
		{ // �J�[�\�����uCONTINUE�v�̎�
			PauseMenu = PAUSE_MENU_QUIT;
		}
		else if (PauseMenu == PAUSE_MENU_RETRY)
		{ // �J�[�\�����uRETRY�v�̎�
			PauseMenu = PAUSE_MENU_CONTINUE;
		}
		else if (PauseMenu == PAUSE_MENU_QUIT)
		{ // �J�[�\�����uQUIT�v�̎�
			PauseMenu = PAUSE_MENU_RETRY;
		}
	}

	// �e�N�X�`���̐؂�ւ�
	switch (PauseMenu)
	{
	case PAUSE_MENU_CONTINUE:	// �J�[�\�����uCONTINUE�v�̎�
		g_fContinue = 0.0f;
		g_fRetry = 0.5f;
		g_fQuit = 0.5f;
		break;

	case PAUSE_MENU_RETRY:		// �J�[�\�����uRETRY�v�̎�
		g_fContinue = 0.5f;
		g_fRetry = 0.0f;
		g_fQuit = 0.5f;
		break;

	case PAUSE_MENU_QUIT:		// �J�[�\�����uQUIT�v�̎�
		g_fContinue = 0.5f;
		g_fRetry = 0.5f;
		g_fQuit = 0.0f;
		break;

	default:
		break;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// �e�e�N�X�`���̍X�V
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.5f + g_fContinue);
	pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f + g_fContinue);
	pVtx[10].tex = D3DXVECTOR2(1.0f, 0.5f + g_fContinue);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 0.0f + g_fContinue);

	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.5f + g_fRetry);
	pVtx[13].tex = D3DXVECTOR2(0.0f, 0.0f + g_fRetry);
	pVtx[14].tex = D3DXVECTOR2(1.0f, 0.5f + g_fRetry);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f + g_fRetry);

	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.5f + g_fQuit);
	pVtx[17].tex = D3DXVECTOR2(0.0f, 0.0f + g_fQuit);
	pVtx[18].tex = D3DXVECTOR2(1.0f, 0.5f + g_fQuit);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f + g_fQuit);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//==============================================================================
// �|�[�Y���j���[�̕`�揈��
//==============================================================================
void DrawPause(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffPause,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (nCnt == 0)
		{ // �w�i�Ó]�̃e�N�X�`��
			pDevice->SetTexture(0, NULL);
		}
		else
		{ // �|�[�Y���j���[�̃e�N�X�`��
			pDevice->SetTexture(0, g_pTexturePause[nCnt - 1]);
		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}

//==============================================================================
// �|�[�Y�̏��擾
//==============================================================================
PAUSE_MENU GetPause(void)
{
	return PauseMenu;
}