//==============================================================================
//
// �|�[�Y���j���[�̕`��kpause.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "pause.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "gamepad.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSE_POLYGON] = {};	// �|�[�Y�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;			// �o�b�t�@�ւ̃|�C���^
PAUSE Pause;											// �|�[�Y�̍\����

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

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/pause_BS.png",
		&g_pTexturePause[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/continue_logo.png",
		&g_pTexturePause[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/retry_logo.png",
		&g_pTexturePause[2]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/option_logo.png",
		&g_pTexturePause[3]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/quit_logo.png",
		&g_pTexturePause[4]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/option.jpg",
		&g_pTexturePause[5]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * PAUSE_POLYGON,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	Pause.fContinue = 0.0f;
	Pause.fRetry = 0.5f;
	Pause.fOption = 0.5f;
	Pause.fQuit = 0.5f;
	Pause.colOption = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	Pause.bOption = false;
	Pause.PauseMenu = PAUSE_MENU_CONTINUE;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// �����߂̒��S���W
	Pause.posBackScreen = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);

	// �����ߔw�i�̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(Pause.posBackScreen.x - SCREEN_CENTERX, Pause.posBackScreen.y + SCREEN_CENTERY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pause.posBackScreen.x - SCREEN_CENTERX, Pause.posBackScreen.y - SCREEN_CENTERY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pause.posBackScreen.x + SCREEN_CENTERX, Pause.posBackScreen.y + SCREEN_CENTERY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pause.posBackScreen.x + SCREEN_CENTERX, Pause.posBackScreen.y - SCREEN_CENTERY, 0.0f);

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

	// �|�[�Y���j���[�w�i�̒��S���W
	Pause.posWindow = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);

	// �|�[�Y���j���[�w�i�̊e���_���W
	pVtx[4].pos = D3DXVECTOR3(Pause.posWindow.x - PAUSE_WINDOWX, Pause.posWindow.y + PAUSE_WINDOWY, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(Pause.posWindow.x - PAUSE_WINDOWX, Pause.posWindow.y - PAUSE_WINDOWY, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(Pause.posWindow.x + PAUSE_WINDOWX, Pause.posWindow.y + PAUSE_WINDOWY, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(Pause.posWindow.x + PAUSE_WINDOWX, Pause.posWindow.y - PAUSE_WINDOWY, 0.0f);

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

	for (int nCnt = 0; nCnt < 4; nCnt++, pVtx += 4)
	{
		// �|�[�Y���j���[�̒��S���W
		Pause.posText[nCnt] = D3DXVECTOR3(SCREEN_WIDTH / 2, PAUSETEXT_POSY + (nCnt * 90.0f), 0.0f);

		// �|�[�Y���j���[�̊e���_���W
		pVtx[8].pos = D3DXVECTOR3(Pause.posText[nCnt].x - PAUSE_SIZEX, Pause.posText[nCnt].y + PAUSE_SIZEY, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(Pause.posText[nCnt].x - PAUSE_SIZEX, Pause.posText[nCnt].y - PAUSE_SIZEY, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(Pause.posText[nCnt].x + PAUSE_SIZEX, Pause.posText[nCnt].y + PAUSE_SIZEY, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(Pause.posText[nCnt].x + PAUSE_SIZEX, Pause.posText[nCnt].y - PAUSE_SIZEY, 0.0f);

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


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// �u�����т����v�\���̒��S���W
	Pause.posBackScreen = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	// �u�����т����v�\���̊e���_���W
	pVtx[24].pos = D3DXVECTOR3(Pause.posBackScreen.x - (SCREEN_WIDTH / 2), Pause.posBackScreen.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[25].pos = D3DXVECTOR3(Pause.posBackScreen.x - (SCREEN_WIDTH / 2), Pause.posBackScreen.y - (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[26].pos = D3DXVECTOR3(Pause.posBackScreen.x + (SCREEN_WIDTH / 2), Pause.posBackScreen.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[27].pos = D3DXVECTOR3(Pause.posBackScreen.x + (SCREEN_WIDTH / 2), Pause.posBackScreen.y - (SCREEN_HEIGHT / 2), 0.0f);

	// rhw�̐ݒ�
	pVtx[24].rhw = 1.0f;
	pVtx[25].rhw = 1.0f;
	pVtx[26].rhw = 1.0f;
	pVtx[27].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[24].col = Pause.colOption;
	pVtx[25].col = Pause.colOption;
	pVtx[26].col = Pause.colOption;
	pVtx[27].col = Pause.colOption;

	// ���_���W�̐ݒ�
	pVtx[24].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[25].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[26].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[27].tex = D3DXVECTOR2(1.0, 0.0);

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
	FADE fade = GetFade();

	// �|�[�Y����Q�[�����s
	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(KEYINFO_PAUSE) == true || IsButtonDown(KEYINFO::KEYINFO_PAUSE) == true)
		{
			if (Pause.PauseMenu != PAUSE_MENU_CONTINUE && Pause.colOption.a <= 0.0f)
			{
				Pause.PauseMenu = PAUSE_MENU_CONTINUE;
				Pause.bOption = false;
				Pause.colOption.a = 0.0f;
			}
		}
	}

	// �u�����т����v�̕\��
	if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
	{
		if (Pause.PauseMenu == PAUSE_MENU_OPTION && Pause.colOption.a <= 0.0f)
		{// �u�����т����v��I��
			Pause.bOption = true;	// �\��������ON
		}	
	}

	if (Pause.bOption == true)
	{// �t�F�[�h�C������
		if (Pause.colOption.a < 1.0f)
		{
			Pause.colOption.a += 0.05f;
		}
		else if (Pause.colOption.a >= 1.0f)
		{// �t�F�[�h�A�E�g�ֈڍs
			if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
			{
				Pause.bOption = false;
			}
		}
	}
	else if (Pause.bOption == false)
	{// �t�F�[�h�A�E�g����
		if (Pause.colOption.a > 0.0f)
		{
			Pause.colOption.a -= 0.05f;
		}
	}

	// �I�����
	if (Pause.colOption.a <= 0.0f && fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(KEYINFO_DOWN) == true || IsButtonDown(KEYINFO::KEYINFO_DOWN) == true)
		{
			// ���̍Đ�
			PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

			if (Pause.PauseMenu == PAUSE_MENU_CONTINUE)
			{ // �J�[�\�����uCONTINUE�v�̎�
				Pause.PauseMenu = PAUSE_MENU_RETRY;
			}
			else if (Pause.PauseMenu == PAUSE_MENU_RETRY)
			{ // �J�[�\�����uRETRY�v�̎�
				Pause.PauseMenu = PAUSE_MENU_OPTION;
			}
			else if (Pause.PauseMenu == PAUSE_MENU_OPTION)
			{ // �J�[�\�����uQUIT�v�̎�
				Pause.PauseMenu = PAUSE_MENU_QUIT;
			}
			else if (Pause.PauseMenu == PAUSE_MENU_QUIT)
			{ // �J�[�\�����uQUIT�v�̎�
				Pause.PauseMenu = PAUSE_MENU_CONTINUE;
			}
		}
		else if (GetKeyboardTrigger(KEYINFO_UP) == true || IsButtonDown(KEYINFO::KEYINFO_UP) == true)
		{
			// ���̍Đ�
			PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

			if (Pause.PauseMenu == PAUSE_MENU_CONTINUE)
			{ // �J�[�\�����uCONTINUE�v�̎�
				Pause.PauseMenu = PAUSE_MENU_QUIT;
			}
			else if (Pause.PauseMenu == PAUSE_MENU_RETRY)
			{ // �J�[�\�����uRETRY�v�̎�
				Pause.PauseMenu = PAUSE_MENU_CONTINUE;
			}
			else if (Pause.PauseMenu == PAUSE_MENU_OPTION)
			{ // �J�[�\�����uQUIT�v�̎�
				Pause.PauseMenu = PAUSE_MENU_RETRY;
			}
			else if (Pause.PauseMenu == PAUSE_MENU_QUIT)
			{ // �J�[�\�����uQUIT�v�̎�
				Pause.PauseMenu = PAUSE_MENU_OPTION;
			}
		}
	}

	// �e�N�X�`���̐؂�ւ�
	switch (Pause.PauseMenu)
	{
	case PAUSE_MENU_CONTINUE:	// �J�[�\�����uCONTINUE�v�̎�
		Pause.fContinue = 0.0f;
		Pause.fRetry = 0.5f;
		Pause.fOption = 0.5f;
		Pause.fQuit = 0.5f;
		break;

	case PAUSE_MENU_RETRY:		// �J�[�\�����uRETRY�v�̎�
		Pause.fContinue = 0.5f;
		Pause.fRetry = 0.0f;
		Pause.fOption = 0.5f;
		Pause.fQuit = 0.5f;
		break;

	case PAUSE_MENU_OPTION:		// �J�[�\�����uOPTION�v�̎�
		Pause.fContinue = 0.5f;
		Pause.fRetry = 0.5f;
		Pause.fOption = 0.0f;
		Pause.fQuit = 0.5f;
		break;

	case PAUSE_MENU_QUIT:		// �J�[�\�����uQUIT�v�̎�
		Pause.fContinue = 0.5f;
		Pause.fRetry = 0.5f;
		Pause.fOption = 0.5f;
		Pause.fQuit = 0.0f;
		break;

	default:
		break;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// �e�e�N�X�`���̍X�V
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.5f + Pause.fContinue);
	pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f + Pause.fContinue);
	pVtx[10].tex = D3DXVECTOR2(1.0f, 0.5f + Pause.fContinue);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 0.0f + Pause.fContinue);

	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.5f + Pause.fRetry);
	pVtx[13].tex = D3DXVECTOR2(0.0f, 0.0f + Pause.fRetry);
	pVtx[14].tex = D3DXVECTOR2(1.0f, 0.5f + Pause.fRetry);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 0.0f + Pause.fRetry);

	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.5f + Pause.fOption);
	pVtx[17].tex = D3DXVECTOR2(0.0f, 0.0f + Pause.fOption);
	pVtx[18].tex = D3DXVECTOR2(1.0f, 0.5f + Pause.fOption);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 0.0f + Pause.fOption);

	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.5f + Pause.fQuit);
	pVtx[21].tex = D3DXVECTOR2(0.0f, 0.0f + Pause.fQuit);
	pVtx[22].tex = D3DXVECTOR2(1.0f, 0.5f + Pause.fQuit);
	pVtx[23].tex = D3DXVECTOR2(1.0f, 0.0f + Pause.fQuit);

	pVtx[24].col = Pause.colOption;
	pVtx[25].col = Pause.colOption;
	pVtx[26].col = Pause.colOption;
	pVtx[27].col = Pause.colOption;

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
	for (int nCnt = 0; nCnt < 7; nCnt++)
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
PAUSE GetPause(void)
{
	return Pause;
}