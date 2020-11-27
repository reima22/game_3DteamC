//==============================================================================
//
// �E�B���h�E�\���̏����kmain.cpp�l
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include "meshfield.h"
#include "meshwall.h"
#include <stdio.h>
#include <string.h>
//#include "player.h"
//#include "bg.h"
//#include "block.h"
//#include "enemy.h"
//#include "item.h"
//#include "score.h"
//#include "fade.h"
//#include "title.h"
//#include "tutorial.h"
//#include "game.h"
//#include "result.h"
//#include "ranking.h"
//#include "sound.h"
//#include "gamepad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define CLASS_NAME		"WindowClass"	// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"3DAction"	// �E�B���h�E�̖��O

//==============================================================================
// �v���g�^�C�v�錾
//==============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// �E�B���h�E�v���V�[�W��
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);							// ����������
void Uninit(void);		// �I������
void Update(void);		// �X�V����
void Draw(void);		// �`�揈��
void DrawFPS(void);		// FPS�̕`�揈��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3D9 g_pD3D = NULL;				// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	// Direct3D�f�o�C�X�ւ̃|�C���^(�`�揈���ɕK�v)
LPD3DXFONT g_pFont = NULL;				// �t�H���g�ւ̃|�C���^
int g_nCountFPS;						// FPS�J�E���^
MODE g_mode = MODE_TITLE;				// �Q�[�����[�h

//==============================================================================
// ���C���֐�
//==============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ϐ��錾
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		("%s",CLASS_NAME),					// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;	// �������s�ŏI����
	DWORD dwFPSLastTime;	// FPS�v���ŏI����
	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwFrameCount;		// �t���[���J�E���g

	dwExecLastTime =
	dwFPSLastTime = 
	dwCurrentTime = timeGetTime();
	dwFrameCount = 0;

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);	// �E�B���h�E�̑傫���𒲐�����

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindowEx(
		0,
		("%s", CLASS_NAME),		// �E�B���h�E�N���X�̖��O
		("%s", WINDOW_NAME),	// �E�B���h�E�̖��O(�L���v�V����)
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,			// �E�B���h�E�̍���X���W
		CW_USEDEFAULT,			// �E�B���h�E�̍���Y���W
		rect.right,				// �X�N���[���̕�
		rect.bottom,			// �X�N���[���̍���
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while(1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// ���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{ // windows�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{ // DirectX�̏���
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{ // 0.5�b�o��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;		// �l�̍X�V
				dwFrameCount = 0;					// �J�E���g�N���A
			}

			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �I������
	Uninit();

	// �E�B���h�E�N���X�̓o�^����
	UnregisterClass(
		("%s", CLASS_NAME),		// �E�B���h�E�N���X�̖��O
		wcex.hInstance);

	return (int)msg.wParam;
}

//==============================================================================
// �E�B���h�E�v���V�[�W��
//==============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ���[�J���ϐ��錾
	int nID;		// ���b�Z�[�W�ւ̉�

	// �E�B���h�E�̓��e
	switch (uMsg)
	{
	case WM_CLOSE:	// �E�B���h�E�����
		// ���b�Z�[�W�{�b�N�X�̕\���ƑI��
		nID = MessageBox(NULL, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION);
		if (nID == IDYES)
		{ // ���b�Z�[�W[�͂�]��I��
			DestroyWindow(hWnd);	// WM_DESTROY���b�Z�[�W��Ԃ�
		}
		else
		{ // ���b�Z�[�W[������]��I��
			return 0;				// �������p��
		}
		break;

	case WM_DESTROY:			// ���b�Z�[�W�̔j��
		PostQuitMessage(0);		// WM_QUIT���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:			// �L�[���͂̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:			// ESC�L�[����
			// ���b�Z�[�W�{�b�N�X�̕\���ƑI��
			nID = MessageBox(NULL, "�I�����܂����H", "�m�F", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
			if (nID == IDYES)
			{ // ���b�Z�[�W[�͂�]��I��
				DestroyWindow(hWnd);	// WM_DESTROY���b�Z�[�W��Ԃ�
			}
			else
			{ // ���b�Z�[�W[������]��I��
				return 0;				// �������p��
			}
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//==============================================================================
// ����������
//==============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ���[�J���ϐ��錾
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// �f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	// Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{ // �`�揈��:�n�[�h�E�F�A�A���_����:�n�[�h�E�F�A�ł̏������s
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{ // �`�揈��:�\�t�g�E�F�A�A���_����:�n�[�h�E�F�A�ł̏������s
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{ // �`�揈��:�\�t�g�E�F�A�A���_����:�\�t�g�E�F�A�ł̏������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�(�e�N�X�`���w�i(�|���S���{�̂̐F)�̓��߂Ȃ�)
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);		// �k�����@���
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);		// �g�厞�@���
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_WRAP);		// U�l�@�J��Ԃ�
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_WRAP);		// V�l�@�J��Ԃ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);	// �A���t�@�l�̍���	
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_CURRENT);

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(
		g_pD3DDevice,20,0,0,0,FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);

	// ���͂̏���������
	InitKeyboard(hInstance, hWnd);

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// �e�̏���������
	InitShadow();

	// �|���S���̏���������
	InitPolygon();

	// ���b�V���t�B�[���h�̏�����
	InitMeshfield();

	// �ǂ̏���������
	InitWall();

	// ���b�V���ǂ̏���������
	InitMeshwall();

	SetWall(D3DXVECTOR3(0.0f, -5.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, 5.0f);
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 100.0f, 50.0f);
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI / -2, 0.0f), 100.0f, 50.0f);
	//SetWall(D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100.0f, 50.0f);

	// ���f���̏���������
	InitModel();

	// �r���{�[�h�̏�����
	InitBillboard();

	//// �p�b�h���͂̏���������
	//InitGamepad(hInstance, hWnd);

	//// �T�E���h�Đ��̏���������
	//InitSound(hWnd);

	//// ���[�h�̐ݒ�
	//SetMode(g_mode);

	//// �t�F�[�h�̏���������
	//InitFade(g_mode);
	
	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void Uninit(void)
{
	//// �T�E���h�Đ��̏I������
	//UninitSound();

	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	//// �t�F�[�h�̏I������
	//UninitFade();

	// �|���S���̏I������
	UninitPolygon();

	// ���b�V���t�B�[���h�̏I������
	UninitMeshfield();

	// �ǂ̏I������
	UninitWall();

	// ���b�V���ǂ̏I������
	UninitMeshwall();

	// ���f���̏I������
	UninitModel();

	// �r���{�[�h�̏I������
	UninitBillboard();

	// �e�̏I������
	UninitShadow();

	// �t�H���g�̊J��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	// Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// ���͂̏I������
	UninitKeyboard();

	//// �p�b�h���͂̏I������
	//UninitGamepad();
}

