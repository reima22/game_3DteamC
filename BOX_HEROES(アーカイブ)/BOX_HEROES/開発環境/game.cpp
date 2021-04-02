//==============================================================================
//
// �Q�[����ʂ̕`��kgame.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include "player.h"
#include "start.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "shadow.h"
#include "billboard.h"
#include "meshfield.h"
#include "meshwall.h"
#include "bullet.h"
#include "object.h"
#include "sound.h"
#include "input.h"
#include "hp.h"
#include "fade.h"
#include "item.h"
#include "pause.h"
#include "particle.h"
#include "gamepad.h"
#include "meshorbit.h"
#include "select.h"
#include "bullet_ui.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

//==============================================================================
// �}�N����`
//==============================================================================
//#define VERTICAL_STEP	(90)	// �c�ړ�����u���b�N�̃J�E���g�Ԋu
//#define SIDE_STEP		(240)	// ���ړ�����u���b�N�̃J�E���g�Ԋu
//#define BLOCKX			(46)	// �u���b�N�z�u��csv�t�@�C���̗�
//#define BLOCKY			(24)	// �u���b�N�z�u��csv�t�@�C���̍s��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
bool g_bPause;				// �|�[�Y�̏��

//==============================================================================
// �Q�[����ʂ̏���������
//==============================================================================
HRESULT InitGame(void)
{
	// �����������猻���������O
	srand((unsigned int)time(0));

	// �ϐ��̏�����
	g_bPause = false;

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �e�̏���������
	InitShadow();

	// �A�C�e���̏���������
	InitItem();

	// �v���C���[�̏���������
	InitPlayer();

	InitObject();

	// ���b�V���t�B�[���h�̏�����
	InitMeshfield();

	// ���b�V���ǂ̏���������
	InitMeshwall();

	// ���b�V���O�Տ�����
	InitMeshOrbit();

	// �e�̏�����
	InitBullet();

	// �G�t�F�N�g�̏���������
	InitParticle();

	// �|�[�Y���j���[�̏���������
	InitPause();

	// UI�̏������ݒ�
	InitHp();

	// �e��UI������
	InitBulletUI();

	// �J�n�����̏�����
	InitStart();

	Select *pSelect = GetSelect();

	bool bGamebgm = GAME_BGM;
	if (bGamebgm == true)
	{
		if (pSelect->stage == 0)
		{
			// BGM�̍Đ�
			PlaySound(SOUND_LABEL_STAGE0);
		}
		else if (pSelect->stage == 1)
		{
			// BGM�̍Đ�
			PlaySound(SOUND_LABEL_STAGE1);
		}
		else
		{
			// BGM�̍Đ�
			PlaySound(SOUND_LABEL_STAGE2);
		}
	}

	return S_OK;
}

//==============================================================================
// �Q�[����ʂ̏I������
//==============================================================================
void UninitGame(void)
{
	// �T�E���h�̒�~����
	StopSound();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// �|���S���̏I������
	UninitObject();

	UninitItem();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	// ���b�V���ǂ̏I������
	UninitMeshwall();

	// ���b�V����Ղ̏I������
	UninitMeshOrbit();

	// �v���C���[�̏I������
	UninitPlayer();

	// �e�̏I������
	UninitBullet();

	// �e�̏I������
	UninitShadow();

	// �G�t�F�N�g�̏I������
	UninitParticle();

	// �|�[�Y���j���[�̏I������
	UninitPause();

	// UI�̏I������
	UninitHp();

	// �e��UI�I������
	UninitBulletUI();

	// �J�n�����̏I������
	UninitStart();
}

