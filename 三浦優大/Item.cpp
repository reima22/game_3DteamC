//================================================
//
//石の処理[stone.h]
// Author; miura yuudai
//
//================================================

#include "Item.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "Billboard.h"
#include "bullet.h"
#include "model.h"
#include "fade.h"
#include "Timer.h"
#include "Coin.h"

//=====================
//グローバル変数
//=====================
//メッシュ（頂点情報）へのポインタ
LPD3DXMESH g_pMeshItem[2];

//マテリアル（材質情報）へのポインタ
LPD3DXBUFFER g_pBuffMatItem[2];

DWORD g_nNumMatItem[2];//マテリアルの数
Item g_PosItem[MAXITEM];//xファイル
D3DXMATRIX g_mtxWolrdItem;//ワールドマトリックス
int nCntScore = 0;
int ItemReleasegun = 0;
int ItemReleasenaihu = 0;

//====================
//モデルの初期化処理
//====================
void InitItem(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//xファイルの読み込み
	D3DXLoadMeshFromX("data/MODEL/gun.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatItem[0], NULL, &g_nNumMatItem[0], &g_pMeshItem[0]);
	D3DXLoadMeshFromX("data/MODEL/rancher.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatItem[1], NULL, &g_nNumMatItem[1], &g_pMeshItem[1]);

	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		//変数初期化
		g_PosItem[nCntMat].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].rotmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_PosItem[nCntMat].MaxStone = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);
		g_PosItem[nCntMat].MinStone = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);
		g_PosItem[nCntMat].bUse = false;
		nCntScore = 0;
		//マテリアルへのポインタ
		//D3DXMATERIAL *pMat;

		////マテリアルデータへのポインタを取得
		//pMat = (D3DXMATERIAL*)g_pBuffMatItem->GetBufferPointer();

		//if (pMat[nCntMat].pTextureFilename != NULL)
		//{
		//	//テキスチャの読み込み
		//	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Wall3.png", &g_PosItem[nCntMat].g_apTextureItem);
		//}
	}
}
//=======================
//モデルの終了処理
//=======================
void UninitItem(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//頂点の開放
		if (g_pMeshItem[nCnt]!= NULL)
		{
			g_pMeshItem[nCnt]->Release();
			g_pMeshItem[nCnt] = NULL;
		}

		//材質の開放
		if (g_pBuffMatItem[nCnt] != NULL)
		{
			g_pBuffMatItem[nCnt]->Release();
			g_pBuffMatItem[nCnt] = NULL;
		}
	}

}
//=======================
//モデルの更新処理
//=======================
void UpdateItem(void)
{
	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE *pVtxBuff;//頂点バッファへのポインタ


	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		if (g_PosItem[nCntMat].bUse == true)
		{
			nNumVtx = g_pMeshItem[g_PosItem[nCntMat].nType]->GetNumVertices();

			//頂点フォーマットのサイズを取得
			sizeFVF = D3DXGetFVFVertexSize(g_pMeshItem[g_PosItem[nCntMat].nType]->GetFVF());

			//頂点バッファのロック
			g_pMeshItem[g_PosItem[nCntMat].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

			for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;//頂点座標の代入

				if (vtx.x > g_PosItem[nCntMat].MaxStone.x)
				{
					g_PosItem[nCntMat].MaxStone.x = vtx.x;
				}

				if (vtx.x < g_PosItem[nCntMat].MinStone.x)
				{
					g_PosItem[nCntMat].MinStone.x = vtx.x;
				}

				if (vtx.y > g_PosItem[nCntMat].MaxStone.y)
				{
					g_PosItem[nCntMat].MaxStone.y = vtx.y;
				}

				if (vtx.y < g_PosItem[nCntMat].MinStone.y)
				{
					g_PosItem[nCntMat].MinStone.y = vtx.y;
				}

				if (vtx.z > g_PosItem[nCntMat].MaxStone.z)
				{
					g_PosItem[nCntMat].MaxStone.z = vtx.z;
				}

				if (vtx.z < g_PosItem[nCntMat].MinStone.z)
				{
					g_PosItem[nCntMat].MinStone.z = vtx.z;
				}

				pVtxBuff += sizeFVF;//頂点フォーマットのサイズ分ポインタを進める
			}

			if (nCntScore == 20)
			{
				SetFade(FADE_OUT, MODE_RESULT);
			}

			for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
			{
				g_PosItem[nCntMat].rotDest.y += D3DX_PI / 46;

				// 目的の回転角の上限
				if (g_PosItem[nCntMat].rotDest.y - g_PosItem[nCntMat].rot.y < -D3DX_PI)
				{
					g_PosItem[nCntMat].rotDest.y += D3DX_PI * 2.0f;
				}
				else if (g_PosItem[nCntMat].rotDest.y - g_PosItem[nCntMat].rot.y > D3DX_PI)
				{
					g_PosItem[nCntMat].rotDest.y -= D3DX_PI * 2.0f;
				}

				// 向きの更新
				g_PosItem[nCntMat].rot.y += (g_PosItem[nCntMat].rotDest.y - g_PosItem[nCntMat].rot.y) * 0.1f;

				// 現在の回転角の上限
				if (g_PosItem[nCntMat].rot.y < -D3DX_PI)
				{
					g_PosItem[nCntMat].rot.y += D3DX_PI * 2.0f;
				}
				else if (g_PosItem[nCntMat].rot.y > D3DX_PI)
				{
					g_PosItem[nCntMat].rot.y -= D3DX_PI * 2.0f;
				}
			}

			for (int nCntMat = 0; nCntMat < 30; nCntMat++)
			{
				D3DXVECTOR3 pos;
				int nLife;
				D3DXVECTOR3 move;
				float fAngle;

				pos = D3DXVECTOR3(g_PosItem[nCntMat].Pos.x, g_PosItem[nCntMat].Pos.y, g_PosItem[nCntMat].Pos.z);//位置
				nLife = 20;//寿命をランダム
				fAngle = (float)(rand() % 628 - 314) / 100.0f;//爆発の範囲
				move.x = sinf(fAngle)*2.5f;//x軸の弾の速度
				move.y = 0.5f;//y軸の弾の速度
				move.z = cosf(fAngle)*2.5f;//y軸の弾の速度
				//SetBillboard(pos, nLife, move, 0);//エフェクト処理
			}

		}
	}


}
//=======================
//モデルの描画処理
//=======================
void DrawItem(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//マテリアルへのポインタ
	D3DXMATERIAL *pMat;

	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;

	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			if (g_PosItem[nCntMat].bUse == true)
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_mtxWolrdItem);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_PosItem[nCntMat].rot.y, g_PosItem[nCntMat].rot.x, g_PosItem[nCntMat].rot.z);

				D3DXMatrixMultiply(&g_mtxWolrdItem, &g_mtxWolrdItem, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_PosItem[nCntMat].Pos.x, g_PosItem[nCntMat].Pos.y, g_PosItem[nCntMat].Pos.z);

				D3DXMatrixMultiply(&g_mtxWolrdItem, &g_mtxWolrdItem, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_mtxWolrdItem);

				//現在のマテリアルを取得
				pDevice->GetMaterial(&matDef);

				//マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)g_pBuffMatItem[nCnt]->GetBufferPointer();

				for (int nCntMatVer = 0; nCntMatVer < (int)g_nNumMatItem; nCntMatVer++)
				{
					if (g_PosItem[nCntMat].nType == 0)
					{
						//マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_pMeshItem[0]->DrawSubset(nCntMatVer);
						break;
					}

					else if (g_PosItem[nCntMat].nType == 1)
					{
						//マテリアルの設定
						pDevice->SetMaterial(&pMat[nCntMatVer].MatD3D);

						//テクスチャの設定
						pDevice->SetTexture(0, NULL);

						//モデルパーツの描画
						g_pMeshItem[1]->DrawSubset(nCntMatVer);
						break;
					}
				}
			}
		}
		//保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}
