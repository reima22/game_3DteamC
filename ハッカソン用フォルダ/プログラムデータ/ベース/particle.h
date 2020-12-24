//==============================================================================
//
// �p�[�e�B�N���̕`��kparticle.h�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _PARTICLE_H_
#define _PARTICLE_H_
#include "main.h"

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
HRESULT InitParticle(void);		// �p�[�e�B�N���̏���������
void UninitParticle(void);		// �p�[�e�B�N���̏I������
void UpdateParticle(void);		// �p�[�e�B�N���̍X�V����
void DrawParticle(void);		// �p�[�e�B�N���̕`�揈��
void SetEffect(					// �G�t�F�N�g�̐ݒ�
	D3DXVECTOR3 pos,			// �ʒu
	float fMove,				// �ړ���
	D3DXCOLOR color,			// �F�E�����x
	float fRadius,				// ���a
	float fAlphaDown,			// ���ߓx
	int nEffect);				// �G�t�F�N�g�̌�

#endif