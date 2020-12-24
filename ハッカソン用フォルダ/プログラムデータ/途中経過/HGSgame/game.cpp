//==============================================================================
//
// �Q�[����ʂ̕`��kgame.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "game.h"
#include "player.h"
#include "bg.h"
#include "bullet.h"
//#include "enemy.h"
//#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "input.h"
//#include "ui.h"
#include "fade.h"
#include "item.h"
#include "pause.h"
//#include "counter.h"
//#include "life.h"
//#include "effect.h"
#include "particle.h"
//#include "bullet_ui.h"
//#include "line.h"
//#include "stock.h"
//#include "warning.h"
#include "block.h"
#include "gamepad.h"
#include "timer.h"
#include "time.h"
#include "stdlib.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define ENEMY_POSX			(50.0f)		// �G�̏���X���W
#define ENEMY_POSY			(-20.0f)	// �G�̏���Y���W

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
bool g_bPause;

//==============================================================================
// �Q�[����ʂ̏���������
//==============================================================================
HRESULT InitGame(void)
{
	// �����������猻���������O
	srand((unsigned int)time(0));

	// �ϐ��̏�����
	g_bPause = false;

	// �w�i�|���S���̏������ݒ�
	InitBg();

	// ���[�U�[�C���^�[�t�F�[�X�̏������ݒ�
	//InitStock();

	// �v���C���[�̏���������
	InitPlayer();

	// �ǂ̏������ݒ�
	InitBlock();

	// �A�C�e���̏���������
	InitItem();

	// �e�̏������ݒ�
	InitBullet();

	// �G�t�F�N�g�̏���������
	InitParticle();

	// �^�C�}�[�̏���������
	InitTimer();

	// �X�R�A�̏���������
	InitScore();

	// �|�[�Y���j���[�̏���������
	InitPause();

	// BGM�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);

	return S_OK;
}

//==============================================================================
// �Q�[����ʂ̏I������
//==============================================================================
void UninitGame(void)
{
	// �T�E���h�̒�~����
	StopSound();

	// �w�i�|���S���̏I������
	UninitBg();

	// ���[�U�[�C���^�[�t�F�[�X�̏I������
	//UninitStock();

	// �e�̏I������
	UninitBullet();

	// �v���C���[�̏I������
	UninitPlayer();

	// �G�̏I������
	UninitBlock();

	// �A�C�e���̏I������
	UninitItem();

	// �G�t�F�N�g�̏I������
	UninitParticle();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �X�R�A�̏I������
	UninitScore();

	// �|�[�Y���j���[�̏I������
	UninitPause();
}

//==============================================================================
// �Q�[����ʂ̍X�V����
//==============================================================================
void UpdateGame(void)
{
	// ���[�J���ϐ��錾
	PLAYER *Player;
	PAUSE_MENU pause;
	FADE fade;
	//ENEMYINFO info = GetInfo();		// �G�̑S�̏��̎擾
	//PHASESTATE phase = GetPhase();	// �x����Ԃ̎擾

	// �v���C���[�̎擾
	Player = GetPlayer();

	// �|�[�Y�̎擾
	pause = GetPause();

	// �t�F�[�h�̎擾
	fade = GetFade();

	// �|�[�Y���j���[�ֈڍs
	//if (info.nStartCnt >= OPEN_CNT)
	{
		if (GetKeyboardTrigger(KEYINFO_PAUSE) == true || IsButtonDown(KEYINFO::KEYINFO_PAUSE) == true)
		{
			// ���̍Đ�
			PlaySound(SOUND_LABEL_SE_START000);
			g_bPause = g_bPause ? false : true;	// �|�[�Y�̐؂�ւ�
		}
	}

	if (g_bPause == true)
	{ // �|�[�Y���̐ݒ�
		UpdatePause();	// �|�[�Y�̍X�V����

		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{ // �I�����̏���
			if (fade != FADE_OUT)
			{ // �I�������̏d���h�~
				// �T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_START000);
			}
			
			if (pause == PAUSE_MENU_CONTINUE)
			{ // CONTINUE�̎�
				g_bPause = false;				// �|�[�Y�̉���(�Q�[���̑��s)
			}
			else if(pause == PAUSE_MENU_RETRY)
			{ // RETRY�̎�
				SetFade(FADE_OUT, MODE_GAME);	// �Q�[���̂�蒼��
			}
			else if (pause == PAUSE_MENU_QUIT)
			{ // QUIT�̎�
				SetFade(FADE_OUT, MODE_TITLE);	// �^�C�g���ֈڍs
			}
		}
	}
	else
	{ // ��|�[�Y���̏���
		if (/*info.boss != BIGENEMY_DEATH && */Player->state != PLAYERSTATE_GAMEOVER)
		{ // �Q�[�����̏���
		  // �w�i�|���S���̍X�V����
			UpdateBg();

			// ���[�U�[�C���^�[�t�F�[�X�̍X�V����
			//UpdateStock();

			// �e�̍X�V����
			UpdateBullet();

			// �G�̍X�V����
			UpdateBlock();

			// �A�C�e���̍X�V����
			UpdateItem();

			// �v���C���[�X�V���̏���
			//if (info.nStartCnt >= OPEN_CNT && phase == PHASESTATE_NORMAL)
			{
				// �v���C���[�̍X�V����
				UpdatePlayer();
			}

			// �G�t�F�N�g�̍X�V����
			UpdateParticle();

			// �^�C�}�[�̍X�V����
			UpdateTimer();

			// �X�R�A�̍X�V����
			UpdateScore();
		}

		// ���U���g��ʂւ̑J��
		if (/*info.boss == BIGENEMY_DEATH ||*/ Player->state == PLAYERSTATE_GAMEOVER)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
}

//==============================================================================
// �Q�[����ʂ̕`�揈��
//==============================================================================
void DrawGame(void)
{
	// �w�i�|���S���̕`�揈��
	DrawBg();

	// �G�̕`�揈��
	DrawBlock();

	// �A�C�e���̕`�揈��
	DrawItem();

	// �e�̕`�揈��
	DrawBullet();

	// �G�t�F�N�g�̍X�V����
	DrawParticle();

	// �^�C�}�[�̕`�揈��
	DrawTimer();
	
	// �|���S���̕`�揈��
	DrawPlayer();

	// ���[�U�[�C���^�[�t�F�[�X�̕`�揈��
	//DrawStock();

	// �X�R�A�̕`�揈��
	DrawScore();

	// �|�[�Y�̕`�揈��
	if (g_bPause == true)
	{
		DrawPause();
	}
}