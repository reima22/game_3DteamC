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

//==============================================================================
// �}�N����`
//==============================================================================
#define MODEL_PARTS		(14)	// ���f���p�[�c�̍ő吔
#define MAX_KEY			(8)		// �L�[���̍ő吔
#define FRAME_NUM		(50)	// �t���[���̍ő吔

//==============================================================================
// ���[�V�����̎��
//==============================================================================
typedef enum
{
	MOTIONTYPE_NEUTRAL = 0,	// �j���[�g�������[�V����
	MOTIONTYPE_MOVE,		// �ړ����[�V����
	MOTIONTYPE_MAX			// ���[�V�����̍ő吔
} MOTIONTYPE;

//==============================================================================
// �L�[�̍\����
//==============================================================================
typedef struct
{
	float fPosX;	// �ʒuX
	float fPosY;	// �ʒuY
	float fPosZ;	// �ʒuZ
	float fRotX;	// ����X
	float fRotY;	// ����Y
	float fRotZ;	// ����Z
} KEY;

//==============================================================================
// �L�[���̍\����
//==============================================================================
typedef struct
{
	int nFrame;				// �Đ��t���[��			
	KEY aKey[MODEL_PARTS];	// �e���f���̃L�[�v�f 
} KEY_SET;

//==============================================================================
// ���[�W�������̍\����
//==============================================================================
typedef struct
{
	bool bLoop;				// ���[�v���邩
	int nNumKey;			// �L�[�̑���
	KEY_SET aKeySet[10];	// �L�[���
} MOTION_INFO;

//==============================================================================
// ���f���̍\����
//==============================================================================
typedef struct
{
	LPD3DXMESH pMeshModel;		// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMatModel;	// �}�e���A���ւ̃|�C���^
	DWORD nNumMatModel;			// �}�e���A���̐�
	D3DXVECTOR3 pos;			// �ʒu(�I�t�Z�b�g)
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nIdxModelParent;		// �e���f���̃C���f�b�N�X
	char aFileName[128];		
}Model;

//==============================================================================
// �v���C���[�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 posOld;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rotDest;
	int nIdx;
	Model aModel[MODEL_PARTS];					// ���f��(�p�[�c)
	int nNumModel/* = MODEL_PARTS*/;			// ���f��(�p�[�c)��
	MOTION_INFO aMotionInfo[MOTIONTYPE_MAX];	// ���[�V�������
	int nNumMotion = MOTIONTYPE_MAX;			// ���[�V������
	MOTIONTYPE motionType;						// ���[�V�����^�C�v
	bool bLoopMotion;							// ���[�v���邩�ǂ���
	int nNumKey;								// �L�[��
	int nKey;									// �L�[��
	int nCounterMotion;							// ���[�V�����̃J�E���^�[
} Player;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitPlayer(void);	// �v���C���[�̏���������
void UninitPlayer(void);	// �v���C���[�̏I������
void UpdatePlayer(void);	// �v���C���[�̍X�V����
void DrawPlayer(void);		// �v���C���[�̕`�揈��
Player *GetPlayer(void);	// �v���C���[�̎擾
void SetMotion(MOTIONTYPE motionType);		// ���[�V�����̐ݒ� 
void UpdateMotion(MOTIONTYPE motionType);	// ���[�V�����̍X�V
void LoadMotion(void);						// .txt�t�H���_�̓ǂݍ���

#endif