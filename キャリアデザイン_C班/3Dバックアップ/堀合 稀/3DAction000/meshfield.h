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

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitMeshfield(void);	// 3D�|���S���̏���������
void UninitMeshfield(void);		// 3D�|���S���̏I������
void UpdateMeshfield(void);		// 3D�|���S���̍X�V����
void DrawMeshfield(void);		// 3D�|���S���̕`�揈��

#endif
