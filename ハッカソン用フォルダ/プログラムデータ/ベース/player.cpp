//==============================================================================
//
// �v���C���[�̕`��kplayer.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "player.h"
#include "game.h"
#include "enemy.h"
#include "block.h"
#include "input.h"
#include "item.h"
#include "score.h"
#include "particle.h"
#include "sound.h"
#include "timer.h"
#include "gamepad.h"
#include "xpad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define PLAYER_LEFT_REMIT	(-20)	// �v���C���[�ړ��̍������[�v�n�_
#define PLAYER_RIGHT_REMIT	(1300)	// �v���C���[�ړ��̉E�����[�v�n�_
#define APPEAR_REMIT		(80)	// �o����ԃJ�E���^�[���
#define WAIT_REMIT			(30)	// �ҋ@��ԃJ�E���^�[���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// �v���C���[�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// �o�b�t�@�ւ̃|�C���^
PLAYER Player;										// �v���C���[�̏��

//==============================================================================
// �v���C���[�̏���������
//==============================================================================
HRESULT InitPlayer(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	ITEM *pItem;
	pItem = GetItem();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	Player.fWidth = PLAYER_SIZEX;
	Player.fHeight = PLAYER_SIZEY;
	Player.colorPlayer = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Player.state = PLAYERSTATE_NORMAL;
	Player.nCounterState = 0;
	Player.nCounterDisp = 0;
	Player.nLife = PLAYER_LIFE;
	Player.nStock = 0;
	Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Player.nCntAnime = 1;
	Player.bRight = true;
	Player.bJump = true;
	Player.fAnime = 0.0f;
	Player.nGetCoin = 0;
	Player.nTrueCoin = 0;
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++, pItem++)
	{
		if (pItem->bUse == true)
		{
			Player.nTrueCoin++;
		}
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/player000.png",
		&g_pTexturePlayer);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �v���C���[�̏����z�u���S���W
	SetPlayer();

	// �v���C���[�̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(Player.pos.x - Player.fWidth, Player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Player.pos.x - Player.fWidth, Player.pos.y - Player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Player.pos.x + Player.fWidth, Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Player.pos.x + Player.fWidth, Player.pos.y - Player.fHeight, 0.0f);

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

	// �e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / 4.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 4.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//==============================================================================
// �v���C���[�̏I������
//==============================================================================
void UninitPlayer(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//==============================================================================
// �v���C���[�̍X�V����
//==============================================================================
void UpdatePlayer(void)
{
	// �O��̈ʒu��ۑ�
	Player.posOld = Player.pos;

	// �A�C�e������
	ItemGet();

	// �G�Ƃ̐ڐG
	TouchEnemy();

	// �v���C���[�̈ړ�
	MovePlayer();

	// �v���C���[�̃e�N�X�`���A�j���[�V����
	PlayerAnim();

	// �v���C���[�̏��
	PlayerState(Player.state);
}

//==============================================================================
// �v���C���[�̕`�揈��
//==============================================================================
void DrawPlayer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffPlayer,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}

//==============================================================================
// �v���C���[�̎擾
//==============================================================================
PLAYER *GetPlayer(void)
{
	return &Player;
}

//==============================================================================
// �A�C�e�����菈��
//==============================================================================
void ItemGet(void)
{
	// ���[�J���ϐ��錾
	ITEM *pItem;
	int nStage = GetStage();

	// �A�C�e���̎擾
	pItem = GetItem();

	// ���@�ƃA�C�e���̐ڐG
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++, pItem++)
	{
		if (Player.pos.x + PLAYER_SIZEX >= pItem->pos.x - ITEM_SIZEX / 2 &&
			Player.pos.x - PLAYER_SIZEX <= pItem->pos.x + ITEM_SIZEX / 2 &&
			Player.pos.y - PLAYER_SIZEY <= pItem->pos.y + ITEM_SIZEY / 2 &&
			Player.pos.y >= pItem->pos.y - ITEM_SIZEY / 2)
		{
			if (pItem->bUse == true)
			{ // �A�C�e���o����

				// �A�C�e���|���S���̏���
				pItem->bUse = false;

				// �X�R�A�̒ǉ�
				if (pItem->col.g == 0.0f)
				{
					// �G�t�F�N�g�̐ݒ�
					SetEffect(D3DXVECTOR3(pItem->pos.x, pItem->pos.y, 0.0f), 0.02f, D3DXCOLOR(1.0f, 0.1f, 0.1f, 1.0f), 10.0f, 0.05f, 30);

					// �T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_HIGHCOIN);
					AddScore(50000);
				}
				else
				{
					// �G�t�F�N�g�̐ݒ�
					SetEffect(D3DXVECTOR3(pItem->pos.x, pItem->pos.y, 0.0f), 0.02f, D3DXCOLOR(1.0f, 0.9f, 0.1f, 1.0f), 10.0f, 0.05f, 30);

					// �T�E���h�̍Đ�
					PlaySound(SOUND_LABEL_SE_COIN);
					AddScore(5000);
				}

				Player.nGetCoin++;

				// �X�e�[�W�̃N���A����
				if (Player.nGetCoin == Player.nTrueCoin)
				{
					Player.state = PLAYERSTATE_CLEAR;
				}
			}
		}
	}
}

