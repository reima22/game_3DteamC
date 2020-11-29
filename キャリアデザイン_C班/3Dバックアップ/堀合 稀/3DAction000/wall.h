//==============================================================================
//
// �ǂ̕`��kwall.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

// �}�N����`
#define MAX_WALL	(4)		// �ǂ̍ő吔
#define WALL_WIDTH	(50.0f)	// �W���l
#define WALL_HEIGHT	(50.0f)	// �W���l

// �ǂ̍\����
typedef struct
{
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 pos;
	D3DXVECTOR3	posMove;
	D3DXVECTOR3 rot;
	float fWidth;
	float fHeight;
	bool bUse;
} Wall;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitWall(void);	// �ǂ̏���������
void UninitWall(void);	// �ǂ̏I������
void UpdateWall(void);	// �ǂ̍X�V����
void DrawWall(void);	// �ǂ̕`�揈��
void SetWall(			// �ǂ̐ݒ�
D3DXVECTOR3 pos,			// �ʒu
D3DXVECTOR3 rot,			// ����
float fWidth,				// ��
float fHeight);				// ����

#endif
