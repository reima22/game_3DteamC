//-----------------------------------------------------------------------------
//
// ライトの処理
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------

#include "light.h"

//マクロ定義
#define MAX_LIGHT (3)

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
D3DLIGHT9 g_light[MAX_LIGHT];

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//デバイスポインタ
	D3DXVECTOR3 VecDir[MAX_LIGHT];			//設定用方向ベクトル

	//デバイス取得
	pDevice = GetDevice();
	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		//ライトをクリアする
		ZeroMemory(&g_light[nCount], sizeof(D3DLIGHT9));
	}

	//ライトの種類を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;
	g_light[2].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光の設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 0.65f);
	g_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 0.15f);

	//ライトの方向を設定
	VecDir[0] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	VecDir[1] = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	VecDir[2] = D3DXVECTOR3(0.9f, -0.1f, 0.4f);

	for (int nCount = 0; nCount < MAX_LIGHT; nCount++)
	{
		D3DXVec3Normalize(&VecDir[nCount], &VecDir[nCount]);	//正規化
		g_light[nCount].Direction = VecDir[nCount];
		//ライトの設定
		pDevice->SetLight(nCount, &g_light[nCount]);
		//ライトを有効かする
		pDevice->LightEnable(nCount, TRUE);
	}

	
}

//-----------------------------------------------------------------------------
//終了処理
//-----------------------------------------------------------------------------
void UninitLight(void)
{

}

//-----------------------------------------------------------------------------
//更新処理
//-----------------------------------------------------------------------------
void UpdateLight(void)
{

}