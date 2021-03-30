//==============================================================================
//
// ���b�V���t�B�[���h�̕`��kmeshfield.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_
#include "main.h"

// ���b�V���t�B�[���h�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// �p�x
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	bool bUse;				// �g�p���Ă��邩
	int nAllPoint;			// �����_��
	int nPolygon;			// �|���S����
	int nIdxPoint;			// �C���f�b�N�X�o�b�t�@�̕K�v�Ȋm�ې�
	float fWidth;			// �|���S���������̕�
	float fDepth;			// �|���S���������̉��s
	int nWidth;				// �����̒��_��
	int nDepth;				// ���s�̒��_��
	float fWidthMax;		// �����̍ő�
	float fDepthMax;		// ���s�̍ő�
}MeshField;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshfield(void);	// 3D�|���S���̏���������
void UninitMeshfield(void);		// 3D�|���S���̏I������
void UpdateMeshfield(void);		// 3D�|���S���̍X�V����
void DrawMeshfield(void);		// 3D�|���S���̕`�揈��
void SetField(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 rot,
	int nWidth,
	int nDepth,
	float fWidth,
	float fDepth);

void SetTex(int nStage);

#endif
