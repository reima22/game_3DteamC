//-----------------------------------------------------------------
//
// HP�o�[�̏��� (hp.h)
// Author:shouta takahashi
//
//-----------------------------------------------------------------
#ifndef _HP_H_
#define _HP_H_
#include "main.h"

//-----------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------
#define MAXTEX_UI	(8)
#define MAX_TEX_UI	(4)					// �e�N�X�`���ő吔
#define UI_WIDTH	(640.0f)			// ��
#define UI_HEIGHT	(100.0f)			// ����
#define UI_HARF_W	(UI_WIDTH / 2.0f)	// ���T�C�Y����
#define UI_HARF_H	(UI_HEIGHT / 2.0f)	// �����T�C�Y����
#define HP_LIMIT	(400.0f)			// �ő�HP

//-----------------------------------------------------------------------------
// HP�̊��蓖��
//-----------------------------------------------------------------------------
typedef enum
{
	PLAYER_0 = 0,	// �v���C���[1
	PLAYER_1,		// �v���C���[2
	PLAYER_MAX
}HP_Player;

//-----------------------------------------------------------------------------
// HP�o�[�̍\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 posFrame;
	D3DXVECTOR3 posBar;
	HP_Player hp;			// �ǂ���̃v���C���[��
	float fBar;				// �o�[�̕\����
}HP;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitHp(void);		// HP�o�[�̏���������
void UninitHp(void);		// HP�o�[�̏I������
void UpdateHp(void);		// HP�o�[�̍X�V����
void DrawHp(void);			// HP�o�[�̕`�揈��
void SetVertexHp(int nIdx);	// HP�o�[�̒��_���W�X�V
void CalcuHp(				// HP�̉����Z����
	int nHp,				// �v���C���[�̎��
	float fValue,			// ���l
	bool bPlus);			// ���Z�E���Z�̋��
HP *GetHp(void);			// HP���̎擾

#endif
