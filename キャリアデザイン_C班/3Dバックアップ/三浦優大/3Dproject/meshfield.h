#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

//�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 Pos;//�ʒu
	D3DXVECTOR3 oldPos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	int g_nCounterAnim;//�A�j���[�V����
	int g_nPatternAnim;//�A�j���[�V����
	int g_nseetAnim;//�A�j���[�V����
	//PLAYERSTATE state;//���
	int nCounterState;//��ԃJ�E���^�[
	int nCounterStateStar;
	int nType;//���
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
	float g_fLengthPlayer;//�Ίp���̒���
	float g_fAnglePlayer;//�Ίp���̊p�x
}MESHFIELD;

//===============
//�v���g�^�C�v�錾
//===============
HRESULT InitMeshfield(void);//����������
void UninitMeshfield(void);//�I������
void UpdateMeshfield(void);//�X�V����
void DrawMeshfield(void);//�`�揈��
#endif
