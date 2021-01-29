//==============================================================================
//
// �����L���O��ʂ̕`��kranking.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "ranking.h"
#include "title.h"
#include "input.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "gamepad.h"
#include "stdio.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define RANK_NUM			(5)			// �����L���O���ʐ�
#define MAX_POLY			(56)		// �g�p����|���S����
#define RANKINGLOGO_POSX	(640.0f)	// �����L���O���S�̒��SX���W
#define RANKINGLOGO_POSY	(50.0f)		// �����L���O���S�̒��SY���W
#define RANKINGLOGO_SIZEX	(240.0f)	// �����L���O���S�̒��S����̕�
#define RANKINGLOGO_SIZEY	(40.0f)		// �����L���O���S�̒��S����̍���
#define RANKINGRANK_POSX	(320.0f)	// ���ʕ\����X���W�ʒu
#define RANKINGRANK_POSY	(140.0f)	// ���ʕ\����Y���W�ʒu
#define RANKINGRANK_SIZEX	(50.0f)		// ���ʕ\���̕�
#define RANKINGRANK_SIZEY	(30.0f)		// ���ʕ\���̍���
#define RANKING_SCOREX		(550.0f)	// �X�R�A�\����X���W�J�n�ʒu
#define RANKING_SCOREY		(140.0f)	// �X�R�A�\����Y���W�J�n�ʒu
#define RANKING_SCORE_SIZEX	(20.0f)		// �X�R�A�\���̕�
#define RANKING_SCORE_SIZEY	(30.0f)		// �X�R�A�\���̍���
#define RANKING_NOWLOGOX	(320.0f)	// ���݃X�R�A���S
#define RANKING_NOWLOGOY	(600.0f)	// ���݃X�R�A���S
#define RANKING_NOWSCOREX	(550.0f)	// ���݂̃X�R�AX���W
#define RANKING_NOWSCOREY	(600.0f)	// ���݂̃X�R�AY���W

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;			// �����L���O��ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingLogo = NULL;		// �����L���O���S�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingRank = NULL;		// �����L���O���ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankingScore = NULL;		// �����L���O�X�R�A�e�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureNowLogo = NULL;			// ���݂̃X�R�A���S�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;		// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posRanking;								// �����L���O��ʂ̈ʒu
D3DXVECTOR3 g_posRankingLogo;							// �����L���O���S�̈ʒu
D3DXVECTOR3 g_posRankingRank[RANK_NUM];					// ���ʕ\���̈ʒu
D3DXVECTOR3 g_posRankingScore[RANK_NUM * MAX_SCORE];	// �����L���O�X�R�A�̈ʒu
D3DXVECTOR3 g_posNowLogo;								// ���݂̃X�R�A���S�̈ʒu
D3DXVECTOR3 g_posNowScore[MAX_SCORE];					// ���݂̃X�R�A�̈ʒu
int g_aScoreR[RANK_NUM];								// �����L���O�̃X�R�A
int g_nColorCnt;										// �_�ŐF�̃J�E���g
bool g_aRankInScore[RANK_NUM];							// �V�K�����N�C���̔��f
bool g_bRankIn;											// �����N�C���������ǂ���
int g_nCounter;											// �����J�ڂ̃J�E���g

//==============================================================================
// �����L���O��ʂ̏���������
//==============================================================================
HRESULT InitRanking(void)
{
	// ���[�J���ϐ��錾
	//VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	TITLE title = GetTitle();	// �^�C�g���̎����J�ڏ��

	int nScore = GetScore();	// �X�R�A�̎擾

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/ranking_bg.jpg",
		&g_pTextureRanking);

	// ���S�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/ranking_logo.png",
		&g_pTextureRankingLogo);

	// ���ʃe�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/ranking_rank.png",
		&g_pTextureRankingRank);

	// �X�R�A�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureRankingScore);

	// ���݂̃X�R�A���S�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/yourscore.png",
		&g_pTextureNowLogo);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_POLY,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	g_nColorCnt = 0;
	g_nCounter = 0;
	g_bRankIn = false;
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		g_aScoreR[nCnt] = 0;
		g_aRankInScore[nCnt] = false;
	}

	// �������ɂ�����|���S���̔z�u
	SetInitRanking();

	// BGM�̍Đ�
	PlaySound(SOUND_LABEL_BGM004);

	// �����L���O�̓ǂݍ���
	LoadData();

	// �����L���O�̕��ёւ�
	SetRanking(nScore);

	return S_OK;
}

