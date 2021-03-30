//==============================================================================
//
// ���b�V���O�Ղ̕`��kmeshorbit.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_
#include "main.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_ORBIT	(2)		// �O�Ղ̍ő吔
#define MESH_MAIN	(2)		// ����_��
#define MESHPOINT	(20)	// ���_�ő吔

//==============================================================================
// ���b�V���\���O�Ղ̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 rot;						// �p�x
	//D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	//bool bUse;							// �g�p���Ă��邩

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX *pMtxParent;					// �e�̃}�g���b�N�X�̃|�C���^
	D3DXVECTOR3 aOffset[MESH_MAIN];			// ���[�̃I�t�Z�b�g
	D3DXCOLOR aCol[MESH_MAIN];				// ���[�̊�̐F
	D3DXMATRIX aMtxWorldPoint[MESH_MAIN];	// ���[�̃��[���h�}�g���b�N�X
	D3DXVECTOR3 aPosPoint[MESHPOINT];		// ���[�̊e���_���W
	D3DXCOLOR aColPoint[MESHPOINT];			// ���[�̊e���_�J���[
}MeshOrbit;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshOrbit(void);	// ���b�V���\���̋O�Ղ̏���������
void UninitMeshOrbit(void);		// ���b�V���\���̋O�Ղ̏I������
void UpdateMeshOrbit(void);		// ���b�V���\���̋O�Ղ̍X�V����
void DrawMeshOrbit(void);		// ���b�V���\���̋O�Ղ̕`�揈��
void SetMeshOrbit(				// ���b�V���\���̋O�Ղ̐ݒ�
	D3DXVECTOR3 pos0,			// �I�t�Z�b�g0�̈ʒu
	D3DXVECTOR3 pos1,			// �I�t�Z�b�g1�̈ʒu
	D3DXCOLOR col0,				// ��F0
	D3DXCOLOR col1);			// ��F1
MeshOrbit GetOrbit(void);

#endif