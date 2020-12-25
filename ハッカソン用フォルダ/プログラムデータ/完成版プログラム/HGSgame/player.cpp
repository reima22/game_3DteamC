//==============================================================================
//
// �v���C���[�̕`��kplayer.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "player.h"
#include "score.h"
#include "input.h"
#include "bullet.h"
#include "item.h"
#include "fade.h"
#include "sound.h"
#include "particle.h"
#include "gamepad.h"
#include "block.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define PLAYER_UP_REMIT		(90)	// �v���C���[�ړ��̏���E
#define PLAYER_DOWN_REMIT	(700)	// �v���C���[�ړ��̉����E
#define PLAYER_LEFT_REMIT	(20)	// �v���C���[�ړ��̍����E
#define PLAYER_RIGHT_REMIT	(1260)	// �v���C���[�ړ��̉E���E
#define APPEAR_REMIT		(80)	// �o����ԃJ�E���^�[���
#define WAIT_REMIT			(30)	// �ҋ@��ԃJ�E���^�[���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// �v���C���[�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// �o�b�t�@�ւ̃|�C���^
PLAYER Player;										// �v���C���[�̏��
int g_nShotCount;									// �e���ˊԊu

//==============================================================================
// �v���C���[�̏���������
//==============================================================================
HRESULT InitPlayer(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	Player.state = PLAYERSTATE_NORMAL;
	Player.colorPlayer = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Player.nCounterDisp = 0;
	Player.nCounterState = 0;
	Player.nLife = PLAYER_LIFE;
	Player.nStock = PLAYER_STOCK;
	Player.nLineOver = 0;
	Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Player.fLength = sqrtf(PLAYER_SIZEX * PLAYER_SIZEX + PLAYER_SIZEY * PLAYER_SIZEY);
	Player.fAngle = atan2f(PLAYER_SIZEX, PLAYER_SIZEY);
	Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCnt = 0; nCnt < BULLET_PLUS; nCnt++)
	{
		Player.aBullet[nCnt] = false;
	}
	g_nShotCount = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/player001.png",
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

	// �v���C���[�̒��S���W
	Player.pos = D3DXVECTOR3(POSPLAYERX, POSPLAYERY, 0.0f);

	// �v���C���[�̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(Player.pos.x + sinf(-Player.fAngle) * Player.fLength, Player.pos.y + cosf(-Player.fAngle) * Player.fLength, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Player.pos.x + sinf(Player.fAngle - D3DX_PI) * Player.fLength, Player.pos.y + cosf(Player.fAngle - D3DX_PI) * Player.fLength, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Player.pos.x + sinf(Player.fAngle) * Player.fLength, Player.pos.y + cosf(Player.fAngle) * Player.fLength, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Player.pos.x + sinf(-Player.fAngle + D3DX_PI) * Player.fLength, Player.pos.y + cosf(-Player.fAngle + D3DX_PI) * Player.fLength, 0.0f);
	
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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

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
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	
	if (Player.state == PLAYERSTATE_NORMAL)
	{ // �u�[�X�^�[�p�[�e�B�N���̐ݒ�
		SetEffect(D3DXVECTOR3(Player.pos.x, Player.pos.y + 25.0f, 0.0f), 0.009f, D3DXCOLOR(0.2f, 0.4f, 0.9f, 1.0f), 3.0f, 0.1f);
	}

	// �G�Ƃ̐ڐG��
	TouchBlock();

	// �v���C���[�̃A�C�e���擾
	//ItemGet();

	// �v���C���[�̑���
	PlayerMove();

	// �v���C���[�̏��
	switch (Player.state)
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
		Player.colorPlayer.a = 0;								// �e���_�J���[�̐ݒ�
		Player.pos = D3DXVECTOR3(POSPLAYERX, POSPLAYERY, 0.0f);	// �z�u�ʒu�̃��Z�b�g
		Player.state = PLAYERSTATE_WAIT;						// �ҋ@��Ԃֈڍs

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

	// �|���S���̒��_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(Player.pos.x + sinf(-Player.fAngle + Player.rot.z) * Player.fLength, Player.pos.y + cosf(-Player.fAngle + Player.rot.z) * Player.fLength, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Player.pos.x + sinf(Player.fAngle - D3DX_PI + Player.rot.z) * Player.fLength, Player.pos.y + cosf(Player.fAngle - D3DX_PI + Player.rot.z) * Player.fLength, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Player.pos.x + sinf(Player.fAngle + Player.rot.z) * Player.fLength, Player.pos.y + cosf(Player.fAngle + Player.rot.z) * Player.fLength, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Player.pos.x + sinf(-Player.fAngle + D3DX_PI + Player.rot.z) * Player.fLength, Player.pos.y + cosf(-Player.fAngle + D3DX_PI + Player.rot.z) * Player.fLength, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
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
// ���@�ւ̖����ƃ_���[�W����
//==============================================================================
bool HitPlayer(int nDamage)
{
	// ���[�J���ϐ��錾
	int nScore = GetScore();

	// �_���[�W�v�Z
	Player.nLife -= nDamage;

	// �c��̗͂ɂ�鏈��
	if (Player.nLife <= 0)
	{ // ���j���ꂽ�Ƃ�
		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_EXPLOSION003);

		// �G�t�F�N�g�̔���
		SetEffect(Player.pos, 0.3f, D3DXCOLOR(0.2f, 0.4f, 0.9f, 1.0f), 15.0f, 0.015f);

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
			Player.state = PLAYERSTATE_GAMEOVER;	// �Q�[���I�[�o�[�ւ̈ڍs
		}

		return true;
	}
	else
	{ // �_���[�W���󂯂��Ƃ�
		Player.state = PLAYERSTATE_DAMAGE;	// ��_���[�W��Ԃւ̕ω�
		Player.nCounterState = 9;			// �J�E���g�̐ݒ�

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_HIT001);

		// �p�[�e�B�N���̐ݒ�
		SetEffect(Player.pos, 0.05f, D3DXCOLOR(0.1f, 0.4f, 0.9f, 1.0f), 3.0f, 0.015f);

		// �v���C���[�̐F�ݒ�
		Player.colorPlayer = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		return false;
	}
}