//==============================================================================
// ���@�ւ̃_���[�W����
//==============================================================================
bool HitPlayer(int nDamage)
{
	// �_���[�W�v�Z
	Player.nLife -= nDamage;
	int nScore = GetScore();

	// �c��̗͂ɂ�鏈��
	if (Player.nLife <= 0)
	{ // ���j���ꂽ�Ƃ�
	  // �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_STOCK_LOST);

		// �X�R�A�̌��Z
		if (nScore >= 2000)
		{
			AddScore(-2000);
		}
		else if (nScore < 2000)
		{
			AddScore(-nScore);
		}

		// ���S�X�e�[�^�X��
		Player.state = PLAYERSTATE_DEATH;

		// �c�@����Ō��Ă��ꂽ�ꍇ
		if (Player.nStock >= 0)
		{
			Player.nStock--;	// �c�@�̌���
		}

		// �c�@�Ȃ��Ō��Ă��ꂽ�ꍇ
		if (Player.nStock < 0)
		{
			Player.nStock = 0;						// �c�@�̕\�����u0�v�ɕێ�
			UpdateScore();							// �X�R�A�\���̍X�V
			Player.state = PLAYERSTATE_GAMEOVER;	// �Q�[���I�[�o�[�ւ̈ڍs
		}

		return true;
	}
	else
	{ // �_���[�W���󂯂��Ƃ�
		Player.state = PLAYERSTATE_DAMAGE;	// ��_���[�W��Ԃւ̕ω�
		Player.nCounterState = 9;			// �J�E���g�̐ݒ�

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_HIT000);

		// �X�R�A�̌��Z
		if (nScore >= 2000)
		{
			AddScore(-2000);
		}
		else if (nScore < 2000)
		{
			AddScore(-nScore);
		}

		// �v���C���[�̐F�ݒ�
		Player.colorPlayer = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		return false;
	}
}

//==============================================================================
// �G�Ƃ̐ڐG
//==============================================================================
void TouchEnemy(void)
{
	// ���[�J���ϐ��錾
	ENEMY *pEnemy;

	// �G�̎擾
	pEnemy = GetEnemy();

	// �G�Ƃ̐ڐG����
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			if (Player.pos.x + PLAYER_FUTSIZEX >= pEnemy->pos.x - ENEMY_SIZEX &&
				Player.pos.x - PLAYER_FUTSIZEX <= pEnemy->pos.x + ENEMY_SIZEX &&
				Player.pos.y - PLAYER_SIZEY <= pEnemy->pos.y &&
				Player.pos.y >= pEnemy->pos.y - ENEMY_SIZEY &&
				Player.state == PLAYERSTATE_NORMAL)
			{
				// ���@�Ƃ̐ڐG����(�̗͂�1����)
				HitPlayer(1);
			}
		}
	}
}

