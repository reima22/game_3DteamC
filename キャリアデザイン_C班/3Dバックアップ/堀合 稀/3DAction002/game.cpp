//==============================================================================
//
// �Q�[����ʂ̕`��kgame.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "game.h"
#include "player.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "meshwall.h"
#include "bullet.h"
#include "object.h"
//#include "bg.h"
//#include "enemy.h"
#include "score.h"
#include "sound.h"
#include "input.h"
//#include "ui.h"
#include "fade.h"
//#include "item.h"
#include "pause.h"
//#include "life.h"
//#include "particle.h"
//#include "block.h"
//#include "timer.h"
#include "gamepad.h"
//#include "nodamage.h"
#include "time.h"
#include "stdlib.h"
#include "stdio.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define VERTICAL_STEP	(90)	// �c�ړ�����u���b�N�̃J�E���g�Ԋu
#define SIDE_STEP		(240)	// ���ړ�����u���b�N�̃J�E���g�Ԋu
#define BLOCKX			(46)	// �u���b�N�z�u��csv�t�@�C���̗�
#define BLOCKY			(24)	// �u���b�N�z�u��csv�t�@�C���̍s��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
bool g_bPause;				// �|�[�Y�̏��
int g_nGameCnt = START_NUM;	// �X�e�[�W�J�E���g
int g_nStartCnt;
int g_aMapData[BLOCKY][BLOCKX];

//==============================================================================
// �Q�[����ʂ̏���������
//==============================================================================
HRESULT InitGame(void)
{
	// �����������猻���������O
	srand((unsigned int)time(0));

	// �ϐ��̏�����
	g_bPause = false;
	g_nStartCnt = g_nGameCnt;

	// �w�i�|���S���̏������ݒ�
	//InitBg();
	// �^�C�}�[�̏���������
	//InitTimer();
	// �A�C�e���̏���������
	//InitItem();
	// �A�C�e���̔z�u
	//PutItem(g_nGameCnt);

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �e�̏���������
	InitShadow();

	// �v���C���[�̏���������
	InitPlayer();

	InitObject();

	// �|���S���̏���������
	InitPolygon();

	// ���b�V���t�B�[���h�̏�����
	InitMeshfield();

	// �ǂ̏���������
	InitWall();

	// ���b�V���ǂ̏���������
	InitMeshwall();

	// �r���{�[�h�̏�����
	InitBillboard();

	// �e�̏�����
	InitBullet();

	// �G�t�F�N�g�̏���������
	//InitParticle();

	// �X�R�A�̏���������
	InitScore();

	// �|�[�Y���j���[�̏���������
	InitPause();

	// �̗͕\���̏���������
	//InitLife();
	// UI�̏������ݒ�
	//InitUI();

	// �m�[�_���[�W�{�[�i�X�̏���������
	//InitNodamage();

	// BGM�̍Đ�
	//if (g_nGameCnt == 0)
	//{
	//	PlaySound(SOUND_LABEL_BGM001);
	//}
	//else if (g_nGameCnt == 1)
	//{
	//	PlaySound(SOUND_LABEL_BGM005);	
	//}
	//else if (g_nGameCnt == 2)
	//{
	//	PlaySound(SOUND_LABEL_BGM006);
	//}

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
	UninitPolygon();

	UninitObject();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	// �ǂ̏I������
	UninitWall();

	// ���b�V���ǂ̏I������
	UninitMeshwall();

	// �w�i�|���S���̏I������
	//UninitBg();

	// �v���C���[�̏I������
	UninitPlayer();

	// �r���{�[�h�̏I������
	UninitBillboard();

	// �e�̏I������
	UninitBullet();

	// �e�̏I������
	UninitShadow();

	// �G�̏I������
	//UninitEnemy();
	// �A�C�e���̏I������
	//UninitItem();
	// �G�t�F�N�g�̏I������
	//UninitParticle();

	// �X�R�A�̏I������
	UninitScore();

	// �^�C�}�[�̏I������
	//UninitTimer();

	// �|�[�Y���j���[�̏I������
	UninitPause();

	// �̗͕\���̏I������
	//UninitLife();
	// UI�̏I������
	//UninitUI();
	// �m�[�_���[�W�{�[�i�X�̏I������
	//UninitNodamage();
}

