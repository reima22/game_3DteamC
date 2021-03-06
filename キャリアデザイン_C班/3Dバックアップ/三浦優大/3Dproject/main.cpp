#define _CRT_SECURE_NO_WARNINGS
//======================
//
//Windowsの処理[main.cpp]
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
//プロトタイプ宣言
//================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawTEXT(void);

//===============
//グローバル変数
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
//メイン関数
//==========
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	DWORD dwExecLastTime;//処理実行最終時刻
	DWORD dwFPSLastTime;//FPS計測最終時刻
	DWORD dwCurrentTime;//現在時刻
	DWORD dwFrameCount;//フレームカウント

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
		CLASS_NAME,//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_EXCLAMATION),
	};
	HWND hWnd;
	MSG msg;
	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);
	//ウィンドウの作成
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, TRUE);
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,//ウィンドウクラスの名前
		WINDOW_NAME,//ウィンドウの名前
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

//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//メッセージループ
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
				//メッセージの翻訳と送出
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

					//更新処理
					Update();
					//描画処理
					Draw();

					dwFrameCount++;
				}
		}

	}
	//終了処理
	Uninit();
	//ウィンドウクラスの登録解除
	UnregisterClass(
		CLASS_NAME,//ウィンドウクラスの名前
		wcex.hInstance);
	return (int)msg.wParam;
}
//ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	switch (uMsg)
	{
	case WM_DESTROY://ウィンドウを破棄する
		PostQuitMessage(0);//WM_QUITメッセージを返す
		break;
	case WM_CREATE:
		SetTimer(hWnd, ID_TIMER, TIMER_INTERVAL, NULL);
		break;
	case WM_TIMER:
		//無効領域を強制的に発生させる
		InvalidateRect(hWnd, &rect, FALSE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_BUTTON000)
		{
			nID = MessageBox(hWnd, "終了しますか？", "本当に？", MB_YESNOCANCEL | MB_ICONASTERISK);
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

	case WM_CLOSE://×ボタンで確認表示
		nID = MessageBox(NULL, "終了しますか？", "本当に？", MB_YESNOCANCEL | MB_ICONASTERISK);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);//YESだったら閉じる
		}
		else
		{
			return 0;//それ以外はウィンドウは閉じない
		}
		break;
	}
		switch (wParam)
		{

		case WM_KEYDOWN://キー押したときのメッセージ
			break;

		case VK_UP:
			//無効領域を強制的に発生させる
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_RIGHT:
		
			//無効領域を強制的に発生させる
			InvalidateRect(hWnd, &rect, FALSE);
			break;

		case VK_ESCAPE://エスケープキーで表示
			DestroyWindow(hWnd);
			break;

		default:
			break;
		}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//==========
//初期化処理
//==========
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	
	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//ディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメーターの設定
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

	//Direct3Dデヴァイスの生成
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

	//モードの設定
	//SetMode(MODE_TITLE);

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
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
//終了処理
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

	//Directオブジェクトの開放
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
//更新処理
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
//描画処理
//=========
void Draw(void)
{
	//バックバッファ&Zバッファのクリア（画面のクリア）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f,
		0);

	//描画の開始
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
		//描画の終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void DrawFPS(void)
{
	char aStr[256];
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
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

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 255, 255));
}