//==============================================================================
// �X�V����
//==============================================================================
void Update(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// ���͂̍X�V����
	UpdateKeyboard();

	//// �p�b�h���͂̍X�V����
	//UpdateGamepad();

	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	// �r���{�[�h�̍X�V����
	UpdateBillboard();

	//// ���[�h�̐ݒ�
	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	// �^�C�g����ʂ̍X�V����
	//	UpdateTitle();
	//	break;

	//case MODE_TUTORIAL:
	//	// �`���[�g���A����ʂ̍X�V����
	//	UpdateTutorial();
	//	break;

	//case MODE_GAME:
	//	// �Q�[����ʂ̍X�V����
	//	UpdateGame();
	//	break;

	//case MODE_RESULT:
	//	// ���U���g��ʂ̍X�V����
	//	UpdateResult();
	//	break;

	//case MODE_RANKING:
	//	// �����L���O��ʂ̍X�V����
	//	UpdateRanking();
	//	break;

	//default:
	//	break;
	//}

	//// �t�F�[�h�̍X�V����
	//UpdateFade();

	// �|���S���̍X�V����
	UpdatePolygon();

	// ���b�V���t�B�[���h�̍X�V����
	UpdateMeshfield();

	// �ǂ̍X�V����
	UpdateWall();

	// ���b�V���ǂ̍X�V����
	UpdateMeshwall();

	// ���f���̍X�V����
	UpdateModel();

	// �e�̍X�V����
	UpdateShadow();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A(��ʂ̃N���A)
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	// �`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//switch (g_mode)
		//{
		//case MODE_TITLE:
		//	// �^�C�g����ʂ̕`�揈��
		//	DrawTitle();
		//	break;

		//case MODE_TUTORIAL:
		//	// �`���[�g���A����ʂ̕`�揈��
		//	DrawTutorial();
		//	break;

		//case MODE_GAME:
		//	// �Q�[����ʂ̕`�揈��
		//	DrawGame();
		//	break;

		//case MODE_RESULT:
		//	// ���U���g��ʂ̕`�揈��
		//	DrawResult();
		//	break;

		//case MODE_RANKING:
		//	// �����L���O��ʂ̕`�揈��
		//	DrawRanking();
		//	break;

		//default:
		//	break;
		//}

		// �|���S���̕`�揈��
		DrawPolygon();

		// ���b�V���t�B�[���h�̕`�揈��
		DrawMeshfield();

		// �ǂ̕`�揈��
		DrawWall();

		// ���b�V���ǂ̕`�揈��
		DrawMeshwall();

		// ���f���̕`�揈��
		DrawModel();

		// �e�̕`�揈��
		DrawShadow();

		// �r���{�[�h�̕`�揈��
		DrawBillboard();

		//// �t�F�[�h�̕`�揈��
		//DrawFade();

		// �f�o�b�O���[�h�̎�
		#ifdef _DEBUG

		// FPS�̕`�揈��
		DrawFPS();

		DrawT();

		#endif

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//==============================================================================
// FPS�̕`�揈��
//==============================================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];
	int nNum;
	Camera camera = GetCamera();

	nNum = sprintf(&aStr[0], "FPS:%d\n",g_nCountFPS);
	nNum += sprintf(&aStr[nNum], " (���_)  X:%.2f Y:%.2f Z:%.2f\n", camera.posV.x, camera.posV.y, camera.posV.z);
	nNum += sprintf(&aStr[nNum], " (�����_)X:%.2f Y:%.2f Z:%.2f\n", camera.posR.x, camera.posR.y, camera.posR.z);
	nNum += sprintf(&aStr[nNum], "���f���̈ړ��F[ �� �� �� �� ]\n");
	nNum += sprintf(&aStr[nNum], "���f���ʒu���Z�b�g�FENTER\n�J�����ʒu���Z�b�g�FSPACE\n");

	// �e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//==============================================================================
// �f�o�C�X�̎擾
//==============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//==============================================================================
// ���[�h�̐ݒ�
//==============================================================================
void SetMode(MODE mode)
{
	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	// �^�C�g����ʂ̏I������
	//	UninitTitle();
	//	break;

	//case MODE_TUTORIAL:
	//	// �`���[�g���A����ʂ̏I������
	//	UninitTutorial();
	//	break;

	//case MODE_GAME:
	//	// �Q�[����ʂ̏I������
	//	UninitGame();
	//	break;

	//case MODE_RESULT:
	//	// ���U���g��ʂ̏I������
	//	UninitResult();
	//	break;

	//case MODE_RANKING:
	//	// �����L���O��ʂ̏I������
	//	UninitRanking();
	//	break;

	//default:
	//	break;
	//}
	// 
	//switch (mode)
	//{
	//case MODE_TITLE:
	//	// �^�C�g����ʂ̏���������
	//	InitTitle();

	//	// �X�e�[�W�J�E���g�̏�����
	//	InitGameCnt();

	//	// �X�R�A�̏���������
	//	InitScore();

	//	break;

	//case MODE_TUTORIAL:
	//	// �`���[�g���A����ʂ̏���������
	//	InitTutorial();
	//	break;

	//case MODE_GAME:
	//	// �Q�[����ʂ̏���������
	//	InitGame();
	//	break;

	//case MODE_RESULT:
	//	// ���U���g��ʂ̏���������
	//	InitResult();
	//	break;

	//case MODE_RANKING:
	//	// �����L���O��ʂ̏���������
	//	InitRanking();
	//	break;

	//default:
	//	break;
	//}

	//g_mode = mode;
}

//==============================================================================
// ���[�h�̎擾
//==============================================================================
MODE GetMode(void)
{
	return g_mode;
}

// �e�L�X�g�`��
void DrawT(void)
{
	//RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//char aStr[512];

	//Camera camera = GetCamera();

	////int nNum;

	//sprintf(&aStr[0], "FPS:%d\n",g_nCountFPS);

	//// �e�L�X�g�̕`��
	//g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));
}