Item *GetItem(void)
{
	return &g_PosItem[0];
}
//==============================================================================
// 外積を利用した当たり判定
//==============================================================================
bool CollisionVecItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	bool bLand = false;

	D3DXVECTOR3 pos = *pPos;// 判定対象の位置

	int g_nCntSt;
	int nCntStone;

	g_nCntSt = 0;
	nCntStone = 0;
	ItemReleasegun = 0;//アイテムの受け渡しの初期化
	ItemReleasenaihu = 0;//アイテムの受け渡しの初期化

	//ポインタの受け渡し
	BILLBOARD *pBill;
	pBill = GetBillboard();

	Player *pPlayer;
	pPlayer = GetModel();


	for (int nCount = 0; nCount < MAXITEM; nCount++)
	{
		//if (g_PosItem[nCount].bUse == true)
		{
			//aPosの値設定
			g_PosItem[nCount].aPos[0 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MinStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MinStone.z);
			g_PosItem[nCount].aPos[1 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MinStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MaxStone.z);
			g_PosItem[nCount].aPos[2 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MaxStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MaxStone.z);
			g_PosItem[nCount].aPos[3 + (nCount * 4)] = D3DXVECTOR3(g_PosItem[nCount].Pos.x + g_PosItem[nCount].MaxStone.x, 0.0f, g_PosItem[nCount].Pos.z + g_PosItem[nCount].MinStone.z);

			//外積の式
			g_PosItem[nCount].Vec[0 + (nCount * 4)] = g_PosItem[nCount].aPos[1 + (nCount * 4)] - g_PosItem[nCount].aPos[0 + (nCount * 4)];
			g_PosItem[nCount].Vec[1 + (nCount * 4)] = g_PosItem[nCount].aPos[2 + (nCount * 4)] - g_PosItem[nCount].aPos[1 + (nCount * 4)];
			g_PosItem[nCount].Vec[2 + (nCount * 4)] = g_PosItem[nCount].aPos[3 + (nCount * 4)] - g_PosItem[nCount].aPos[2 + (nCount * 4)];
			g_PosItem[nCount].Vec[3 + (nCount * 4)] = g_PosItem[nCount].aPos[0 + (nCount * 4)] - g_PosItem[nCount].aPos[3 + (nCount * 4)];
		}
	}

	for (int nCount = 0; nCount < MAXITEMVER; nCount++)
	{
		//外積の式2
		if (nCount == 0 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - g_PosItem[nCntStone].aPos[nCount];
		}
		else if (nCount == 1 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - g_PosItem[nCntStone].aPos[nCount];
		}
		else if (nCount == 2 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - g_PosItem[nCntStone].aPos[nCount];
		}
		else if (nCount == 3 + g_nCntSt)
		{
			g_PosItem[nCntStone].g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - g_PosItem[nCntStone].aPos[nCount];
		}

		g_PosItem[nCntStone].PlayerVec[nCount] = (g_PosItem[nCntStone].Vec[nCount].z * g_PosItem[nCntStone].g_Vec[nCount].x) - (g_PosItem[nCntStone].Vec[nCount].x * g_PosItem[nCntStone].g_Vec[nCount].z);

		if (pPos->y <= g_PosItem[nCntStone].Pos.y + g_PosItem[nCntStone].MaxStone.y - fHeightMin && pPos->y > g_PosItem[nCntStone].Pos.y + g_PosItem[nCntStone].MinStone.y - fHeightMax)
		{
			if (g_PosItem[nCntStone].PlayerVec[0 + (nCntStone * 4)] > 0.0f && g_PosItem[nCntStone].PlayerVec[1 + (nCntStone * 4)] > 0.0f && g_PosItem[nCntStone].PlayerVec[2 + (nCntStone * 4)] > 0.0f && g_PosItem[nCntStone].PlayerVec[3 + (nCntStone * 4)] > 0.0f)
			{
				if (g_PosItem[nCntStone].bUse == true)
				{
					if (g_PosItem[nCntStone].nType == 0)
					{
						g_PosItem[nCntStone].bUse = false;
						ItemReleasegun++;//アイテムの受け渡し
						AddCoin(1);
						nCntScore++;
						for (int nCntMat = 0; nCntMat < 106; nCntMat++)
						{
							D3DXVECTOR3 pos;
							int nLife;
							D3DXVECTOR3 move;
							float fAngle;

							pos = D3DXVECTOR3(g_PosItem[nCntStone].Pos.x, g_PosItem[nCntStone].Pos.y, g_PosItem[nCntStone].Pos.z);//位置
							nLife = 15 + rand() % 20;//寿命をランダム
							fAngle = (float)(rand() % 628 - 314) / 100.0f;//爆発の範囲
							move.x = sinf(fAngle)*2.5f;//x軸の弾の速度
							move.y = cosf(fAngle)*2.5f;//y軸の弾の速度
							move.z = cosf(fAngle)*2.5f;//y軸の弾の速度
							SetBillboard(pos, nLife, move, 0);//エフェクト処理
						}
						pBill->bUse = false;
						pPlayer->bUse = false;
						//ItemReleasegun = 0;//アイテムの受け渡し
					}

					else if (g_PosItem[nCntStone].nType == 1)
					{
						g_PosItem[nCntStone].bUse = false;
						ItemReleasenaihu += 3;//アイテムの受け渡し
						AddCoin(1);
						nCntScore++;
						for (int nCntMat = 0; nCntMat < 106; nCntMat++)
						{
							D3DXVECTOR3 pos;
							int nLife;
							D3DXVECTOR3 move;
							float fAngle;

							pos = D3DXVECTOR3(g_PosItem[nCntStone].Pos.x, g_PosItem[nCntStone].Pos.y, g_PosItem[nCntStone].Pos.z);//位置
							nLife = 15 + rand() % 20;//寿命をランダム
							fAngle = (float)(rand() % 628 - 314) / 100.0f;//爆発の範囲
							move.x = sinf(fAngle)*2.5f;//x軸の弾の速度
							move.y = cosf(fAngle)*2.5f;//y軸の弾の速度
							move.z = cosf(fAngle)*2.5f;//y軸の弾の速度
							SetBillboard(pos, nLife, move, 0);//エフェクト処理
						}
						//ItemReleasenaihu = 0;//アイテムの受け渡しの初期化
					}
				}
			}
		}

		if (nCount == 3 + (4 * nCntStone))
		{
			g_nCntSt += 4;
			nCntStone += 1;
		}
	}
	return bLand;
}
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType)
{
	BYTE *pVtxBuff;//頂点バッファへのポインタ

	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntMat = 0; nCntMat < MAXITEM; nCntMat++)
	{
		//頂点バッファのロック
		g_pMeshItem[g_PosItem[nCntMat].nType]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		if (g_PosItem[nCntMat].bUse == false)//弾を使用しているかどうか
		{
			if (nType == 0)
			{
				//位置設定
				g_PosItem[nCntMat].Pos = pos;

				//位置回転
				g_PosItem[nCntMat].rot = rot;

				//タイプ分け
				g_PosItem[nCntMat].nType = nType;

				//弾の使用
				g_PosItem[nCntMat].bUse = true;
				break;
			}

			else if (nType == 1)
			{
				//位置設定
				g_PosItem[nCntMat].Pos = pos;

				//位置回転
				g_PosItem[nCntMat].rot = rot;

				//タイプ分け
				g_PosItem[nCntMat].nType = nType;

				//弾の使用
				g_PosItem[nCntMat].bUse = true;
				break;
			}
		}

		//頂点バッファのアンロック
		g_pMeshItem[g_PosItem[nCntMat].nType]->UnlockVertexBuffer();

	}
}
int Releaseitem(void)
{
	return ItemReleasegun;
}
int Releaseitemm(void)
{
	return ItemReleasenaihu;
}

