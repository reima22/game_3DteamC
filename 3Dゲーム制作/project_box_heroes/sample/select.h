//==============================================================================
//
// �I����ʂ̕`��kselect.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _SELECT_H_
#define _SELECT_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define BG_NUM		(1)			// �w�i��
#define MODE_NUM	(2)			// ���[�h�̎�ސ�
#define CHARA_NUM	(3)			// �L�����̎�ސ�
#define STAGE_NUM	(3)			// �X�e�[�W�̎�ސ�
#define ALL_SET		(32)	// �z�u�ő吔
#define ALL_TEX		(16)	// �e�N�X�`���ő�
#define SELECT_MOVE	(10.0f)	// �Z���N�g��ʂ̃|���S���ړ���

//==============================================================================
// ���[�h�I���
//==============================================================================
typedef enum
{
	PLAYMODE_0 = 0,
	PLAYMODE_1,
	PLAYMODE_MAX
}PlayMode;

//==============================================================================
// �L�����I���
//==============================================================================
typedef enum
{
	CHARA_0 = 0,
	CHARA_1,
	CHARA_2,
	CHARA_MAX
}Chara;

//==============================================================================
// �X�e�[�W�I���
//==============================================================================
typedef enum
{
	STAGE_0 = 0,
	STAGE_1,
	STAGE_2,
	STAGE_MAX
}Stage;

//==============================================================================
// �I���p�^�[��
//==============================================================================
typedef enum
{
	SELECTTYPE_MODE = 0,	// �v���C���[�h
	SELECTTYPE_CHARA,		// �L�����N�^�[
	SELECTTYPE_STAGE,		// �X�e�[�W
	SELECTTYPE_MAX
}SelectType;

//==============================================================================
// �e�N�X�`���p�^�[��
//==============================================================================
typedef enum
{
	ST_BG = 0,	// �w�i
	ST_MODE,	// ���[�h�I��
	ST_CHARA,	// �L�����I��
	ST_STAGE,	// �X�e�[�W�I��
	ST_MAX
}SelectTex;

//==============================================================================
// �I����ʏڍׂ̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 move;			// �ړ���
	D3DXCOLOR col;				// �F
	float fWidth;				// ��
	float fHeight;				// ����
	int nType;					// �e�N�X�`���̃^�C�v��
	SelectTex st;				// �g�p�����p�^�[��
	char aFileName[64];			// �t�@�C����
	bool bUse = false;			// �g�p���
}SelectInfo;

//==============================================================================
// �I����ʂ̍\����
//==============================================================================
typedef struct
{
	SelectInfo selectInfo[ALL_SET];	// �I����ʏ��
	int nNumTexSelect;				// �g�p�e�N�X�`����
	int nNumSelect;					// �|���S����
	int nCntPage;					// �I����ʃJ�E���g
	bool bMove;						// �ړ����
	bool bBack;						// �I���L�����Z��
	int nMoveCnt;					// �ړ��J�E���g
	PlayMode mode;					// �I�����[�h�̎��
	Chara chara[2];					// �I���L�����̎��
	bool bDecide[2];				// �L�����I������
	Stage stage;					// �I���X�e�[�W�̎��
	int nCntAnim;					// �I����ʂ̃A�j���[�V����
	SelectType SType;				// �ǂ̑I����
	bool b2PlayerOn;				// 2P���L��
}Select;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitSelect(void);			// �I����ʂ̏���������
void UninitSelect(void);			// �I����ʂ̏I������
void UpdateSelect(void);			// �I����ʂ̍X�V����
void DrawSelect(void);				// �I����ʂ̕`�揈��
void SelectManager(void);			// �I����ʂ̊Ǘ�
void TexSetSelect(void);			// �e�N�X�`���̐ݒ�
void LoadSelect(void);				// �e�L�X�g���[�h
void SetVertexSelect(int nIdx);		// ���_���X�V
void SelectCursor(SelectType ST);	// �I���J�[�\������
Select *GetSelect(void);			// �I�����̎擾

#endif