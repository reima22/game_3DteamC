//==============================================================================
//
// �E�B���h�E�̕\��(main.h)
// Author : Mare Horiai
//
//==============================================================================
#pragma once
#include <windows.h>
#include "d3dx9.h"						// �`�揈���ɕK�v
#define DIRECTINPUT_VERSION	(0x0800)
#include "dinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"					// �T�E���h�Đ��ɕK�v 

//==============================================================================
// ���C�u�����̃����N
//==============================================================================
#pragma comment(lib, "d3d9.lib")	// �`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	// �g�����C�u����
#pragma comment(lib, "dxguid.lib")	// �R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib, "dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib, "winmm.lib")

//==============================================================================
// �}�N����`
//==============================================================================
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	// ���_�t�H�[�}�b�g
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_WIDTH	(1280)		// ��ʂ̕�
#define SCREEN_HEIGHT	(720)		// ��ʂ̍���
#define SPEEDDOWN		(0.2f)		// �����W��
#define SCREEN_CENTERX	(640)		// ��ʂ̒���X��
#define SCREEN_CENTERY	(360)		// ��ʂ̒���Y��

//#define POS1_PLAYER		(D3DXVECTOR3(40.0f,300.0f,0.0f))	// �X�e�[�W1�̃v���C���[�̃X�^�[�g�ʒu
//#define POS2_PLAYER		(D3DXVECTOR3(40.0f,660.0f,0.0f))	// �X�e�[�W2�̃v���C���[�̃X�^�[�g�ʒu
//#define POS3_PLAYER		(D3DXVECTOR3(50.0f,660.0f,0.0f))	// �X�e�[�W3�̃v���C���[�̃X�^�[�g�ʒu
//#define MAX_LIFE		(3)			// �̗͂̍ő�l
//#define SPEEDUP			(1.0f)		// �ړ��̉����x
//#define JUMP_POWER		(20.0f)	// �W�����v��s
//#define DROP_SPEEDUP	(1.4f)		// �����̉����x
//#define MAX_GRAVITY		(30.0f)		// �d�͂̍ő�l
//#define GRAVITY_ENEMY	(25.0f)		// �G�̏d�͂̍ő�l
//#define ENEMY_SIZEX		(20)		// �G�̕�
//#define ENEMY_SIZEY		(40)		// �G�̍���
//#define COIN_SCORE		(5000)		// �R�C���̃X�R�A
//#define REDCOIN_SCORE	(54000)		// �n�C�X�R�A�R�C���̃X�R�A
//#define TIME_BONUS		(2000)		// 1�J�E���g������̃^�C���{�[�i�X�X�R�A
//#define BONUS_STAGE1	(150000)	// �X�e�[�W1�̃m�[�_���[�W�{�[�i�X�X�R�A
//#define BONUS_STAGE2	(100000)	// �X�e�[�W2�̃m�[�_���[�W�{�[�i�X�X�R�A
//#define BONUS_STAGE3	(300000)	// �X�e�[�W3�̃m�[�_���[�W�{�[�i�X�X�R�A
//#define DAMAGE_SCORE	(10000)		// ��_���[�W���̌����X�R�A

//==============================================================================
// ���_�t�H�[�}�b�g�ɍ��킹���\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// 1.0�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

//==============================================================================
// ���[�h�̎��
//==============================================================================
typedef enum
{
	MODE_TITLE = 0,	// �^�C�g�����
	MODE_TUTORIAL,	// �`���[�g���A�����
	MODE_GAME,		// �Q�[�����
	MODE_RESULT,	// ���U���g���
	MODE_RANKING,	// �����L���O���
	MODE_MAX
}MODE;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawT(void);