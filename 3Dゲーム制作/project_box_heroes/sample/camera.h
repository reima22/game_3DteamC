//==============================================================================
//
// �J�����̐ݒ�kcamera.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "main.h"

#define CAMERA_MAX		(2)					// �J�����̍ő吔

//==============================================================================
// �J�����̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 posV;			// ���݂̎��_
	D3DXVECTOR3 posVDest;		// �ړI�̎��_
	D3DXVECTOR3 posR;			// ���݂̒����_
	D3DXVECTOR3 posRDest;		// �ړI�̒����_
	D3DXVECTOR3 vecU;			// ������x�N�g��
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	D3DXVECTOR3 move;			// �ړ���
	D3DXVECTOR3 rot;			// �J�����̊p�x
	float fLength;				// ���_�E�����_�Ԃ̋���
	float fHeightV;				// ���_�̍���
	float fHeightR;				// �����_�̍���
	float fFront;				// ���f���̑O���̋���
	bool bAutoTurn;				// �J�����̉�荞��ON�EOFF
	D3DVIEWPORT9 viewport;		// �r���[�|�[�g
} Camera;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
void InitCamera(void);		// �J�����̏���������
void UninitCamera(void);	// �J�����̏I������
void UpdateCamera(void);	// �J�����̍X�V����
void SetCamera(int nIdx);	// �J�����̐ݒ�
Camera *GetCamera(void);		// �J�����̎擾
void CameraInfo(int nIdx);		// �J�����̏��
void MoveCamera(int nCnt);		// �J�����̑���

#endif
