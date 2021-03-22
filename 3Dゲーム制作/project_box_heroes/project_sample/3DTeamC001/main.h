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
#define FOUR_POINT		(4)			// �����蔻���4�_
#define PLUS_GRAVITY	(0.6f)		// ���Z�����d�͒l
#define MAX_LIFE		(5)			// �̗͂̍ő�l
#define TEXT_LENGTH		(128)	// �e�L�X�g�ǂݍ��݂̍ő吔
#define DATA_LENGTH		(64)	// �f�[�^�ǂݍ��݂̍ő吔
#define TITLE_BGM		(true)		// �^�C�g��BGM�̃I���E�I�t
#define GAME_BGM		(true)		// �Q�[��BGM�̃I���E�I�t
#define RESULT_BGM		(true)		// ���U���gBGM�̃I���E�I�t
#define RANKING_BGM		(true)		// �����L���OBGM�̃I���E�I�t
#define VTX_MINP		(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// �����_�ŏ��l
#define	VTX_MAXP		(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// �����_�ő�l

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
	MODE_SELECT,	// �Z���N�g���
	MODE_TUTORIAL,	// �`���[�g���A�����
	MODE_GAME,		// �Q�[�����
	MODE_RESULT,	// ���U���g���
	MODE_MAX
}MODE;

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);
void DrawT(void);