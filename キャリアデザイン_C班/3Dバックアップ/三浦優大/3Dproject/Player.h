#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//===================
//�v���C���[�̏��
//===================
typedef enum
{
	PLAYERSTATE_NOMAL = 0,//�ʏ펞
	PLAYERSTATE_DAMAGE,//�_���[�W���
	PLAYERSTATE_MUTEKI,//���G���
	PLAYERSTATE_FIRE,//�΂̏��
	PLAYERSTATE_FREAZ,//�X�̏��
	PLAYERSTATE_STAR,
	PLAYERSTATE_MAX
}PLAYERSTATE;

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 oldPos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int g_nCounterAnim;//�A�j���[�V����
	int g_nPatternAnim;//�A�j���[�V����
	int g_nseetAnim;//�A�j���[�V����
	PLAYERSTATE state;//���
	int nCounterState;//��ԃJ�E���^�[
	int nCounterStateStar;
	int nType;//���
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
	float g_fLengthPlayer;//�Ίp���̒���
	float g_fAnglePlayer;//�Ίp���̊p�x
}PLAYER;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitPlayer(void);//����������
void UninitPlayer(void);//�I������
void UpdatePlayer(void);//�X�V����
void DrawPlayer(void);//�`�揈��
#endif