//==============================================================================
// �Q�[����ʂ̍X�V����
//==============================================================================
void UpdateGame(void)
{
	// ���[�J���ϐ��錾
	Player *player;
	PAUSE pause;
	FADE fade;
	//int nTime = GetTimer();
	int nGameCnt = g_nGameCnt;

	// �v���C���[�̎擾
	player = GetPlayer();

	// �|�[�Y�̎擾
	pause = GetPause();

	// �t�F�[�h�̎擾
	fade = GetFade();

	// �J�����̐ݒ�
	SetCamera();

	// �|�[�Y���j���[�ֈڍs
	if (/*player->state != PLAYERSTATE_CLEAR && player->state != PLAYERSTATE_GAMEOVER &&*/ pause.colOption.a <= 0.0f && fade == FADE_NONE)
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
		{ // �I�����̉�ʑJ�ڏ���
			if (fade != FADE_OUT && pause.colOption.a <= 0.0f)
			{ // �I�������̏d���h�~
				// �T�E���h�̍Đ�
				PlaySound(SOUND_LABEL_SE_START000);
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
		//if (player->state != PLAYERSTATE_CLEAR && player->state != PLAYERSTATE_GAMEOVER)
		{ // �Q�[�����̏���
		  // �w�i�|���S���̍X�V����
			//UpdateBg();

			// �G�̍X�V����
			//UpdateEnemy();

			// �A�C�e���̍X�V����
			//UpdateItem();

			// �J�����̍X�V����
			UpdateCamera();

			// ���C�g�̍X�V����
			UpdateLight();

			// �r���{�[�h�̍X�V����
			UpdateBillboard();

			// �e�̍X�V����
			UpdateBullet();

			// �v���C���[�̍X�V����
			UpdatePlayer();

			// �|���S���̍X�V����
			UpdatePolygon();

			// ���b�V���t�B�[���h�̍X�V����
			UpdateMeshfield();

			// �ǂ̍X�V����
			UpdateWall();

			// ���b�V���ǂ̍X�V����
			UpdateMeshwall();

			UpdateObject();

			// �e�̍X�V����
			UpdateShadow();

		}

		// �G�t�F�N�g�̍X�V����
		//UpdateParticle();

		//if (player->state != PLAYERSTATE_GAMEOVER)
		{
			// �X�R�A�̍X�V����
			//UpdateScore();

			// �^�C�}�[�̍X�V����
			//UpdateTimer();

			// �m�[�_���[�W�{�[�i�X�̍X�V����
			//UpdateNodamage();
		}
	
		//// ��ʂ̑J�ځi�Q�[���N���A���j
		//if (nTime <= 0 && Player->state == PLAYERSTATE_CLEAR && g_nGameCnt < MAX_STAGE && g_nStartCnt == g_nGameCnt)
		//{
		//	g_nGameCnt++;					// �X�e�[�W�J�E���g���Z
		//	SetFade(FADE_OUT, MODE_GAME);	// �Q�[�����[�h���s
		//}
		//else if(nTime <= 0 && g_nGameCnt == MAX_STAGE)
		//{
		//	SetFade(FADE_OUT, MODE_RESULT);	// ���U���g��
		//}
		//
		//// ��ʂ̑J�ځi�Q�[���I�[�o�[���j
		//if (Player->state == PLAYERSTATE_GAMEOVER)
		//{
		//	SetFade(FADE_OUT, MODE_RESULT);	// ���U���g��
		//}

		if (GetKeyboardTrigger(KEYINFO_OK) == true && g_bPause == false)
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
	//// �w�i�|���S���̕`�揈��
	//DrawBg();
	//// �G�̕`�揈��
	//DrawEnemy();
	//// �A�C�e���̕`�揈��
	//DrawItem();

	// �|���S���̕`�揈��
	DrawPolygon();

	// ���b�V���t�B�[���h�̕`�揈��
	DrawMeshfield();

	// �ǂ̕`�揈��
	DrawWall();

	// ���b�V���ǂ̕`�揈��
	DrawMeshwall();

	// ���f���̕`�揈��
	DrawPlayer();

	DrawObject();

	// �e�̕`�揈��
	DrawShadow();

	// �e�̕`�揈��
	DrawBullet();

	// �r���{�[�h�̕`�揈��
	DrawBillboard();

	//// �G�t�F�N�g�̍X�V����
	//DrawParticle();
	//// �u���b�N�̕`�揈��
	//DrawBlock();
	//// UI�̕`�揈��
	//DrawUI();

	// �X�R�A�̕`�揈��
	DrawScore();

	//// �^�C�}�[�̕`�揈��
	//DrawTimer();
	//// �̗͕\���̕`�揈��
	//DrawLife();
	//// �m�[�_���[�W�{�[�i�X�̕`�揈��
	//DrawNodamage();

	// �|�[�Y�̕`�揈��
	if (g_bPause == true)
	{
		DrawPause();
	}
}

//==============================================================================
// �Q�[���X�e�[�W�J�E���g�̏�����
//==============================================================================
//HRESULT InitGameCnt(void)
//{
//	//// �ϐ��̏�����
//	//g_nGameCnt = 0;
//
//	//return S_OK;
//}