//==============================================================================
// �v���C���[�̈ړ�
//==============================================================================
void MovePlayer(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// �v���C���[�̑���
	if (Player.bJump == false)
	{ // �W�����v�̏���
		if (GetKeyboardTrigger(KEYINFO_JUMP) == true || IsButtonDown(KEYINFO::KEYINFO_JUMP) == true || XinputPress() == true)
		{
			Player.move.y = JUMP_POWER;
			// �T�E���h�̍Đ�
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
	}

	// �v���C���[�̈ړ�
	if (GetKeyboardPress(KEYINFO_LEFT) == true || IsButtonPush(KEYINFO::KEYINFO_LEFT) == true || XinputPress(XINPUT_GAMEPAD_DPAD_LEFT) == true)
	{ // ����
		Player.move.x += sinf(D3DX_PI / -2) * SPEEDUP;
		Player.bRight = false;		// ���Ɍ���
		if (Player.bJump == false)
		{
			Player.nCntAnime++;
		}

		if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
		{// �t�ړ��ʂ̉��Z
			Player.move.x += sinf(D3DX_PI / 2) * SPEEDUP;
		}
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
	{ // �E��
		Player.move.x += sinf(D3DX_PI / 2) * SPEEDUP;
		Player.bRight = true;
		if (Player.bJump == false)
		{
			Player.nCntAnime++;
		}
	}
	else
	{ // �Î~��Ԃ̃A�j���[�V�����J�E���g
		Player.nCntAnime = 1;
		Player.fAnime = 0.0f;
	}

	// �ړ��ʂ̑��
	Player.pos.x += Player.move.x;
	Player.pos.y += Player.move.y;

	// ������̌�������(����)
	Player.move.x += (0.0f - Player.move.x) * SPEEDDOWN;

	// �d�͂̔���
	if (Player.move.y <= MAX_GRAVITY && Player.bJump == true)
	{
		Player.move.y += DROP_SPEEDUP;
	}

	// �u���b�N�Ƃ̐ڐG����
	if (CollisionBlock(
		&Player.pos, &Player.posOld,
		&Player.move, PLAYER_FUTSIZEX,
		Player.fHeight, ONTYPE_PLAYER) == false)
	{
		Player.bJump = true;
	}
	else
	{
		Player.bJump = false;
	}

	// ��ʍ��Ń��[�v(�E���ֈړ�)
	if (Player.pos.x < PLAYER_LEFT_REMIT)
	{
		Player.pos.x = PLAYER_RIGHT_REMIT;
	}

	// ��ʉE�Ń��[�v(�����ֈړ�)
	if (Player.pos.x > PLAYER_RIGHT_REMIT)
	{
		Player.pos.x = PLAYER_LEFT_REMIT;
	}

	// ��ʉ����ŗ�������
	if (Player.pos.y > 760.0f)
	{
		Player.pos = POS3_PLAYER;
		HitPlayer(1);
	}

	// ���_�o�b�t�@�����b�N����
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̒��_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(Player.pos.x - Player.fWidth, Player.pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Player.pos.x - Player.fWidth, Player.pos.y - Player.fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Player.pos.x + Player.fWidth, Player.pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Player.pos.x + Player.fWidth, Player.pos.y - Player.fHeight, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================================
// �v���C���[�̏��
//==============================================================================
void PlayerState(PLAYERSTATE state)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	int nTimer = GetTimer();	// �^�C�}�[�̎擾
	int nStage = GetStage();	// �X�e�[�W�̎擾

	// ���Ԑ؂�̎�
	if (nTimer <= 0 && state != PLAYERSTATE_CLEAR && nStage != MAX_STAGE)
	{
		Player.state = PLAYERSTATE_GAMEOVER;
	}

	switch (state)
	{
	case PLAYERSTATE_APPEAR:	// �v���C���[�o����
		Player.nCounterDisp++;				// �o����ԃJ�E���g�̑���

		if (Player.nCounterDisp % 2 == 0)
		{ // �J�E���g���Q�̔{���ŏ���
			Player.colorPlayer.a = 1.0f;	// �e���_�����x�̐ݒ�
		}
		else
		{ // ����ȊO�ł̏���
			Player.colorPlayer.a = 0.0f;	// �e���_�����x�̐ݒ�
		}

		if (Player.nCounterDisp >= APPEAR_REMIT)
		{ // �J�E���^�[�����
			Player.state = PLAYERSTATE_NORMAL;	// �ʏ펞�ւ̈ڍs
			Player.nCounterDisp = 0;			// �J�E���^�[�̃��Z�b�g
		}

		break;

	case PLAYERSTATE_DAMAGE:	// �v���C���[���_���[�W���󂯂鎞
		Player.nCounterState--;	// ��_���[�W��Ԃ̃J�E���g�̌���

		if (Player.nCounterState <= 0)
		{ // ��_���[�W��Ԃ̏I��
			Player.state = PLAYERSTATE_APPEAR;						// �ʏ��Ԃւ̈ڍs
			Player.colorPlayer = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �e���_�J���[�̐ݒ�
		}

		break;

	case PLAYERSTATE_WAIT:		// �v���C���[�̑ҋ@���
		Player.nCounterDisp++;	// �ҋ@�J�E���g�̑���

		if (Player.nCounterDisp >= WAIT_REMIT)
		{ // �ҋ@�I����
			Player.state = PLAYERSTATE_APPEAR;	// �o����Ԃֈڍs
			Player.nLife = PLAYER_LIFE;			// �̗͂̃��Z�b�g
			Player.nCounterDisp = 0;			// �J�E���g�̃��Z�b�g
		}

		break;

	case PLAYERSTATE_DEATH:		// �v���C���[�̎��S
		Player.colorPlayer.a = 0;				// �e���_�J���[�̐ݒ�
		Player.state = PLAYERSTATE_WAIT;		// �ҋ@��Ԃֈڍs

		break;

	case PLAYERSTATE_GAMEOVER:	// �Q�[���I�[�o�[
		Player.colorPlayer.a = 0;	// �e���_�J���[�̐ݒ�

		break;
	}

	// ���_�o�b�t�@�����b�N����
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�̐F�̍X�V
	pVtx[0].col = Player.colorPlayer;
	pVtx[1].col = Player.colorPlayer;
	pVtx[2].col = Player.colorPlayer;
	pVtx[3].col = Player.colorPlayer;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================================
// �v���C���[�e�N�X�`���̃A�j���[�V����
//==============================================================================
void PlayerAnim(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	float fAnime = 0.0f;
	float fRight = 0.0f;

	// �e�N�X�`�����E�̐؂�ւ�
	if (Player.bRight == false)
	{
		fRight = 0.5f;
	}
	else
	{
		fRight = 0.0f;
	}

	// �ړ����̃A�j���[�V����
	if (Player.nCntAnime % 8 == 0)
	{
		Player.fAnime += 1.0f;	// �e�N�X�`���̕ω�
	}

	// �W�����v��Ԃ̃A�j���[�V�����Œ�
	if (Player.bJump == true)
	{
		Player.fAnime = 1.0f;
	}

	// ���_�o�b�t�@�����b�N����
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����_���̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (Player.fAnime * 0.25f), 0.5f + fRight);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (Player.fAnime * 0.25f), 0.0f + fRight);
	pVtx[2].tex = D3DXVECTOR2(0.25f + (Player.fAnime * 0.25f), 0.5f + fRight);
	pVtx[3].tex = D3DXVECTOR2(0.25f + (Player.fAnime * 0.25f), 0.0f + fRight);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//==============================================================================
// �X�e�[�W���Ƃ̃v���C���[�̏����z�u
//==============================================================================
void SetPlayer(void)
{
	// ���[�J���ϐ��錾
	int nStage = GetStage();

	// �X�e�[�W���Ƃ̏����z�u
	switch (nStage)
	{
	case 0:	// �X�e�[�W1
		Player.pos = POS1_PLAYER;
		Player.posOld = POS1_PLAYER;

		break;

	case 1:	// �X�e�[�W2
		Player.pos = POS2_PLAYER;
		Player.posOld = POS2_PLAYER;

		break;

	case 2:	// �X�e�[�W3
		Player.pos = POS3_PLAYER;
		Player.posOld = POS3_PLAYER;

		break;

	default:
		break;
	}
}