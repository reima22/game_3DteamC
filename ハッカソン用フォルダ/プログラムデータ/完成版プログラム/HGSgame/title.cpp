//-----------------------------------------------------------------------------
//
// �^�C�g����ʂ̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "gamepad.h"
//#include "Effect.h"
#include "sound.h"

//�}�N����`
#define MAX_TITLE_TEX (3)				//�^�C�g���̉摜�̐�
#define MAX_TITLE (3)					//�^�C�g���|���S����
#define TITLE_BG_SIZE_X (640)			//�^�C�g����ʂ̉���
#define TITLE_BG_SIZE_Y (360)			//�^�C�g����ʂ̗���
#define GAME_TITLE_SIZE_X (700)			//�^�C�g���̉���
#define GAME_TITLE_SIZE_Y (100)			//�^�C�g���̗���
#define ENTER_SIZE_X (400)				//�v���X�G���^�[�̉���
#define ENTER_SIZE_Y (75)				//�v���X�G���^�[�̗���
#define MOVE_SIZE_TITLE_X (7)			//�^�C�g���̈ړ����x
#define MOVE_SIZE_TITLE_Y (1)			//�^�C�g���̈ړ����x

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_���
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE_TEX] = {};	//�e�N�X�`��
TITLE g_aTitle[MAX_TITLE];
int g_nCounterTitle = 30;
int g_FadeCounter;
int g_nCounterT;
bool g_bEnter;
int g_TitleFadeCounter;
TITLEAUTO titleauto;
int g_nShiftCnt;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	//�T�E���h�X�^�[�g
	//PlaySound(SOUND_LABEL_BGM001);

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title.png", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gametitle.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pressenter.png", &g_pTextureTitle[2]);

	titleauto = TITLE_NONE;
	g_TitleFadeCounter = 0;
	g_bEnter = false;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aTitle[nCntTitle].bDisp = true;	
		
	}	

	g_aTitle[1].size.x = 0.0f;
	g_aTitle[1].size.y = 0.0f;

	//�e�N�X�`���ݒ�
	g_aTitle[0].TexType = 0;
	g_aTitle[1].TexType = 1;
	g_aTitle[2].TexType = 2;

	g_FadeCounter = 0;
	g_nCounterTitle = 30;
	g_nShiftCnt = 0;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{

		SetVertexTitle(nCntTitle);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx[0].col = g_aTitle[nCntTitle].col;
		pVtx[1].col = g_aTitle[nCntTitle].col;
		pVtx[2].col = g_aTitle[nCntTitle].col;
		pVtx[3].col = g_aTitle[nCntTitle].col;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTitle->Unlock();
	}

	// BGM�̍Đ�
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	// �T�E���h�̒�~����
	StopSound();

	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE_TEX; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	FADE fade;
	fade = GetFade();

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	VERTEX_2D *pVtx;

	g_nCounterT++;		//�\���J�E���^�[
	g_nShiftCnt++;		// �����J�ڃJ�E���^�[

	if (g_aTitle[1].size.y < 100 || g_aTitle[1].size.x < 700)
	{
		g_aTitle[1].size.x += MOVE_SIZE_TITLE_X;
		g_aTitle[1].size.y += MOVE_SIZE_TITLE_Y;

	}

	if (g_nShiftCnt >= 600)// ��10�b
	{ // �����J�ڎ��s
	  // �t�F�[�h�A�E�g
		SetFade(FADE_OUT, MODE_RANKING);
		titleauto = TITLE_AUTO;
	}

	if ((g_nCounterT % g_nCounterTitle) == 0)
	{
		g_aTitle[2].bDisp = g_aTitle[2].bDisp ? false : true;	//�v���X�G���^�[�̓_��
	}

	if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_SHOT) == true && fade == FADE_NONE)
	{

		if (g_aTitle[1].size.y < 100 || g_aTitle[1].size.x < 700)
		{
			g_aTitle[1].size.x = GAME_TITLE_SIZE_X;
			g_aTitle[1].size.y = GAME_TITLE_SIZE_Y;
		}

		else if (g_aTitle[1].size.y >= 100 && g_aTitle[1].size.x >= 700 && g_bEnter == false)
		{
			g_nCounterTitle -= 25;

			PlaySound(SOUND_LABEL_SE_START000);

			g_bEnter = true;
		}
	}

	if (g_bEnter == true)
	{
		if ((g_nCounterT % 2) == 0)
		{

			g_FadeCounter++;
		}
	}
	if (g_FadeCounter == 30)
	{
		//SetFade(FADE_OUT, MODE_GAME);

		SetFade(FADE_OUT, MODE_TUTORIAL);
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[1].pos.x - g_aTitle[1].size.x, g_aTitle[1].pos.y + g_aTitle[1].size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitle[1].pos.x - g_aTitle[1].size.x, g_aTitle[1].pos.y - g_aTitle[1].size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitle[1].pos.x + g_aTitle[1].size.x, g_aTitle[1].pos.y + g_aTitle[1].size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitle[1].pos.x + g_aTitle[1].size.x, g_aTitle[1].pos.y - g_aTitle[1].size.y, 0.0f);

	//���_�o�b�t�@�A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[g_aTitle[nCntTitle].TexType]);

		if (g_aTitle[nCntTitle].bDisp == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// �^�C�g���̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------

void SetVertexTitle(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	pVtx += nIdx * 4;

	
	if (nIdx == 0)
	{//�w�i
	

		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		g_aTitle[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	}
	else if (nIdx == 1)
	{//�^�C�g��
		g_aTitle[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 350, 0);
		
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - g_aTitle[1].size.x, g_aTitle[nIdx].pos.y + g_aTitle[1].size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - g_aTitle[1].size.x, g_aTitle[nIdx].pos.y - g_aTitle[1].size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + g_aTitle[1].size.x, g_aTitle[nIdx].pos.y + g_aTitle[1].size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + g_aTitle[1].size.x, g_aTitle[nIdx].pos.y - g_aTitle[1].size.y, 0.0f);

		//���_�̃J���[�ݒ�
		g_aTitle[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (nIdx == 2)
	{//�v���X�G���^�[
		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 550.0f, 0.0f);
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		g_aTitle[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

TITLEAUTO GetTitle(void)
{
	return titleauto;
}