//-----------------------------------------------------------------------------
//
// ダイレクトｘの処理
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "input.h"
#include "polygon.h"
#include "meshfild.h"
#include "meshwall.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "wall.h"
#include "billboard.h"
#include <stdio.h>

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);
void DrawTxt(void);

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3D9 g_pD3D = NULL;							//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;				//Direct3Dディバイスへのポインタ
LPD3DXFONT g_pFont = NULL;							//フォントへのポインタ
int g_nCountFPS;									//FPSカウンタ			

//-----------------------------------------------------------------------------
//メイン関数
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hlnstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	//構造体の設定(ウィンドウになげるやつ)
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
		CLASS_NAME,
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;
	MSG msg;
	//ウィンドウの登録
	RegisterClassEx(&wcex);

	//ウィンドウを生成(作ったウィンドウをウィンドウハンドルに納めて監理する)
	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//初期化処理(ウィンドウを生成してから行う)(DirectX本体からの生成を行っている)
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return-1;
	}
	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);                                     //ウィンドウの表示(ウィンドウの表示状態を設定)
	UpdateWindow(hWnd);                                             //ウィンドウの反映(ウィンドウのクライアント領域を更新)
																	//メッセージグループ(メッセージキューからメッセージを取得)
	DWORD dwExecLastTime = 0;
	DWORD dwFPSLastTime = 0;
	DWORD dwCurrentTime = timeGetTime();
	DWORD dwFrameCount = 0;

	while (1)                                                       //メッセージを取得しなかったら0を返す
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)          //メッセージを取得しなかったら0を返す
		{
			//windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;                                              //"WM_QUIT"メッセージが送られてきたらループを抜ける
			}
			else
			{
				//メッセージの翻訳と送出
				TranslateMessage(&msg);                             //仮想キーメッセージを文字メッセージへ変更
				DispatchMessage(&msg);                              //ウィンドウプロシージャメッセージを送出
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) > (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				//DirectXの処理
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

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}//←メイン終了のかっこ

 //-----------------------------------------------------------------------------
 //ウィンドプロシージャ
 //-----------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;
	switch (uMsg)
	{
		//ウィンドウ破棄のメッセージ
	case WM_DESTROY:
		//WM_QUITメッセージを返す
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		//
		nID = MessageBox(hWnd, "終了しますか？？", "終了？", MB_YESNO);
		if (nID == IDYES)
		{
			//ウィンドウを破棄する(WM_DESTROYメッセージを送る
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: //[ESC]キーが押された
			DestroyWindow(hWnd);
			break;
		}
	}

	//規定の処理を返す
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;                                 //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;                         //プレゼンテーションパラメータ
														 //Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;               //エラーが出る
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//初期化部分
	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	D3DXCreateFont(g_pD3DDevice, 25, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Teminal", &g_pFont);

	//キーボードの初期化処理
	InitKeyboard(hInstance, hWnd);

	//メッシュフィールドの初期化処理
	InitMeshifild();

	//メッシュの壁の初期化処理
	InitMeshwall();

	//壁の初期化処理
	InitWall();

	//モデルの初期化処理
	InitModel();

	//ビルボードの初期化処理
	InitBillboard();

	//影の初期化処理
	InitShadow();

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	return S_OK;
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void Uninit(void)
{
	//キーボードの終了処理
	UninitKeyboard();

	//ライトの終了処理
	UninitLight();

	//カメラの終了処理
	UninitCamera();

	//影の終了処理
	UninitShadow();

	//ビルボードの終了処理
	UninitBillboard();

	//モデル終了処理
	UninitModel();

	//壁の終了処理
	UninitWall();

	//メッシュの壁の終了処理
	UninitMeshwall();

	//メッシュフィールドの終了処理
	UninitMeshifild();

	//各種オブジェクトの終了処理
	//Direct3Dディバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//フォントオブジェクトの開放
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void Update(void)
{
	//各種オブジェクト更新処理

	//キーボードの更新処理
	UpdateKeyboard();

	//メッシュフィールドの更新処理
	UpdateMeshifild();

	//メッシュの壁の更新処理
	UpdateMeshwall();

	//壁の更新処理
	UpdateWall();

	//モデルの更新処理
	UpdateModel();

	//ビルボードの更新処理
	UpdateBillboard();

	//影の更新処理
	UpdateShadow();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

}

//-----------------------------------------------------------------------------
//描写処理
//-----------------------------------------------------------------------------
void Draw(void)
{//バックバッファ&Zバッファのクリア
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//各種オブジェクトの描画処理

		SetCamera();
	
		//メッシュフィールドの描画
		DrawMeshifild();

		//メッシュの壁の描画
		DrawMeshwall();

		//壁の描画処理
		DrawWall();

		//モデルの描画処理
		DrawModel();

		//ビルボードの描画
		//DrawBillboard();

		//影の描画処理
		DrawShadow();

		//FPSの表示
#ifdef _DEBUG
		DrawFPS();
		DrawTxt();
#endif

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//-----------------------------------------------------------------------------
// FPSの表示
//-----------------------------------------------------------------------------
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_RIGHT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//カメラ座標テキストの表示
void DrawTxt(void)
{
	Camera *pCamera;
	pCamera = GetCamera();

	Model *pModel;
	pModel = GetModel();

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[1024];
	int nNum = sprintf(&aStr[0],"カメラ視点:(%.2f , %.2f , %.2f)\n\n",pCamera->posV.x, pCamera->posV.y, pCamera->posV.z);

	nNum += sprintf(&aStr[nNum], "カメラ注視点:(%.2f , %.2f , %.2f)\n\n", pCamera->posR.x, pCamera->posR.y, pCamera->posR.z);

	nNum += sprintf(&aStr[nNum], "カメラ角度:(%.2f)\n\n", pCamera->rot.y);

	nNum += sprintf(&aStr[nNum], "モデルの位置:(%.2f , %.2f , %.2f)\n\n", pModel->pos.x, pModel->pos.y, pModel->pos.z);

	nNum += sprintf(&aStr[nNum], "モデル角度:(%.2f)\n\n", pModel->rot.y);

	nNum += sprintf(&aStr[nNum], "モデルの目的の角度:(%.2f)\n\n", pModel->PurposeRot.y);

	nNum += sprintf(&aStr[nNum], "sinf:(%.4f)\n\n", sinf(pCamera->rot.y));

	nNum += sprintf(&aStr[nNum], "cosf:(%.4f)\n\n", cosf(pCamera->rot.y));

	//テキストの描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}


LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