//==============================================================================
// �Q�[����ʂ̍X�V����
//==============================================================================
void UpdateGame(void)
{
	// ���[�J���ϐ��錾
	Player *pPlayer;
	PAUSE pause;
	FADE fade;
	HP *hp = GetHp();
	int nStart = GetCount();

	// �v���C���[�̎擾
	pPlayer = GetPlayer();

	// �|�[�Y�̎擾
	pause = GetPause();

	// �t�F�[�h�̎擾
	fade = GetFade();

	UpdateStart();

	// �|�[�Y���j���[�ֈڍs
	if (pPlayer->state != PLAYERSTATE_CLEAR && pPlayer->state != PLAYERSTATE_GAMEOVER && pause.colOption.a <= 0.0f && fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(KEYINFO_PAUSE) == true || IsButtonDown(KEYINFO::KEYINFO_PAUSE) == true)
		{
				// ���̍Đ�
				PlaySound(SOUND_LABEL_SE_START);

				g_bPause = g_bPause ? false : true;	// �|�[�Y�̐؂�ւ�
		}
	}

	if (g_bPause == true)
	{ // �|�[�Y���̐ݒ�
		UpdatePause();	// �|�[�Y�̍X�V����

		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{ // �I�����̉�ʑJ�ڏ���
			if (fade != FADE_OUT && pause.colOption.a <= 0.0f)
			{ // �I�������̏d���h�~
				// �T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_START);
			}
			
			if (pause.PauseMenu == PAUSE_MENU_CONTINUE)
			{ // CONTINUE�̎�
				g_bPause = false;				// �|�[�Y�̉���(�Q�[���̑��s)
			}
			else if(pause.PauseMenu == PAUSE_MENU_RETRY)
			{ // RETRY�̎�
				SetFade(FADE_OUT, MODE_GAME);	// �Q�[���̂�蒼��
				//g_nGameCnt = START_NUM;
			}
			else if (pause.PauseMenu == PAUSE_MENU_QUIT)
			{ // QUIT�̎�
				SetFade(FADE_OUT, MODE_TITLE);	// �^�C�g���ֈڍs
			}
		}
	}
	else
	{ // ��|�[�Y���̏���
		if (pPlayer->state != PLAYERSTATE_CLEAR && nStart >= 240)
		{ // �Q�[�����̏���
			// �J�����̍X�V����
			UpdateCamera();

			// ���C�g�̍X�V����
			UpdateLight();

			// �e�̍X�V����
			UpdateBullet();

			// �v���C���[�̍X�V����
			UpdatePlayer();

			// ���b�V���t�B�[���h�̍X�V����
			UpdateMeshfield();

			// ���b�V���ǂ̍X�V����
			UpdateMeshwall();

			// ���b�V���O�Ղ̍X�V����
			UpdateMeshOrbit();

			UpdateObject();

			UpdateItem();

			UpdateHp();

			// �e�̍X�V����
			UpdateShadow();

			// �e��UI�X�V
			UpdateBulletUI();
		}

		// �G�t�F�N�g�̍X�V����
		UpdateParticle();
	
		// ��ʂ̑J�ځi�Q�[���N���A���j
		if (pPlayer->state == PLAYERSTATE_CLEAR)
		{
			SetFade(FADE_OUT, MODE_RESULT);	// �Q�[�����[�h���s
		}
	}
}

//==============================================================================
// �Q�[����ʂ̕`�揈��
//==============================================================================
void DrawGame(void)
{
	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshfield();

	// ���b�V���ǂ̕`�揈��
	DrawMeshwall();

	// ���f���̕`�揈��
	DrawPlayer();

	DrawObject();

	DrawItem();

	// �e�̕`�揈��
	DrawShadow();

	// �e�̕`�揈��
	DrawBullet();

	// �G�t�F�N�g�̍X�V����
	DrawParticle();

	// UI�̕`�揈��
	DrawHp();

	// ���b�V���O�Ղ̕`�揈��
	DrawMeshOrbit();

	// �e��UI�`��
	DrawBulletUI();

	// �J�n�����̕`�揈��
	DrawStart();

	// �|�[�Y�̕`�揈��
	if (g_bPause == true)
	{
		DrawPause();
	}
}