//==============================================================================
//
// �^�C�g����ʂ̕`��ktitle.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "gamepad.h"
//#include "xpad.h"
#include "xinput.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define TITLE_TEX			(3)		// �^�C�g���̃e�N�X�`����
#define TITLE_POLYGON		(4)		// �^�C�g����ʂ̃|���S����
#define SIGN_POLYGON		(2)		// �G���^�[�T�C���̕�����
#define TITLE_LOGOX			(640)	// �^�C�g�����S��X���W
#define TITLE_FIRST_LOGOY	(-50)	// �^�C�g�����S�̍ŏ���Y���W
#define TITLE_LAST_LOGOY	(200)	// �^�C�g�����S�̍ŏIY���W
#define TITLE_LOGO_SIZEX	(480)	// �^�C�g�����S�̕�
#define TITLE_LOGO_SIZEY	(80)	// �^�C�g�����S�̍���
#define TITLE_ENTER_POSY	(510)	// �G���^�[�T�C����Y���̈ʒu
#define TITLE_ENTER_SIZEX	(480)	// �G���^�[�T�C���̕�
#define TITLE_ENTER_SIZEY	(80)	// �G���^�[�T�C���̍���
#define MOVESIGN			(20)	// �G���^�[�T�C���̈ړ���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_TEX] = {};		// �^�C�g����ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;			// �o�b�t�@�ւ̃|�C���^
TITLE title;