//==============================================================================
// �ǂƂ̐ڐG
//==============================================================================
void TouchBlock(void)
{
	// ���[�J���ϐ��錾
	BLOCK *pBlock;

	// �ǂ̎擾
	pBlock = GetBlock();

	// �G�Ƃ̐ڐG����
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++, pBlock++)
	{
		if (pBlock->bUse == true)
		{
			if (Player.pos.x + PLAYER_SIZEX >= pBlock->pos.x - BLOCK_SIZEX &&
				Player.pos.x - PLAYER_SIZEX <= pBlock->pos.x + BLOCK_SIZEX &&
				Player.pos.y - PLAYER_SIZEY <= pBlock->pos.y + BLOCK_SIZEY &&
				Player.pos.y + PLAYER_SIZEY >= pBlock->pos.y - BLOCK_SIZEY &&
				Player.state == PLAYERSTATE_NORMAL)
			{
				// ���@�Ƃ̐ڐG����(�̗͂�1����)
				HitPlayer(1);
			}
		}
	}
}

//==============================================================================
// �A�C�e�����菈��
//==============================================================================
//void ItemGet(void)
//{
//	// ���[�J���ϐ��錾
//	ITEM *pItem;
//
//	// �A�C�e���̎擾
//	pItem = GetItem();
//
//	// ���@�ƃA�C�e���̐ڐG
//	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++, pItem++)
//	{
//		if (Player.pos.x + PLAYER_SIZEX >= pItem->pos.x - ITEM_SIZEX &&
//			Player.pos.x - PLAYER_SIZEX <= pItem->pos.x + ITEM_SIZEX &&
//			Player.pos.y - PLAYER_SIZEY <= pItem->pos.y + ITEM_SIZEY &&
//			Player.pos.y + PLAYER_SIZEY >= pItem->pos.y - ITEM_SIZEY)
//		{
//			if (pItem->bUse == true)
//			{ // �A�C�e���o����
//				for (int nCntBullet = 0; nCntBullet < BULLET_PLUS; nCntBullet++)
//				{
//					if (pItem->nType == nCntBullet)
//					{ // �A�C�e���̎�ނɂ���Ď擾���镐���̔���
//						if (Player.aBullet[nCntBullet] == false)
//						{ // �ǉ��e�̎擾
//							Player.aBullet[nCntBullet] = true;
//						}
//					}
//				}
//
//				// �A�C�e���|���S���̏���
//				pItem->bUse = false;
//
//				// �T�E���h�̍Đ�
//				PlaySound(SOUND_LABEL_SE_ITEM000);
//
//				// �X�R�A�̒ǉ�
//				AddScore(5000);
//			}
//		}
//	}
//}

