//-----------------------------------------------------------------------------
//
// モデル描画の処理
// Author  :Yuto Koseki
//
//-----------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"

//モデル構造体
typedef struct
{
	LPD3DXMESH pMesh = NULL;			//メッシュ（頂点情報）へのポインタ
	LPD3DXBUFFER pBuffMat = NULL;		//マテリアル（材質情報）へのポインタ
	DWORD nNumMat;						//マテリアルの数
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 rot;					//向き
	int nIdxModelParent;				//親モデルのインデックス
}Model;

//モーションの種類
typedef enum
{
	MOTIONTYPE_NUTRAL = 0,		//ニュートラルモーション
	MOTIONTYPE_MAX,
}MOTIONTYPE;

//キーの構造体
typedef struct
{
	float PosX;		//位置X
	float PosY;		//位置Y
	float PosZ;		//位置Z
	float RotX;		//向きX
	float RotY;		//向きY
	float RotZ;		//向きZ
}KEY;

//キー情報の構造体
typedef struct
{
	int Frame;		//再生フレーム
	KEY aKey[14];	//各モデルのキー要素
}KEY_INFO;

//モーション情報の構造体
typedef struct
{
	bool bLoop;				//ループするかどうか
	int nNumKey;			//キーの総数
	KEY_INFO aKeyInfo[8]	//キーの情報
}MOTION_INFO;

//プレイヤーの構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 rotDest;
	D3DXMATRIX mtxWorld;				//ワールドマトリックス

	Model aModel[14];					//モデル（パーツ）
	int nNumModel= 14;					//モデル（パーツ）数

	MOTION_INFO aMotionInfo[5];			//モーション情報
	int nNumMotion;						//モーションの総数
	MOTIONTYPE MotionType;				//モーションタイプ
	bool bLoopMotion;					//ループするかどうか
	int nNumKey;						//キー数
	int nKey;							//キーNo.
	int nCounterMotion;					//モーションカウンター

}Player;

//プロトタイプ宣言
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetMotion(int nNumKey, int nType, bool bLoop);
Player *GetPlayer(void);

#endif _PLAYER_H_