//==============================================================================
// �^�C�g����ʂ̏���������
//==============================================================================
HRESULT InitTitle(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/title_bg.jpg",
		&g_pTextureTitle[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/title000.png",
		&g_pTextureTitle[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/press_enter.png",
		&g_pTextureTitle[2]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * TITLE_POLYGON,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,							// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̏�����
	title.Sign = ENTERSIGN_NONE;
	title.colSign = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	title.titleauto = TITLE_NONE;
	title.nCntMoveLogo = 0;
	title.nShiftCount = 0;
	title.nSignCounter = 0;
	title.nSignAppear = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �^�C�g�����(�w�i)�̒��S���W
	title.posTitle = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(title.posTitle.x - SCREEN_CENTERX, title.posTitle.y + SCREEN_CENTERY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(title.posTitle.x - SCREEN_CENTERX, title.posTitle.y - SCREEN_CENTERY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(title.posTitle.x + SCREEN_CENTERX, title.posTitle.y + SCREEN_CENTERY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(title.posTitle.x + SCREEN_CENTERX, title.posTitle.y - SCREEN_CENTERY, 0.0f);

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

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �^�C�g����ʂ̒��S���W
	title.posTitlelogo = D3DXVECTOR3(TITLE_LOGOX, TITLE_FIRST_LOGOY, 0.0f);

	// �|���S���̊e���_���W
	pVtx[4].pos = D3DXVECTOR3(title.posTitlelogo.x - TITLE_LOGO_SIZEX, title.posTitlelogo.y + TITLE_LOGO_SIZEY, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(title.posTitlelogo.x - TITLE_LOGO_SIZEX, title.posTitlelogo.y - TITLE_LOGO_SIZEY, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(title.posTitlelogo.x + TITLE_LOGO_SIZEX, title.posTitlelogo.y + TITLE_LOGO_SIZEY, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(title.posTitlelogo.x + TITLE_LOGO_SIZEX, title.posTitlelogo.y - TITLE_LOGO_SIZEY, 0.0f);

	// rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_���W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[5].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[6].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[7].tex = D3DXVECTOR2(1.0, 0.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < SIGN_POLYGON; nCnt++,pVtx += 4)
	{
		// �G���^�[�T�C���̒��S���W
		title.posTitleEnter[nCnt] = D3DXVECTOR3(-TITLE_ENTER_SIZEX + ((float)nCnt * (SCREEN_WIDTH + (TITLE_ENTER_SIZEX * 2))), TITLE_ENTER_POSY + ((float)nCnt *TITLE_ENTER_SIZEY), 0.0f);

		// �|���S���̊e���_���W
		pVtx[8].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x - TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y + TITLE_ENTER_SIZEY / 2, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x - TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y - TITLE_ENTER_SIZEY / 2, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x + TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y + TITLE_ENTER_SIZEY / 2, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x + TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y - TITLE_ENTER_SIZEY / 2, 0.0f);

		// rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[8].col = title.colSign;
		pVtx[9].col = title.colSign;
		pVtx[10].col = title.colSign;
		pVtx[11].col = title.colSign;

		// ���_���W�̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.5f + nCnt * 0.5f);
		pVtx[9].tex = D3DXVECTOR2(0.0f, nCnt * 0.5f);
		pVtx[10].tex = D3DXVECTOR2(1.0f, 0.5f + nCnt * 0.5f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, nCnt * 0.5f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

	// BGM�̍Đ�
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//==============================================================================
// �^�C�g����ʂ̏I������
//==============================================================================
void UninitTitle(void)
{
	// �T�E���h�̒�~����
	StopSound();

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < TITLE_TEX; nCnt++)
	{
		if (g_pTextureTitle[nCnt] != NULL)
		{
			g_pTextureTitle[nCnt]->Release();
			g_pTextureTitle[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �^�C�g����ʂ̍X�V����
//==============================================================================
void UpdateTitle(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	FADE fade;
	//XINPUT_STATE state;
	//XInputGetState(0, &state);
	// �t�F�[�h�̎擾
	fade = GetFade();

	// �^�C�g�����S�̈ړ�
	if (title.posTitlelogo.y != TITLE_LAST_LOGOY)
	{
		title.nCntMoveLogo++;
		if (title.nCntMoveLogo % 2 == 0)
		{
			title.posTitlelogo.y += 2;
			if (title.posTitlelogo.y >= TITLE_LAST_LOGOY)
			{
				title.posTitlelogo.y = TITLE_LAST_LOGOY;
			}
		}
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̊e���_���W
	pVtx[4].pos = D3DXVECTOR3(title.posTitlelogo.x - TITLE_LOGO_SIZEX, title.posTitlelogo.y + TITLE_LOGO_SIZEY, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(title.posTitlelogo.x - TITLE_LOGO_SIZEX, title.posTitlelogo.y - TITLE_LOGO_SIZEY, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(title.posTitlelogo.x + TITLE_LOGO_SIZEX, title.posTitlelogo.y + TITLE_LOGO_SIZEY, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(title.posTitlelogo.x + TITLE_LOGO_SIZEX, title.posTitlelogo.y - TITLE_LOGO_SIZEY, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();


	if (title.posTitlelogo.y != TITLE_LAST_LOGOY)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true) 
			//|| /*state.Gamepad.wButtons & XINPUT_GAMEPAD_A*/ XinputPress(XINPUT_GAMEPAD_A) == true)
		{
			title.posTitlelogo.y = TITLE_LAST_LOGOY - 1;
		}
	}

	if (title.Sign == ENTERSIGN_NORMAL)
	{
		if (fade != FADE_OUT)
		{
			title.nShiftCount++;	// ������ʑJ�ڃJ�E���^�[�̑���
		}
		
		if (title.nShiftCount >= 300)
		{ // �����J�ڎ��s
		  // �t�F�[�h�A�E�g
			SetFade(FADE_OUT, MODE_RANKING);
			title.titleauto = TITLE_AUTO;
		}
	}

	// �G���^�[�L�[���͂ŃQ�[����ʂ֑J��
	if (title.Sign == ENTERSIGN_NORMAL && title.nShiftCount < 300)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true /*|| state.Gamepad.wButtons & XINPUT_GAMEPAD_A*/)
		{
			if (title.Sign != ENTERSIGN_ACTIVE)
			{
				// �T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_START000);
			}

			// �t�F�[�h�A�E�g
			SetFade(FADE_OUT, MODE_TUTORIAL);

			// �G���^�[�T�C���̏�ԕω�
			title.Sign = ENTERSIGN_ACTIVE;
		}
	}

	// �G���^�[�T�C���̏��
	EnterSign();
}

//==============================================================================
// �^�C�g����ʂ̕`�揈��
//==============================================================================
void DrawTitle(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffTitle,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCnt = 0; nCnt < TITLE_POLYGON; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		if (nCnt == 3)
		{
			pDevice->SetTexture(0, g_pTextureTitle[2]);
		}
		else
		{
			pDevice->SetTexture(0, g_pTextureTitle[nCnt]);
		}

		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}

//==============================================================================
// �����J�ڏ��̎擾
//==============================================================================
TITLE GetTitle(void)
{
	return title;
}

//==============================================================================
// �G���^�[�T�C���̕\�����
//==============================================================================
void EnterSign(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	//XINPUT_STATE state;
	//XInputGetState(0, &state);
	// �G���^�[�T�C���̏��
	switch (title.Sign)
	{
	case ENTERSIGN_NORMAL:	// �T�C���̓_��
		title.nSignCounter++;	// �G���^�[�T�C���J�E���^�[�̑���
		if (title.nSignCounter % 60 == 0)
		{
			title.colSign.a = 0.0f;	// �����x0��
		}
		else if (title.nSignCounter % 30 == 0 && title.nSignCounter % 60 != 0)
		{
			title.colSign.a = 1.0f;	// �����x�ő��
		}

		break;

	case ENTERSIGN_NONE:
		// �ړ���Ԃւ̈ڍs
		if (title.posTitlelogo.y == TITLE_LAST_LOGOY)
		{
			title.nSignAppear++;	// �G���^�[�T�C���o���J�E���g�̑���

			if (title.nSignAppear >= 30 || GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
			{
				title.Sign = ENTERSIGN_MOVE;
			}
		}

		break;

	case ENTERSIGN_ACTIVE:
		title.nSignCounter++;	// �G���^�[�T�C���J�E���^�[�̑���
		if (title.nSignCounter % 4 == 0)
		{
			title.colSign.a = 0.0f;	// �����x0��
		}
		else if (title.nSignCounter % 2 == 0 && title.nSignCounter % 4 != 0)
		{
			title.colSign.a = 1.0f	;// �����x�ő��
		}

		break;

	case ENTERSIGN_MOVE:	// �T�C���̃A�j���[�V����
		// ��ʍ��[����T�C���̏㔼�����o��
		if (title.posTitleEnter[0].x != SCREEN_CENTERX)
		{
			title.posTitleEnter[0].x += MOVESIGN;
			if (title.posTitleEnter[0].x >= SCREEN_CENTERX)
			{
				title.posTitleEnter[0].x = SCREEN_CENTERX;
			}
		}

		// ��ʉE�[����T�C���̉��������o��
		if (title.posTitleEnter[1].x != SCREEN_CENTERX)
		{
			title.posTitleEnter[1].x -= MOVESIGN;
			if (title.posTitleEnter[1].x <= SCREEN_CENTERX)
			{
				title.posTitleEnter[1].x = SCREEN_CENTERX;
			}
		}

		// �{�^�����͂ŒZ�k
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true/* || state.Gamepad.wButtons & XINPUT_GAMEPAD_A*/)
		{
			for (int nCnt = 0; nCnt < SIGN_POLYGON; nCnt++)
			{
				title.posTitleEnter[nCnt].x = SCREEN_CENTERX;
			}
		}

		// �ʏ��Ԃֈڍs
		if (title.posTitleEnter[0].x == SCREEN_CENTERX)
		{
			title.Sign = ENTERSIGN_NORMAL;
		}

		break;

	default:
		break;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < SIGN_POLYGON; nCnt++, pVtx += 4)
	{
		// �|���S���̊e���_���W
		pVtx[8].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x - TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y + TITLE_ENTER_SIZEY / 2, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x - TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y - TITLE_ENTER_SIZEY / 2, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x + TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y + TITLE_ENTER_SIZEY / 2, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(title.posTitleEnter[nCnt].x + TITLE_ENTER_SIZEX, title.posTitleEnter[nCnt].y - TITLE_ENTER_SIZEY / 2, 0.0f);

		// �e���_�J���[�̍X�V
		pVtx[8].col = title.colSign;
		pVtx[9].col = title.colSign;
		pVtx[10].col = title.colSign;
		pVtx[11].col = title.colSign;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}