//==============================================================================
//
// �X�R�A�̕`��kbullet_ui.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _BULLET_UI_H_
#define _BULLET_UI_H_
#include "main.h"

// �}�N����`
#define MAX_BULLET_UI	(8)
#define MAX_UI_NUM		(3)
#define TEX_BULLET_UI	(2)

typedef struct
{
	D3DXVECTOR3 posLogo;
	D3DXVECTOR3 posNum[MAX_UI_NUM];
	int nBullet;
}BulletUI;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitBulletUI(void);						// �e��UI�̏���������
void UninitBulletUI(void);						// �e��UI�̏I������
void UpdateBulletUI(void);						// �e��UI�̍X�V����
void DrawBulletUI(void);						// �e��UI�̕`�揈��
//void AddScore(int nValue);					// �e��UI�̉��Z����
void SetVertexBulletUI(int nIdx, int nNumber,
int nCnt);	// �e��UI�̍��W���擾
//int GetScore(void);							// �e��UI���̎擾

#endif