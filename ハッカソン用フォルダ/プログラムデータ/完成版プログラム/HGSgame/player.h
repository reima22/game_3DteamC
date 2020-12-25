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
#define PLAYER_LIFE		(1)		// �v���C���[�̃��C�t�l
#define PLAYER_STOCK	(0)		// �����c�@��
#define PLAYER_SIZEX	(20)	// �v���C���[�̕�
#define PLAYER_SIZEY	(20)	// �v���C���[�̍���

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
	PLAYERSTATE_GAMEOVER,	// �Q�[���I�[�o�[
	PLAYERSTATE_MAX
} PLAYERSTATE;

//==============================================================================
// �v���C���[�̃X�e�[�^�X
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXCOLOR colorPlayer;		// �F
	int nLife;					// �̗�
	PLAYERSTATE state;			// ���
	int nCounterState;			// ��ԃJ�E���g
	int nCounterDisp;			// �_�ŃJ�E���g
	int nStock;					// �c�@
	bool aBullet[BULLET_PLUS];	// �ǉ��e�ۗ̕L���
	int nLineOver;				// ���C���z���J�E���g
	D3DXVECTOR3 rot;			// �v���C���[�̉�]�p
	float fLength;				// �v���C���[�̑Ίp���̒���
	float fAngle;				// �v���C���[�̑Ίp���̊p�x
	D3DXVECTOR3 move;			// �v���C���[�̈ړ���
} PLAYER;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitPlayer(void);		// �v���C���[�̏���������
void UninitPlayer(void);		// �v���C���[�̏I������
void UpdatePlayer(void);		// �v���C���[�̍X�V����
void DrawPlayer(void);			// �v���C���[�̕`�揈��
PLAYER *GetPlayer(void);		// �v���C���[�̏��̎擾
bool HitPlayer(int nDamage);	// �v���C���[�̓����蔻��
void TouchBlock(void);			// �ǂƂ̐ڐG
//void ItemGet(void);			// �A�C�e���̓���
void PlayerMove(void);			// �v���C���[�̍s��

#endif