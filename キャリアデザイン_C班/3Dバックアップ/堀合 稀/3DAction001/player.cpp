//==============================================================================
//
// 3Dプレイヤーの描画〔player.cpp〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "object.h"
#include "math.h"

// マクロ定義
//#define MODEL_MOVE	(1.0f)
//#define MODEL_TURN	(0.1f)
#define PLAYER_MOVE		(1.0f)
#define PLAYER_TURN		(0.1f)
#define VTX_MINP		(D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f))		// 仮頂点最小値
#define	VTX_MAXP		(D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f))	// 仮頂点最大値
//#define MAT_MAX		(3)		// マテリアルの最大数
//#define TEX_MAX		(3)		// テクスチャの最大数



//==============================================================================
// グローバル変数
//==============================================================================

//LPD3DXMESH g_pMeshPlayer = NULL;						// メッシュ(頂点情報)へのポインタ
//LPD3DXBUFFER g_pBuffMatPlayer = NULL;					// マテリアル(材質情報)へのポインタ
//LPDIRECT3DTEXTURE9 g_apTextureModel[TEX_MAX] = {};	// テクスチャへのポインタ
//DWORD g_nNumMatPlayer = 0;								// マテリアルの数
D3DXVECTOR3 g_vtxMinPlayer, g_vtxMaxPlayer;				// モデルの各座標のの最大値・最小値
Player g_player;										// プレイヤーの構造体

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT InitPlayer(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// デバイスの取得

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		"data/MODEL/00_body.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[0].pBuffMatModel,
		NULL,
		&g_player.aModel[0].nNumMatModel,
		&g_player.aModel[0].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/01_head.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[1].pBuffMatModel,
		NULL,
		&g_player.aModel[1].nNumMatModel,
		&g_player.aModel[1].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/02_arm_top_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[2].pBuffMatModel,
		NULL,
		&g_player.aModel[2].nNumMatModel,
		&g_player.aModel[2].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/03_arm_under_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[3].pBuffMatModel,
		NULL,
		&g_player.aModel[3].nNumMatModel,
		&g_player.aModel[3].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/04_hand_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[4].pBuffMatModel,
		NULL,
		&g_player.aModel[4].nNumMatModel,
		&g_player.aModel[4].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/05_arm_top_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[5].pBuffMatModel,
		NULL,
		&g_player.aModel[5].nNumMatModel,
		&g_player.aModel[5].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/06_arm_under_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[6].pBuffMatModel,
		NULL,
		&g_player.aModel[6].nNumMatModel,
		&g_player.aModel[6].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/07_hand_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[7].pBuffMatModel,
		NULL,
		&g_player.aModel[7].nNumMatModel,
		&g_player.aModel[7].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/08_leg_top_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[8].pBuffMatModel,
		NULL,
		&g_player.aModel[8].nNumMatModel,
		&g_player.aModel[8].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/09_leg_under_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[9].pBuffMatModel,
		NULL,
		&g_player.aModel[9].nNumMatModel,
		&g_player.aModel[9].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/10_foot_R.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[10].pBuffMatModel,
		NULL,
		&g_player.aModel[10].nNumMatModel,
		&g_player.aModel[10].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/11_leg_top_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[11].pBuffMatModel,
		NULL,
		&g_player.aModel[11].nNumMatModel,
		&g_player.aModel[11].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/12_leg_under_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[12].pBuffMatModel,
		NULL,
		&g_player.aModel[12].nNumMatModel,
		&g_player.aModel[12].pMeshModel);

	D3DXLoadMeshFromX(
		"data/MODEL/13_foot_L.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_player.aModel[13].pBuffMatModel,
		NULL,
		&g_player.aModel[13].nNumMatModel,
		&g_player.aModel[13].pMeshModel);

	g_player.nNumModel = MODEL_PARTS;

	// ローカル変数宣言
	int nNumVtx;			// 頂点数
	DWORD sizeFVF;			// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;			// 頂点バッファへのポインタ

	//D3DXMATERIAL *pMat;		// マテリアルへのポインタ
	//						// マテリアル情報に対するポインタを取得
	//pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();
	//for (int nCntMat = 0; nCntMat < (int)g_nNumMatModel; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		// ファイル名を使用してテクスチャを読み込む
	//		D3DXCreateTextureFromFile(
	//			pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&g_apTextureModel[nCntMat]);
	//	}
	//}

	// 頂点数を取得
	nNumVtx = g_player.aModel[0].pMeshModel->GetNumVertices();

	// 頂点フォーマットのサイズの取得
	sizeFVF = D3DXGetFVFVertexSize(g_player.aModel[0].pMeshModel->GetFVF());

	// 各パーツの階層構造設定
	// 体
	g_player.aModel[0].nIdxModelParent = -1;	// 親モデルのインデックスを設定
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頭
	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 右上腕
	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-7.5f, 17.5f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 右下腕
	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-4.5f, 0.0f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 右手
	g_player.aModel[4].nIdxModelParent = 3;
	g_player.aModel[4].pos = D3DXVECTOR3(-5.5f, 0.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 左上腕
	g_player.aModel[5].nIdxModelParent = 0;
	g_player.aModel[5].pos = D3DXVECTOR3(7.5f, 17.5f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 左下腕
	g_player.aModel[6].nIdxModelParent = 5;
	g_player.aModel[6].pos = D3DXVECTOR3(4.5f, 0.0f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 左手
	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(5.5f, 0.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 右腿
	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(-4.0f, 0.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 右下腿
	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -7.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 右足
	g_player.aModel[10].nIdxModelParent = 9;
	g_player.aModel[10].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	g_player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 左腿
	g_player.aModel[11].nIdxModelParent = 0;
	g_player.aModel[11].pos = D3DXVECTOR3(4.0f, 0.0f, 0.0f);
	g_player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 左下腿
	g_player.aModel[12].nIdxModelParent = 11;
	g_player.aModel[12].pos = D3DXVECTOR3(0.0f, -7.0f, 0.0f);
	g_player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 左上腕
	g_player.aModel[13].nIdxModelParent = 12;
	g_player.aModel[13].pos = D3DXVECTOR3(0.0f, -8.0f, 0.0f);
	g_player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 変数の初期化
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_vtxMinPlayer = VTX_MINP;
	g_vtxMaxPlayer = VTX_MAXP;

	// 影の設定
	g_player.nIdx = SetShadow(D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z), 10.0f, 10.0f);

	// 頂点バッファをロック
	g_player.aModel[0].pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// 頂点座標の比較
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

		// 各座標の最大値の比較
		if (g_vtxMaxPlayer.x < vtx.x)
		{			
			g_vtxMaxPlayer.x = vtx.x;
		}			
		if (g_vtxMaxPlayer.y < vtx.y)
		{			
			g_vtxMaxPlayer.y = vtx.y;
		}			
		if (g_vtxMaxPlayer.z < vtx.z)
		{			
			g_vtxMaxPlayer.z = vtx.z;
		}

		// 各座標の最小値の比較
		if (g_vtxMinPlayer.x > vtx.x)
		{			
			g_vtxMinPlayer.x = vtx.x;
		}			
		if (g_vtxMinPlayer.y > vtx.y)
		{			
			g_vtxMinPlayer.y = vtx.y;
		}			
		if (g_vtxMinPlayer.z > vtx.z)
		{			
			g_vtxMinPlayer.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
	}

	// 頂点バッファをアンロック
	g_player.aModel[0].pMeshModel->UnlockVertexBuffer();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < g_player.nNumModel; nCnt++)
	{
		if (g_player.aModel[nCnt].pMeshModel != NULL)
		{// メッシュの破棄
			g_player.aModel[nCnt].pMeshModel->Release();
			g_player.aModel[nCnt].pMeshModel = NULL;
		}
		
		if (g_player.aModel[nCnt].pBuffMatModel != NULL)
		{// バッファの破棄
			g_player.aModel[nCnt].pBuffMatModel->Release();
			g_player.aModel[nCnt].pBuffMatModel = NULL;
		}
	}
}

//==============================================================================
// 更新処理
//==============================================================================
void UpdatePlayer(void)
{
	//// カメラの取得
	Camera camera = GetCamera();
	//double dSqrt = sqrt(2);		// 2の平方根

	// 位置のリセット
	if (GetKeyboardTrigger(KEYINFO_OK) == true)
	{
		g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 弾の発射
	if (GetKeyboardPress(KEYINFO_SHOT) == true)
	{
		SetBullet(
			D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 30.0f, g_player.pos.z),
			D3DXVECTOR3(sinf(D3DX_PI - g_player.rot.y) * -5.0f, 0.0f, cosf(D3DX_PI - g_player.rot.y) * 5.0f),
			100);
	}

	// 移動量の加算
	g_player.pos += g_player.move;

	// 影の追従
	SetPositionShadow(g_player.nIdx, D3DXVECTOR3(g_player.pos.x, 0.0f, g_player.pos.z));

	// モデルの移動
	if (GetKeyboardPress(KEYINFO_UP) == true)
	{
		if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// 左上方向
			g_player.move.x -= cosf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y + D3DX_PI / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + (D3DX_PI * 3 / 4);
			//model.rotDest.y += (camera.rot.y + (D3DX_PI * 3 / 4) - model.rot.y) * MODEL_TURN;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// 右上方向
			g_player.move.x += cosf(camera.rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y - D3DX_PI / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y - (D3DX_PI * 3 / 4);
			//model.rotDest.y += (camera.rot.y - (D3DX_PI * 3 / 4) - model.rot.y) * MODEL_TURN;
		}
		else
		{// 上方向
			g_player.move.x += sinf(camera.rot.y) * PLAYER_MOVE;
			g_player.move.z += cosf(camera.rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI;
		}
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true)
	{
		if (GetKeyboardPress(KEYINFO_LEFT) == true)
		{// 左下方向
			g_player.move.x += cosf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.move.z -= sinf(camera.rot.y + D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI / 4;
			//model.rotDest.y += (camera.rot.y + D3DX_PI / 4 - model.rot.y) * MODEL_TURN;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
		{// 右下方向
			g_player.move.x -= cosf(camera.rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.move.z += sinf(camera.rot.y - D3DX_PI * 3 / 4) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y + D3DX_PI / -4;
			//model.rotDest.y += (camera.rot.y + D3DX_PI / -4 - model.rot.y) * MODEL_TURN;
		}
		else
		{// 下方向
			g_player.move.x += sinf(camera.rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player.move.z += cosf(camera.rot.y - D3DX_PI) * PLAYER_MOVE;
			g_player.rotDest.y = camera.rot.y;
			//model.rotDest.y += (camera.rot.y - model.rot.y) * 0.1f;
		}
	}
	else if (GetKeyboardPress(KEYINFO_LEFT) == true)
	{// 左方向
		g_player.move.x -= cosf(camera.rot.y) * PLAYER_MOVE;
		g_player.move.z += sinf(camera.rot.y) * PLAYER_MOVE;
		g_player.rotDest.y = camera.rot.y + (D3DX_PI / 2);
		//model.rotDest.y += (camera.rot.y + (D3DX_PI / 2) - model.rot.y) * MODEL_TURN;
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true)
	{// 右方向
		g_player.move.x += cosf(camera.rot.y) * PLAYER_MOVE;
		g_player.move.z -= sinf(camera.rot.y) * PLAYER_MOVE;
		g_player.rotDest.y = camera.rot.y + (D3DX_PI / -2);
	}

	//	//model.moveZ.x = sinf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//model.moveZ.z = cosf(camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//model.rot.y = camera.rot.y;
	//	//if (GetKeyboardPress(KEYINFO_LEFT_MODEL) == true)
	//	//{
	//	//	model.moveX.x = cosf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//	model.moveX.z = sinf(-camera.rot.y - D3DX_PI) * MODEL_MOVE;
	//	//	model.rot.y = camera.rot.y + D3DX_PI / 4;
	//	//	//model.moveX.x /= dSqrt;
	//	//	//model.moveX.z /= dSqrt;
	//	//	//model.moveZ.x /= dSqrt;
	//	//	//model.moveZ.z /= dSqrt;
	//	//}
	//	//else if (GetKeyboardPress(KEYINFO_RIGHT_MODEL) == true)
	//	//{
	//	//	model.moveX.x = cosf(-camera.rot.y) * MODEL_MOVE;
	//	//	model.moveX.z = sinf(-camera.rot.y) * MODEL_MOVE;
	//	//	model.rot.y = camera.rot.y + D3DX_PI / -4;
	//	//	//model.moveX.x /= dSqrt;
	//	//	//model.moveX.z /= dSqrt;
	//	//	//model.moveZ.x /= dSqrt;
	//	//	//model.moveZ.z /= dSqrt;
	//	//}
	//}



	// モデルの上昇・下降
	if (GetKeyboardPress(KEYINFO_UP_MODEL) == true)
	{
		g_player.move.y = 2;
	}
	else if (GetKeyboardPress(KEYINFO_DOWN_MODEL) == true)
	{
		g_player.move.y = -2;
	}
	else
	{
		g_player.move.y = 0;
	}

	// モデルの旋回
	if (GetKeyboardPress(KEYINFO_TURN_LEFT_MODEL) == true)
	{
		g_player.rotDest.y += D3DX_PI / 36;
	}
	if (GetKeyboardPress(KEYINFO_TURN_RIGHT_MODEL) == true)
	{
		g_player.rotDest.y -= D3DX_PI / 36;
	}

	// 目的の回転角の上限
	if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}

	// 向きの更新
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * 0.1f;

	// 現在の回転角の上限
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	// 加速後の減速処理
	g_player.move.x += (0.0f - g_player.move.x) * SPEEDDOWN;
	g_player.move.z += (0.0f - g_player.move.z) * SPEEDDOWN;

	//Object *object = GetObject();

	//if ((object->pos.x + object->vtxMinObject.x) < (model.pos.x + g_vtxMaxModel.x))
	//{
	//	if (object->pos.x + object->vtxMinObject.x < model.pos.x + g_vtxMaxModel.x &&
	//		object->pos.x + object->vtxMaxObject.x > model.pos.x + g_vtxMinModel.x &&
	//		object->pos.z + object->vtxMinObject.z < model.pos.z + g_vtxMaxModel.z &&
	//		object->pos.z + object->vtxMaxObject.z > model.pos.z + g_vtxMinModel.z)
	//	{
	//		model.pos.x = object->pos.x + object->vtxMinObject.x - g_vtxMaxModel.x;
	//		model.move.x = 0.0f;
	//	}
	//}
	//else if()

	//if ((object->pos.x + object->vtxMinObject.x) <= (model.pos.x + g_vtxMaxModel.x) && 
	//	model.pos.x < object->pos.x)
	//{
	//	if (object->pos.x + object->vtxMinObject.x < model.pos.x + g_vtxMaxModel.x &&
	//		object->pos.x + object->vtxMaxObject.x > model.pos.x + g_vtxMinModel.x &&
	//		object->pos.z + object->vtxMinObject.z < model.pos.z + g_vtxMaxModel.z &&
	//		object->pos.z + object->vtxMaxObject.z > model.pos.z + g_vtxMinModel.z)
	//	{
	//		model.pos.x = object->pos.x + object->vtxMinObject.x - g_vtxMaxModel.x;
	//		model.move.x = 0.0f;
	//	}
	//}
	//if ((object->pos.x + object->vtxMaxObject.x) > (model.pos.x + g_vtxMinModel.x) &&
	//	model.pos.x > object->pos.x)
	//{
	//	if (object->pos.x + object->vtxMinObject.x < model.pos.x + g_vtxMaxModel.x &&
	//		object->pos.x + object->vtxMaxObject.x > model.pos.x + g_vtxMinModel.x &&
	//		object->pos.z + object->vtxMinObject.z < model.pos.z + g_vtxMaxModel.z &&
	//		object->pos.z + object->vtxMaxObject.z > model.pos.z + g_vtxMinModel.z)
	//	{
	//		model.pos.x = object->pos.x + object->vtxMaxObject.x - g_vtxMinModel.x;
	//		model.move.x = 0.0f;
	//	}
	//}
	//if ((object->pos.z + object->vtxMinObject.z) < (model.pos.z + g_vtxMaxModel.z) &&
	//	model.pos.z < object->pos.z)
	//{
	//	if (object->pos.x + object->vtxMinObject.x < model.pos.x + g_vtxMaxModel.x &&
	//		object->pos.x + object->vtxMaxObject.x > model.pos.x + g_vtxMinModel.x &&
	//		object->pos.z + object->vtxMinObject.z < model.pos.z + g_vtxMaxModel.z &&
	//		object->pos.z + object->vtxMaxObject.z > model.pos.z + g_vtxMinModel.z)
	//	{
	//		model.pos.z = object->pos.z + object->vtxMinObject.z - g_vtxMaxModel.z;
	//		model.move.z = 0.0f;
	//	}
	//}
	//if ((object->pos.z + object->vtxMaxObject.z) > (model.pos.z + g_vtxMinModel.z) &&
	//	model.pos.z > object->pos.z)
	//{
	//	if (object->pos.x + object->vtxMinObject.x < model.pos.x + g_vtxMaxModel.x &&
	//		object->pos.x + object->vtxMaxObject.x > model.pos.x + g_vtxMinModel.x &&
	//		object->pos.z + object->vtxMinObject.z < model.pos.z + g_vtxMaxModel.z &&
	//		object->pos.z + object->vtxMaxObject.z > model.pos.z + g_vtxMinModel.z)
	//	{
	//		model.pos.z = object->pos.z + object->vtxMaxObject.z - g_vtxMinModel.z;
	//		model.move.z = 0.0f;
	//	}
	//}
	//else if ()
}

//==============================================================================
// 描画処理
//==============================================================================
void DrawPlayer(void)
{
	// ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	// プレイヤーのワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	// プレイヤーの向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	// プレイヤーの位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	// プレイヤーのワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用マトリックス
		D3DXMATRIX mtxParent;					// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		// 各パーツの向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel,g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// 各パーツの位置を反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// 各パーツの親マトリックスを設定
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			if (g_player.aModel[nCntModel].nIdxModelParent == 0)
			{
				mtxParent = g_player.aModel[0].mtxWorld;
			}
			else if (g_player.aModel[nCntModel].nIdxModelParent != 0)
			{
				mtxParent = g_player.aModel[nCntModel - 1].mtxWorld;
			}
		}
		else
		{
			mtxParent = g_player.mtxWorld;	// プレイヤーのマトリックスを設定
		}

		// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		// 各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMatModel->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].nNumMatModel; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			g_player.aModel[nCntModel].pMeshModel->DrawSubset(nCntMat);
		}
	}

	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

// モデルの取得
Player *GetPlayer(void)
{
	return &g_player;
}