//==============================================================================
// �����L���O��ʂ̏I������
//==============================================================================
void UninitRanking(void)
{
	// �T�E���h�̒�~����
	StopSound();

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	if (g_pTextureRankingLogo != NULL)
	{
		g_pTextureRankingLogo->Release();
		g_pTextureRankingLogo = NULL;
	}

	if (g_pTextureRankingRank != NULL)
	{
		g_pTextureRankingRank->Release();
		g_pTextureRankingRank = NULL;
	}

	if (g_pTextureRankingScore != NULL)
	{
		g_pTextureRankingScore->Release();
		g_pTextureRankingScore = NULL;
	}

	if (g_pTextureNowLogo != NULL)
	{
		g_pTextureNowLogo->Release();
		g_pTextureNowLogo = NULL;
	}
}

//==============================================================================
// �����L���O��ʂ̍X�V����
//==============================================================================
void UpdateRanking(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	FADE fade;
	TITLE title = GetTitle();	// �����J�ڏ��̎擾
	int nScore = GetScore();	// �X�R�A�̎擾
	float aRank[RANK_NUM] = { 0.0f,0.2f,0.4f,0.6f,0.8f };
	int aNumber[RANK_NUM][MAX_SCORE];
	int nNewCnt = 0;
	float fGreen = 0.0f;
	float fBlue = 0.0f;
	int aNowNum[MAX_SCORE];
	float fAlpha;

	//XINPUT_STATE state;
	//XInputGetState(0, &state);

	// �t�F�[�h�̎擾
	fade = GetFade();

	// �ϐF�J�E���g�̑���
	g_nColorCnt++;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// ���ʂ̕\��
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (nCnt != 0)
		{
			if (g_aScoreR[nCnt] == g_aScoreR[nCnt - 1])
			{
				aRank[nCnt] = aRank[nCnt - 1];
			}
		}

		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.2f + aRank[nCnt]);
		pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f + aRank[nCnt]);
		pVtx[10].tex = D3DXVECTOR2(1.0f, 0.2f + aRank[nCnt]);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 0.0f + aRank[nCnt]);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// �e���̃e�N�X�`���̐؂�ւ�
	for (int nCntRank = 0; nCntRank < RANK_NUM; nCntRank++)
	{
		int nData = (int)pow(10, MAX_SCORE - 1);

		if (g_aScoreR[nCntRank] == nScore &&
			g_bRankIn == false)
		{
			g_aRankInScore[nCntRank] = true;
			g_bRankIn = true;
		}

		for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
		{
			aNumber[nCntRank][nCnt] = (g_aScoreR[nCntRank] / nData) % 10;
			nData /= 10;

			// �e�N�X�`���̒��_���W�̍X�V
			pVtx[28].tex = D3DXVECTOR2(0.0f + ((float)aNumber[nCntRank][nCnt] / 10), 1.0f);
			pVtx[29].tex = D3DXVECTOR2(0.0f + ((float)aNumber[nCntRank][nCnt] / 10), 0.0f);
			pVtx[30].tex = D3DXVECTOR2(0.1f + ((float)aNumber[nCntRank][nCnt] / 10), 1.0f);
			pVtx[31].tex = D3DXVECTOR2(0.1f + ((float)aNumber[nCntRank][nCnt] / 10), 0.0f);

			// ���_�|�C���^��4���i�߂�
			pVtx += 4;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// �V�K�����N�C���̖���
	for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
	{
		if (g_aRankInScore[nCnt] == true)
		{
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++, pVtx = pVtx + 4)
			{
				if (g_nColorCnt % 8 == 0)
				{
					fGreen = 1.0f;
					fBlue = 1.0f;

					// �e���_�J���[�̐ݒ�
					pVtx[28].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
					pVtx[29].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
					pVtx[30].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
					pVtx[31].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
				}

				if (g_nColorCnt % 4 == 0 && g_nColorCnt % 8 != 0)
				{
					fGreen = 0.0f;
					fBlue = 0.0f;

					// �e���_�J���[�̐ݒ�
					pVtx[28].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
					pVtx[29].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
					pVtx[30].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
					pVtx[31].col = D3DXCOLOR(1.0f, fGreen, fBlue, 1.0f);
				}
			}
		}
		else
		{
			pVtx += 4 * MAX_SCORE;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	int nData = (int)pow(10, MAX_SCORE - 1);
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		aNowNum[nCnt] = (nScore / nData) % 10;
		nData /= 10;

		// �e�N�X�`���̒��_���W�̍X�V
		pVtx[192].tex = D3DXVECTOR2(0.0f + ((float)aNowNum[nCnt] / 10), 1.0f);
		pVtx[193].tex = D3DXVECTOR2(0.0f + ((float)aNowNum[nCnt] / 10), 0.0f);
		pVtx[194].tex = D3DXVECTOR2(0.1f + ((float)aNowNum[nCnt] / 10), 1.0f);
		pVtx[195].tex = D3DXVECTOR2(0.1f + ((float)aNowNum[nCnt] / 10), 0.0f);

		// ���_�|�C���^��4���i�߂�
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	if (title.titleauto == TITLE_AUTO)
	{
		fAlpha = 0.0f;
	}
	else
	{
		fAlpha = 1.0f;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�J���[�̐ݒ�
	pVtx[188].col = D3DXCOLOR(1.0f, 0.1f, 1.0f, fAlpha);
	pVtx[189].col = D3DXCOLOR(1.0f, 0.1f, 1.0f, fAlpha);
	pVtx[190].col = D3DXCOLOR(1.0f, 0.1f, 1.0f, fAlpha);
	pVtx[191].col = D3DXCOLOR(1.0f, 0.1f, 1.0f, fAlpha);

	for (int nCnt = 0; nCnt < 8; nCnt++, pVtx += 4)
	{
		// �e���_�J���[�̐ݒ�
		pVtx[192].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, fAlpha);
		pVtx[193].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, fAlpha);
		pVtx[194].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, fAlpha);
		pVtx[195].col = D3DXCOLOR(0.1f, 1.0f, 0.1f, fAlpha);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRanking->Unlock();

	// �^�C�g���ւ̐؂�ւ�
	if ( fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true || g_nCounter >= 300/* || state.Gamepad.wButtons & XINPUT_GAMEPAD_A*/)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}

	if (title.titleauto == TITLE_AUTO)
	{
		g_nCounter++;
	}
}

//==============================================================================
// �����L���O��ʂ̕`�揈��
//==============================================================================
void DrawRanking(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffRanking,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�e�N�X�`���̐ݒ�
	for (int nCnt = 0; nCnt < MAX_POLY; nCnt++)
	{
		if (nCnt == 0)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRanking);
		}
		else if (nCnt == 1)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingLogo);
		}
		else if (nCnt >= 2 && nCnt < (2 + RANK_NUM))
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingRank);
		}
		else if (nCnt == 47)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureNowLogo);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingScore);
		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}

//==============================================================================
// �����L���O�̕��ёւ�
//==============================================================================
void SetRanking(int nScore)
{
	// ���[�J���ϐ��錾
	int nSubData;

	// �����L���O�O�̏��O
	if (g_aScoreR[RANK_NUM - 1] <= nScore)
	{ // �X�R�A�������L���O���̏ꍇ
		g_aScoreR[RANK_NUM - 1] = nScore;
	}

	// �v�Z����
	for (int nCnt = 0; nCnt < RANK_NUM - 1; nCnt++)
	{
		for (int nCnt2 = nCnt + 1; nCnt2 < RANK_NUM; nCnt2++)
		{
			if (g_aScoreR[nCnt] < g_aScoreR[nCnt2])
			{
				nSubData = g_aScoreR[nCnt];
				g_aScoreR[nCnt] = g_aScoreR[nCnt2];
				g_aScoreR[nCnt2] = nSubData;
			}
		}
	}

	// �f�[�^�̕ۑ�����
	SaveData();
}

//==============================================================================
// �t�@�C���̓ǂݍ���
//==============================================================================
void LoadData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	int nCount;

	// �f�[�^�̓ǂݍ���
	pFile = fopen("ranking.txt", "r");
	if (pFile != NULL)
	{ //�t�@�C���W�J�\
		for (nCount = 0; nCount < RANK_NUM; nCount++)
		{
			fscanf(pFile, "%d", &g_aScoreR[nCount]);
		}
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}

//==============================================================================
// �f�[�^�ۑ�����
//==============================================================================
void SaveData(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	int nCount;

	// �t�@�C���̓W�J
	pFile = fopen("ranking.txt", "w");
	if (pFile != NULL)
	{ // �t�@�C���W�J�\
		for (nCount = 0; nCount < RANK_NUM; nCount++)
		{
			fprintf(pFile, "%d\n", g_aScoreR[nCount]);
		}
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}

//==============================================================================
// �������ɂ�����|���S���̔z�u
//==============================================================================
void SetInitRanking(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	TITLE title = GetTitle();

	if (title.titleauto == TITLE_AUTO)
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// �����L���O��ʂ̒��S���W
		g_posRanking = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);

		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posRanking.x - SCREEN_CENTERX, g_posRanking.y + SCREEN_CENTERY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posRanking.x - SCREEN_CENTERX, g_posRanking.y - SCREEN_CENTERY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posRanking.x + SCREEN_CENTERX, g_posRanking.y + SCREEN_CENTERY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posRanking.x + SCREEN_CENTERX, g_posRanking.y - SCREEN_CENTERY, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// �����L���O���S�̒��S���W
		g_posRankingLogo = D3DXVECTOR3(RANKINGLOGO_POSX, RANKINGLOGO_POSY, 0.0f);

		// �|���S���̊e���_���W
		pVtx[4].pos = D3DXVECTOR3(g_posRankingLogo.x - RANKINGLOGO_SIZEX, g_posRankingLogo.y + RANKINGLOGO_SIZEY + 40.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posRankingLogo.x - RANKINGLOGO_SIZEX, g_posRankingLogo.y - RANKINGLOGO_SIZEY + 40.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posRankingLogo.x + RANKINGLOGO_SIZEX, g_posRankingLogo.y + RANKINGLOGO_SIZEY + 40.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posRankingLogo.x + RANKINGLOGO_SIZEX, g_posRankingLogo.y - RANKINGLOGO_SIZEY + 40.0f, 0.0f);

		// rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 2, 2, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 2, 2, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 2, 2, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 2, 2, 255);

		// ���_���W�̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// ���ʕ\���̐ݒ�
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			// ���ʕ\���̒��S���W�̐ݒ�
			g_posRankingRank[nCnt] = D3DXVECTOR3(RANKINGRANK_POSX, RANKINGRANK_POSY + (nCnt * 90), 0.0f);

			//�X�R�A�̒��_���W�̐ݒ�
			pVtx[8].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x - RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y + RANKINGRANK_SIZEY + 60.0f, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x - RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y - RANKINGRANK_SIZEY + 60.0f, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x + RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y + RANKINGRANK_SIZEY + 60.0f, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x + RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y - RANKINGRANK_SIZEY + 60.0f, 0.0f);

			// rhw�̐ݒ�
			pVtx[8].rhw = 1.0f;
			pVtx[9].rhw = 1.0f;
			pVtx[10].rhw = 1.0f;
			pVtx[11].rhw = 1.0f;

			// �e���_�J���[�̐ݒ�
			pVtx[8].col = D3DCOLOR_RGBA(200, 0, 0, 255);
			pVtx[9].col = D3DCOLOR_RGBA(200, 0, 0, 255);
			pVtx[10].col = D3DCOLOR_RGBA(200, 0, 0, 255);
			pVtx[11].col = D3DCOLOR_RGBA(200, 0, 0, 255);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[8].tex = D3DXVECTOR2(0.0f, 0.2f);
			pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[10].tex = D3DXVECTOR2(1.0f, 0.2f);
			pVtx[11].tex = D3DXVECTOR2(1.0f, 0.0f);

			pVtx += 4;	// ���_�|�C���^��4���i�߂�
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// ���ʕ\���̐ݒ�
		for (int nCntRank = 0; nCntRank < RANK_NUM; nCntRank++)
		{
			for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
			{
				// ���ʕ\���̒��S���W�̐ݒ�
				g_posRankingScore[nCnt] = D3DXVECTOR3(RANKING_SCOREX + (nCnt * 40), RANKING_SCOREY + (nCntRank * 90), 0.0f);

				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[28].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x - RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y + RANKING_SCORE_SIZEY + 60.0f, 0.0f);
				pVtx[29].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x - RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y - RANKING_SCORE_SIZEY + 60.0f, 0.0f);
				pVtx[30].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x + RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y + RANKING_SCORE_SIZEY + 60.0f, 0.0f);
				pVtx[31].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x + RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y - RANKING_SCORE_SIZEY + 60.0f, 0.0f);

				// rhw�̐ݒ�
				pVtx[28].rhw = 1.0f;
				pVtx[29].rhw = 1.0f;
				pVtx[30].rhw = 1.0f;
				pVtx[31].rhw = 1.0f;

				// �e���_�J���[�̐ݒ�
				pVtx[28].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
				pVtx[29].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
				pVtx[30].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
				pVtx[31].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);

				// �e�N�X�`�����_���̐ݒ�
				pVtx[28].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[29].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[30].tex = D3DXVECTOR2(0.1f, 1.0f);
				pVtx[31].tex = D3DXVECTOR2(0.1f, 0.0f);

				pVtx += 4;	// ���_�|�C���^��4���i�߂�
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();
	}
	else
	{
		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// �����L���O��ʂ̒��S���W
		g_posRanking = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);

		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posRanking.x - SCREEN_CENTERX, g_posRanking.y + SCREEN_CENTERY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posRanking.x - SCREEN_CENTERX, g_posRanking.y - SCREEN_CENTERY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posRanking.x + SCREEN_CENTERX, g_posRanking.y + SCREEN_CENTERY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posRanking.x + SCREEN_CENTERX, g_posRanking.y - SCREEN_CENTERY, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// �����L���O���S�̒��S���W
		g_posRankingLogo = D3DXVECTOR3(RANKINGLOGO_POSX, RANKINGLOGO_POSY, 0.0f);

		// �|���S���̊e���_���W
		pVtx[4].pos = D3DXVECTOR3(g_posRankingLogo.x - RANKINGLOGO_SIZEX, g_posRankingLogo.y + RANKINGLOGO_SIZEY, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(g_posRankingLogo.x - RANKINGLOGO_SIZEX, g_posRankingLogo.y - RANKINGLOGO_SIZEY, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(g_posRankingLogo.x + RANKINGLOGO_SIZEX, g_posRankingLogo.y + RANKINGLOGO_SIZEY, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(g_posRankingLogo.x + RANKINGLOGO_SIZEX, g_posRankingLogo.y - RANKINGLOGO_SIZEY, 0.0f);

		// rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[4].col = D3DCOLOR_RGBA(255, 2, 2, 255);
		pVtx[5].col = D3DCOLOR_RGBA(255, 2, 2, 255);
		pVtx[6].col = D3DCOLOR_RGBA(255, 2, 2, 255);
		pVtx[7].col = D3DCOLOR_RGBA(255, 2, 2, 255);

		// ���_���W�̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// ���ʕ\���̐ݒ�
		for (int nCnt = 0; nCnt < RANK_NUM; nCnt++)
		{
			// ���ʕ\���̒��S���W�̐ݒ�
			g_posRankingRank[nCnt] = D3DXVECTOR3(RANKINGRANK_POSX, RANKINGRANK_POSY + (nCnt * 90), 0.0f);

			//�X�R�A�̒��_���W�̐ݒ�
			pVtx[8].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x - RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y + RANKINGRANK_SIZEY, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x - RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y - RANKINGRANK_SIZEY, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x + RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y + RANKINGRANK_SIZEY, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(g_posRankingRank[nCnt].x + RANKINGRANK_SIZEX, g_posRankingRank[nCnt].y - RANKINGRANK_SIZEY, 0.0f);

			// rhw�̐ݒ�
			pVtx[8].rhw = 1.0f;
			pVtx[9].rhw = 1.0f;
			pVtx[10].rhw = 1.0f;
			pVtx[11].rhw = 1.0f;

			// �e���_�J���[�̐ݒ�
			pVtx[8].col = D3DCOLOR_RGBA(200, 0, 200, 255);
			pVtx[9].col = D3DCOLOR_RGBA(200, 0, 200, 255);
			pVtx[10].col = D3DCOLOR_RGBA(200, 0, 200, 255);
			pVtx[11].col = D3DCOLOR_RGBA(200, 0, 200, 255);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[8].tex = D3DXVECTOR2(0.0f, 0.2f);
			pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[10].tex = D3DXVECTOR2(1.0f, 0.2f);
			pVtx[11].tex = D3DXVECTOR2(1.0f, 0.0f);

			pVtx += 4;	// ���_�|�C���^��4���i�߂�
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// ���ʕ\���̐ݒ�
		for (int nCntRank = 0; nCntRank < RANK_NUM; nCntRank++)
		{
			for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
			{
				// ���ʕ\���̒��S���W�̐ݒ�
				g_posRankingScore[nCnt] = D3DXVECTOR3(RANKING_SCOREX + (nCnt * 40), RANKING_SCOREY + (nCntRank * 90), 0.0f);

				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[28].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x - RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y + RANKING_SCORE_SIZEY, 0.0f);
				pVtx[29].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x - RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y - RANKING_SCORE_SIZEY, 0.0f);
				pVtx[30].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x + RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y + RANKING_SCORE_SIZEY, 0.0f);
				pVtx[31].pos = D3DXVECTOR3(g_posRankingScore[nCnt].x + RANKING_SCORE_SIZEX, g_posRankingScore[nCnt].y - RANKING_SCORE_SIZEY, 0.0f);

				// rhw�̐ݒ�
				pVtx[28].rhw = 1.0f;
				pVtx[29].rhw = 1.0f;
				pVtx[30].rhw = 1.0f;
				pVtx[31].rhw = 1.0f;

				// �e���_�J���[�̐ݒ�
				pVtx[28].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
				pVtx[29].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
				pVtx[30].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);
				pVtx[31].col = D3DXCOLOR(0.1f, 0.1f, 1.0f, 1.0f);

				// �e�N�X�`�����_���̐ݒ�
				pVtx[28].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[29].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[30].tex = D3DXVECTOR2(0.1f, 1.0f);
				pVtx[31].tex = D3DXVECTOR2(0.1f, 0.0f);

				pVtx += 4;	// ���_�|�C���^��4���i�߂�
			}
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		// ���ʕ\���̒��S���W�̐ݒ�
		g_posNowLogo = D3DXVECTOR3(RANKING_NOWLOGOX, RANKING_NOWLOGOY, 0.0f);

		//�X�R�A�̒��_���W�̐ݒ�
		pVtx[188].pos = D3DXVECTOR3(g_posNowLogo.x - RANKINGRANK_SIZEX, g_posNowLogo.y + RANKINGRANK_SIZEY, 0.0f);
		pVtx[189].pos = D3DXVECTOR3(g_posNowLogo.x - RANKINGRANK_SIZEX, g_posNowLogo.y - RANKINGRANK_SIZEY, 0.0f);
		pVtx[190].pos = D3DXVECTOR3(g_posNowLogo.x + RANKINGRANK_SIZEX, g_posNowLogo.y + RANKINGRANK_SIZEY, 0.0f);
		pVtx[191].pos = D3DXVECTOR3(g_posNowLogo.x + RANKINGRANK_SIZEX, g_posNowLogo.y - RANKINGRANK_SIZEY, 0.0f);

		// rhw�̐ݒ�
		pVtx[188].rhw = 1.0f;
		pVtx[189].rhw = 1.0f;
		pVtx[190].rhw = 1.0f;
		pVtx[191].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[188].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[189].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[190].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[191].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[188].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[189].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[190].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[191].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();


		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
		{
			// ���ʕ\���̒��S���W�̐ݒ�
			g_posNowScore[nCnt] = D3DXVECTOR3(RANKING_NOWSCOREX + (nCnt * 40), RANKING_NOWSCOREY, 0.0f);

			//�X�R�A�̒��_���W�̐ݒ�
			pVtx[192].pos = D3DXVECTOR3(g_posNowScore[nCnt].x - RANKING_SCORE_SIZEX, g_posNowScore[nCnt].y + RANKING_SCORE_SIZEY, 0.0f);
			pVtx[193].pos = D3DXVECTOR3(g_posNowScore[nCnt].x - RANKING_SCORE_SIZEX, g_posNowScore[nCnt].y - RANKING_SCORE_SIZEY, 0.0f);
			pVtx[194].pos = D3DXVECTOR3(g_posNowScore[nCnt].x + RANKING_SCORE_SIZEX, g_posNowScore[nCnt].y + RANKING_SCORE_SIZEY, 0.0f);
			pVtx[195].pos = D3DXVECTOR3(g_posNowScore[nCnt].x + RANKING_SCORE_SIZEX, g_posNowScore[nCnt].y - RANKING_SCORE_SIZEY, 0.0f);

			// rhw�̐ݒ�
			pVtx[192].rhw = 1.0f;
			pVtx[193].rhw = 1.0f;
			pVtx[194].rhw = 1.0f;
			pVtx[195].rhw = 1.0f;

			// �e���_�J���[�̐ݒ�
			pVtx[192].col = D3DXCOLOR(1.0f, 0.6f, 0.01f, 1.0f);
			pVtx[193].col = D3DXCOLOR(1.0f, 0.6f, 0.01f, 1.0f);
			pVtx[194].col = D3DXCOLOR(1.0f, 0.6f, 0.01f, 1.0f);
			pVtx[195].col = D3DXCOLOR(1.0f, 0.6f, 0.01f, 1.0f);

			// �e�N�X�`�����_���̐ݒ�
			pVtx[192].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[193].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[194].tex = D3DXVECTOR2(0.1f, 1.0f);
			pVtx[195].tex = D3DXVECTOR2(0.1f, 0.0f);

			pVtx += 4;	// ���_�|�C���^��4���i�߂�
		}

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffRanking->Unlock();
	}
}