#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>

#include "d3dx9.h"//�`�揈���ɕK�v

#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"//���͏����ɕK�v
#include "xaudio2.h"

//���C�u�����̃����N
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment (lib,"xinput.lib")


//�}�N����`
#define CLASS_NAME "WindowClass"//�E�B���h�E�̃N���X�̖��O
#define WINDOW_NAME "WARNING"//�E�B���h�E�̖��O
#define ID_BUTTON000 (101)//�{�^����ID
#define ID_EDIT000 (111)//�G�f�B�b�g��ID
#define WINDOW_POS_X (40)//
#define WINDOW_POS_Y (40)//
#define ID_TIMER (121)//
#define TIMER_INTERVAL (1000/1)
#define LOOP_PLAYER (3)//
#define SCREEN_WIDTH (1920)//��ʂ̕�
#define SCREEN_HEIGHT (1080)//��ʂ̍���
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//���[�h�̎��
//typedef enum
//{
//	MODE_TITLE = 0,
//	MODE_GAME,
//	MODE_TUTOLIAL,
//	MODE_RESULT,
//	MODE_GAME2,
//	MODE_RANKING,
//	MODE_MAX
//}MODE;

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);

//=============
//�\���̂̒�`
//=============
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

#endif