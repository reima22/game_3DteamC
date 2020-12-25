//==============================================================================
//
// �v���C���[�̕`��kplayer.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define PATTERNANIM		(5.0f)	// �A�j���[�V�����p�^�[����
#define BULLET_PLUS		(3)		// �ǉ��e�̐�
#define PLAYER_LIFE		(3)		// �v���C���[�̃��C�t�l
#define PLAYER_SIZEX	(20)	// �v���C���[�̕�
#define PLAYER_FUTSIZEX	(10)	// �v���C���[�̑����̕�
#define PLAYER_SIZEY	(60)	// �v���C���[�̍���

//==============================================================================
// �v���C���[�̏��
//==============================================================================
typedef enum
{
	PLAYERSTATE_APPEAR = 0,	// �o��
	PLAYERSTATE_NORMAL,		// �ʏ�
	PLAYERSTATE_DAMAGE,		// �_���[�W
	PLAYERSTATE_WAIT,		// �o���҂�
	PLAYERSTATE_DEATH,		// ���S
	PLAYERSTATE_CLEAR,		// �Q�[���N���A
	PLAYERSTATE_GAMEOVER,	// �Q�[���I�[�o�[
	PLAYERSTATE_MAX
} PLAYERSTATE;

//==============================================================================
// �v���C���[�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// ���݂̈ʒu
	D3DXVECTOR3 posOld;			// �O��̈ʒu
	D3DXVECTOR3 move;			// �v���C���[�̈ړ���
	float fWidth;				// ��
	float fHeight;				// ����
	int nLife;					// �v���C���[�̗̑�
	int nStock;					// �v���C���[�̎c�@
	PLAYERSTATE state;			// �v���C���[�̏��
	int nCounterState;			// ��ԕω����̃J�E���g
	int nCounterDisp;			// �_�ŏ�Ԃ̃J�E���g
	D3DXCOLOR colorPlayer;		// �v���C���[�̐F�E�����x
	int nCntAnime;				// �A�j���[�V�����J�E���g
	bool bRight;				// ���E�̌�������
	float fAnime;				// �v���C���[�̃A�j���[�V�����J��
	bool bJump;					// �󒆂ɂ��邩�ǂ���
	int nGetCoin;				// �R�C���̊l����
	int nTrueCoin;				// �N���A�ɕK�v�ȃR�C����
} PLAYER;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitPlayer(void);				// �v���C���[�̏���������
void UninitPlayer(void);				// �v���C���[�̏I������
void UpdatePlayer(void);				// �v���C���[�̍X�V����
void DrawPlayer(void);					// �v���C���[�̕`�揈��
PLAYER *GetPlayer(void);				// �v���C���[�̏��̎擾
void ItemGet(void);						// �A�C�e���Ƃ̓����蔻��
bool HitPlayer(int nDamage);			// ��_���[�W�̏���
void TouchEnemy(void);					// �G�Ƃ̐ڐG�̏���
void MovePlayer(void);					// �v���C���[�̈ړ�
void PlayerState(PLAYERSTATE state);	// �v���C���[�̏��
void PlayerAnim(void);					// �v���C���[�̃e�N�X�`���A�j���[�V����
void SetPlayer(void);					// �X�e�[�W���Ƃ̃v���C���[�̏����z�u

#endif