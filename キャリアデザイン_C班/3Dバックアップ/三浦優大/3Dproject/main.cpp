#define _CRT_SECURE_NO_WARNINGS
//======================
//
//Windows�̏���[main.cpp]
//Author:miura
//======================

#include "main.h"
#include "Player.h"
#include "camera.h"
#include "light.h"
#include "xinput.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "input.h"
#include "stdio.h"
#include "Billboard.h"
#include "meshfield.h"

//================
//�v���g�^�C�v�錾
//================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawTEXT(void);

//===============
//�O���[�o���ϐ�
//===============
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS;
int nCount = 0;
//MODE g_mode = MODE_TITLE;
//float g_Camera;
//float g_Camera;

//==========
//���C���֐�
//==========
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DWORD dwExecLastTime;//�������s�ŏI����
	DWORD dwFPSLastTime;//FPS�v���ŏI����
	DWORD dwCurrentTime;//���ݎ���
	DWORD dwFrameCount;//�t���[���J�E���g

	dwExecLastTime =
		dwFPSLastTime =
		dwCurrentTime = timeGetTime();
	dwFrameCount = 0;
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_EXCLAMATION),
		LoadCursor(NULL,IDC_HAND),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_EXCLAMATION),
	};
	HWND hWnd;
	MSG msg;
	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);
	//�E�B���h�E�̍쐬
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		WINDOW_NAME,//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right-rect.left,
		rect.bottom-rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
				if ((dwCurrentTime-dwExecLastTime) > (1000/60))
				{
					dwExecLastTime = dwCurrentTime;

					//�X�V����
					Update();
					//�`�揈��
					Draw();

					dwFrameCount++;
				}
		}

	}
	//�I������
	Uninit();
	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass(
		CLASS_NAME,//�E�B���h�E�N���X�̖��O
		wcex.hInstance);
	return (int)msg.wParam;
}
//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	switch (uMsg)
	{
	case WM_DESTROY://�E�B���h�E��j������
		PostQuitMessage(0);//WM_QUIT���b�Z�[�W��Ԃ�
		break;
	case WM_CREATE:
		SetTimer(hWnd, ID_TIMER, TIMER_INTERVAL, NULL);
		break;
	case WM_TIMER:
		//�����̈�������I�ɔ���������
		InvalidateRect(hWnd, &rect, FALSE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON000)
		{
			nID = MessageBox(hWnd, "�I�����܂����H", "�{���ɁH", MB_YESNOCANCEL | MB_ICONASTERISK);
			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
		}
		break;

	default:
		break;

	case WM_CLOSE://�~�{�^���Ŋm�F�\��
		nID = MessageBox(NULL, "�I�����܂����H", "�{���ɁH", MB_YESNOCANCEL | MB_ICONASTERISK);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);//YES�����������
		}
		else
		{
			return 0;//����ȊO�̓E�B���h�E�͕��Ȃ�
		}
		break;
	}
		switch (wParam)
		{

		case WM_KEYDOWN://�L�[�������Ƃ��̃��b�Z�[�W
			break;

		case VK_UP:
			//�����̈�������I�ɔ���������
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_RIGHT:
		
			//�����̈�������I�ɔ���������
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_ESCAPE://�G�X�P�[�v�L�[�ŕ\��
			DestroyWindow(hWnd);
			break;

		default:
			break;
		}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//==========
//����������
//==========
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	
	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//�f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�[�̐ݒ�
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

	//Direct3D�f���@�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice
	)))
	{	
		if (FAILED(g_pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice
		)))
		{
			if (FAILED(g_pD3D->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice
			)))
			{
				return E_FAIL;
			}
		}
	}

	//���[�h�̐ݒ�
	//SetMode(MODE_TITLE);

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DXCreateFont(g_pD3DDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);
	MODEL *pModel;
	pModel = GetModel();

	InitMeshfield();
	//InitPlayer();
	InitBillboard();
	InitLight();
	InitCamera();
	InitModel();
	InitWall();
	SetWall(D3DXVECTOR3(0.0f, 75.0f, 25.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//SetWall(D3DXVECTOR3(0.0f, 75.0f, 25.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	
	InitShadow();
	InitKeyboard(hInstance, hWnd);
	
	
	//InitFade(g_mode);
	//g_Camera = 0.0f;

	
	return S_OK;
}
//========
//�I������
//========
void Uninit(void)
{	
	UninitKeyboard();
	UninitMeshfield();
	//UninitPlayer();
	UninitBillboard();
	UninitCamera();
	UninitLight();
	UninitModel();
	UninitShadow();
	UninitWall();


	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	
if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	
}

//=========
//�X�V����
//=========
void Update(void)
{
	UpdateKeyboard();
	UpdateLight();
	UpdateCamera();
	UpdateMeshfield();
	//UpdatePlayer();
	UpdateModel();
	UpdateShadow();
	UpdateWall();
	UpdateBillboard();

	//nCount++;
	Camera *pCamera;
	pCamera = GetCamera();
	MODEL *pModel;
	pModel = GetModel();
	
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
	}
	else
	{
		// Controller is not connected
	}


	// Zero value if thumbsticks are within the dead zone
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}

	if ((state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}
	
	//if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)

}

//=========
//�`�揈��
//=========
void Draw(void)
{
	//�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A�i��ʂ̃N���A�j
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{	
		SetCamera();
		DrawMeshfield();
		DrawModel();
		//DrawPlayer();
		DrawShadow();
		DrawWall();
		DrawBillboard();
		DrawFPS();
		DrawTEXT();
		//�`��̏I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void DrawFPS(void)
{
	char aStr[256];
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_BOTTOM, D3DCOLOR_RGBA(255, 255, 255, 255));
}


LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

void DrawTEXT(void)
{
	Camera *pCamera;
	pCamera = GetCamera();
	MODEL *pModel;
	pModel = GetModel();

	char aStr[456];
	int nNum = sprintf(&aStr[0], "PosR.x:%.2f\n", pCamera->PosR.x);
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	nNum += sprintf(&aStr[nNum], "PosR.y:%.2f\n", pCamera->PosR.y);
	nNum += sprintf(&aStr[nNum], "PosR.z:%.2f\n", pCamera->PosR.z);
	nNum += sprintf(&aStr[nNum], "PosV.x:%.2f\n", pCamera->PosV.x);
	nNum += sprintf(&aStr[nNum], "PosV.y:%.2f\n", pCamera->PosV.y);
	nNum += sprintf(&aStr[nNum], "PosV.z:%.2f\n", pCamera->PosV.z);
	nNum += sprintf(&aStr[nNum], "rot.y:%.2f\n", pCamera->rot.y);
	nNum += sprintf(&aStr[nNum], "Model.Pos.x:%.2f\n", pModel->Pos.x);
	nNum += sprintf(&aStr[nNum], "Model.Pos.z:%.2f\n", pModel->Pos.z);
	nNum += sprintf(&aStr[nNum], "Model.Move.x:%.2f\n", pModel->move.x);
	nNum += sprintf(&aStr[nNum], "Model.Move.z:%.2f\n", pModel->move.z);
	nNum += sprintf(&aStr[nNum], "Model.rot.y:%.2f\n", pModel->rot.y);
	nNum += sprintf(&aStr[nNum], "Model.rot.y:%.2f\n", pModel->rot.y);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 255, 255));
}




