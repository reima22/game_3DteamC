//==============================================================================
//
// �I���J�[�\���̕`��kselect_cursor.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _SELECT_CURSOR_H_
#define _SELECT_CURSOR_H_
#include "main.h"

typedef enum
{
	CURSORTYPE_PLAYER1 = 0,
	CURSORTYPE_PLAYER2,
	CURSORTYPE_CPU,
	CURSORTYPE_MAX
}CURSORTYPE;

typedef enum
{
	CURSORSTATE_NORMAL = 0,		// �ʏ�
	CURSORSTATE_BLINK,			// �_��
	CURSORSTATE_ERASE,			// ����
	CURSORSTATE_MAX
}CURSORSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fHeight;			// ����
	bool bUse;				// �g�p���
	CURSORTYPE cursorType;	// �J�[�\���̎��
	int nCntBlink;			// �J�[�\���̓_�ŃJ�E���g
	CURSORSTATE state;		// �J�[�\���̏��
}CursorInfo;

typedef struct
{
	CursorInfo cursor[CURSORTYPE_MAX];
	int nMoveStartCnt;
	bool bBlinkEnd;			// �_�ŏ�ԏI��
	int nCharNum;			// �L�����I����
}Cursor;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitCursor(void);			// �I���J�[�\���̏���������
void UninitCursor(void);			// �I���J�[�\���̏I������
void UpdateCursor(void);			// �I���J�[�\���̍X�V����
void DrawCursor(void);				// �I���J�[�\���̕`�揈��
void SetVertexCursor(int nIdx);		// ���_���X�V
void CursorManager(void);			// �J�[�\���̐���
Cursor GetCursorS(void);			// �I���J�[�\���̎擾
void CursorState(void);				// �J�[�\���̏��

#endif