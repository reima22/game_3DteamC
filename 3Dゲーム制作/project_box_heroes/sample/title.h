//==============================================================================
//
// �^�C�g����ʂ̕`��ktitle.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"

//==============================================================================
// �G���^�[�T�C���̏��
//==============================================================================
typedef enum
{
	ENTERSIGN_NORMAL = 0,	// �\�����
	ENTERSIGN_NONE,			// ��\�����
	ENTERSIGN_ACTIVE,		// �L�[���͎��̓_��
	ENTERSIGN_MOVE,			// �T�C���̈ړ�
	ENTERSIGN_MAX
} ENTERSIGN;

//==============================================================================
// �����J�ڂ̏��
//==============================================================================
typedef enum
{
	TITLE_NONE = 0,	// �������Ȃ�
	TITLE_AUTO,		// �����J��
	TITLE_MAX
} TITLEAUTO;

//==============================================================================
// �^�C�g���̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 posTitle;			// �^�C�g����ʂ̈ʒu
	D3DXVECTOR3 posTitlelogo;		// �^�C�g�����S�̈ʒu
	D3DXVECTOR3 posTitleEnter[2];	// �G���^�[�T�C���̈ʒu
	D3DXCOLOR colSign;				// �G���^�[�T�C���̐F�E�����x
	ENTERSIGN Sign;					// �G���^�[�T�C���̏��
	TITLEAUTO titleauto;			// ������ʑJ�ڂ̏��
	int nCntMoveLogo;				// ���S�̈ړ��J�E���^�[
	int nSignAppear;				// �G���^�[�T�C���o���J�E���g
	int nMoveSign;					// �G���^�[�T�C���̈ړ��J�E���^�[
	int nSignCounter;				// �G���^�[�T�C���̓_�ŃJ�E���^�[
	int nShiftCount;				// ������ʑJ�ڂւ̃J�E���^�[
}TITLE;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitTitle(void);	// �^�C�g����ʂ̏���������
void UninitTitle(void);		// �^�C�g����ʂ̏I������
void UpdateTitle(void);		// �^�C�g����ʂ̍X�V����
void DrawTitle(void);		// �^�C�g����ʂ̕`�揈��
TITLE GetTitle(void);		// �^�C�g���̏��
void EnterSign(void);		// �G���^�[�T�C���̏��

#endif