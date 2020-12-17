//==============================================================================
//
// 3D���f���̕`��kplayer.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

// �}�N����`
#define MODEL_PARTS		(14)

// ���f���̍\����
typedef struct
{
	LPD3DXMESH pMeshModel;		// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel;	// �}�e���A���ւ̃|�C���^
	DWORD nNumMatModel;			// �}�e���A���̐�
	D3DXVECTOR3 pos;			// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nIdxModelParent;		// �e���f���̃C���f�b�N�X
}Model;

// �v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	int nIdx;
	Model aModel[MODEL_PARTS];		// ���f��(�p�[�c)
	int nNumModel;			// ���f��(�p�[�c)��
} Player;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitPlayer(void);	// 3D���f���̏���������
void UninitPlayer(void);		// 3D���f���̏I������
void UpdatePlayer(void);		// 3D���f���̍X�V����
void DrawPlayer(void);		// 3D���f���̕`�揈��
Player *GetPlayer(void);		// 3D���f���̎擾

#endif