//==============================================================================
// �v���C���[�̑��쏈��
//==============================================================================
void PlayerMove(void)
{
	// ���[�J���ϐ��錾
	//SETBULLET State;

	// �e�̑��U���̎擾
	//State = GetState();

	// �ړ��ʂ̑��
	Player.pos.x += Player.move.x;
	Player.pos.y += Player.move.y;

	// �|���S���̒��S���W�̍X�V�i�ʏ�ړ��j
	if (Player.state == PLAYERSTATE_NORMAL || Player.state == PLAYERSTATE_DAMAGE || Player.state == PLAYERSTATE_APPEAR)
	{
		if (GetKeyboardPress(KEYINFO_UP) == true || IsButtonPush(KEYINFO::KEYINFO_UP) == true)
		{ // ���
			Player.move.y += cosf(D3DX_PI) * SPEEDUP;

			if (GetKeyboardPress(KEYINFO_LEFT) == true || IsButtonPush(KEYINFO::KEYINFO_LEFT) == true)
			{
				Player.move.x += sinf(D3DX_PI / -2) * SPEEDUP;
			}
			else if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
			{
				Player.move.x += sinf(D3DX_PI / 2) * SPEEDUP;
			}
			else if (GetKeyboardPress(KEYINFO_DOWN) == true || IsButtonPush(KEYINFO::KEYINFO_DOWN) == true)
			{
				Player.move.y += cosf(0.0f) * SPEEDUP;
			}
		}
		else if (GetKeyboardPress(KEYINFO_DOWN) == true || IsButtonPush(KEYINFO::KEYINFO_DOWN) == true)
		{ // ����
			Player.move.y += cosf(0.0f) * SPEEDUP;

			if (GetKeyboardPress(KEYINFO_LEFT) == true || IsButtonPush(KEYINFO::KEYINFO_LEFT) == true)
			{
				Player.move.x += sinf(D3DX_PI / -2) * SPEEDUP;
			}
			else if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
			{
				Player.move.x += sinf(D3DX_PI / 2) * SPEEDUP;
			}
		}
		else if (GetKeyboardPress(KEYINFO_LEFT) == true || IsButtonPush(KEYINFO::KEYINFO_LEFT) == true)
		{ // ����
			Player.move.x += sinf(D3DX_PI / -2) * SPEEDUP;

			if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
			{
				Player.move.x += sinf(D3DX_PI / 2) * SPEEDUP;
			}
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
		{ // �E��
			Player.move.x += sinf(D3DX_PI / 2) * SPEEDUP;
		}
	}

	// �X�y�[�X�L�[����(�e�̔���)
	if (Player.state == PLAYERSTATE_NORMAL || Player.state == PLAYERSTATE_DAMAGE || Player.state == PLAYERSTATE_APPEAR)
	{
		if (g_nShotCount == 0)
		{
			if (GetKeyboardPress(KEYINFO_SHOT) == true || IsButtonPush(KEYINFO::KEYINFO_SHOT) == true)
			{
				g_nShotCount = 20;

				// ���̍Đ�
				PlaySound(SOUND_LABEL_SE_SHOT001);

				// �e�̐ݒ�
				SetBullet(Player.pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), 100);
			}
		}
		else if (g_nShotCount > 0)
		{
			g_nShotCount--;
		}
	}

	// ������̌�������
	Player.move.x += (0.0f - Player.move.x) * SPEEDDOWN;
	Player.move.y += (0.0f - Player.move.y) * SPEEDDOWN;

	// ��ʏ㕔���E�Œ�~
	if (Player.pos.y <= PLAYER_UP_REMIT)
	{
		Player.pos.y = PLAYER_UP_REMIT;
	}

	// ��ʉ������E�Œ�~
	if (Player.pos.y >= PLAYER_DOWN_REMIT)
	{
		Player.pos.y = PLAYER_DOWN_REMIT;
	}

	// ��ʍ����E�Œ�~
	if (Player.pos.x <= PLAYER_LEFT_REMIT)
	{
		Player.pos.x = PLAYER_LEFT_REMIT;
	}

	// ��ʉE���E�Œ�~
	if (Player.pos.x >= PLAYER_RIGHT_REMIT)
	{
		Player.pos.x = PLAYER_RIGHT_REMIT;
	}
}