//-----------------------------------------------------------------------------
//
// ���f���`��̏���
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//���f���\����
typedef struct
{
	LPD3DXMESH pMesh = NULL;			//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;		//�}�e���A���i�ގ����j�ւ̃|�C���^
	DWORD nNumMat;						//�}�e���A���̐�
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 rot;					//����
	int nIdxModelParent;				//�e���f���̃C���f�b�N�X
}Model;

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_NUTRAL = 0,		//�j���[�g�������[�V����
	MOTIONTYPE_MAX,
}MOTIONTYPE;

//�L�[�̍\����
typedef struct
{
	float PosX;		//�ʒuX
	float PosY;		//�ʒuY
	float PosZ;		//�ʒuZ
	float RotX;		//����X
	float RotY;		//����Y
	float RotZ;		//����Z
}KEY;

//�L�[���̍\����
typedef struct
{
	int Frame;		//�Đ��t���[��
	KEY aKey[14];	//�e���f���̃L�[�v�f
}KEY_INFO;

//���[�V�������̍\����
typedef struct
{
	bool bLoop;				//���[�v���邩�ǂ���
	int nNumKey;			//�L�[�̑���
	KEY_INFO aKeyInfo[8]	//�L�[�̏��
}MOTION_INFO;

//�v���C���[�̍\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X

	Model aModel[14];					//���f���i�p�[�c�j
	int nNumModel= 14;					//���f���i�p�[�c�j��

	MOTION_INFO aMotionInfo[5];			//���[�V�������
	int nNumMotion;						//���[�V�����̑���
	MOTIONTYPE MotionType;				//���[�V�����^�C�v
	bool bLoopMotion;					//���[�v���邩�ǂ���
	int nNumKey;						//�L�[��
	int nKey;							//�L�[No.
	int nCounterMotion;					//���[�V�����J�E���^�[

}Player;

//�v���g�^�C�v�錾
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetMotion(int nNumKey, int nType, bool bLoop);
Player *GetPlayer(void);

#endif _PLAYER_H_