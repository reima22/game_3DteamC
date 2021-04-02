//==============================================================================
//
// ���U���g��ʂ̕`��kresult.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "result.h"
#include "input.h"
#include "player.h"
#include "hp.h"
#include "sound.h"
#include "fade.h"
#include "gamepad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define RESULT_POLYGON		(5)		// �ő�|���S����
#define TEXTURE_RESULT		(5)		// �e�N�X�`���̐�
#define P_SIZE				(D3DXVECTOR3(100.0f,50.0f,0.0f))
#define P_POS_1				(D3DXVECTOR3(320.0f,200.0f,0.0f))
#define P_POS_2				(D3DXVECTOR3(960.0f,200.0f,0.0f))

#define WL_SIZE				(D3DXVECTOR3(200.0f,50.0f,0.0f))
#define WL_POS_1			(D3DXVECTOR3(320.0f,400.0f,0.0f))
#define WL_POS_2			(D3DXVECTOR3(960.0f,400.0f,0.0f))

//#define RESULTLOGO_POSX		(640.0f)	// ���U���g���S�̒��SX���W
//#define RESULTLOGO_POSY		(200.0f)	// ���U���g���S�̒��SY���W
//#define RESULTLOGO_SIZEX	(240.0f)	// ���U���g���S�̒��S����̕�
//#define RESULTLOGO_SIZEY	(40.0f)		// ���U���g���S�̒��S����̍���
//#define RESULT_PLATE_SIZEX	(240.0f)	// ���U���g�X�R�A�v���[�g�̕�
//#define RESULT_PLATE_SIZEY	(40.0f)		// ���U���g�X�R�A�v���[�g�̍���
//#define RESULT_SCOREX		(500)		// ���U���g�X�R�A�̏�ꌅ�ڂ�X���W
//#define RESULT_SCOREY		(360)		// ���U���g�X�R�A�̏�ꌅ�ڂ�Y���W
//#define RESULT_SCORE_SIZEX	(20.0f)		// ���U���g�X�R�A�̈ꌅ�̕�
//#define RESULT_SCORE_SIZEY	(30.0f)		// ���U���g�X�R�A�̈ꌅ�̍���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[TEXTURE_RESULT] = {};	// ���U���g��ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posResult[RESULT_POLYGON];					// ���U���g��ʂ̈ʒu

//D3DXVECTOR3 g_posResultlogo;								// ���U���g���S�̈ʒu
//D3DXVECTOR3 g_posResultPlate;								// �X�R�A�̃v���[�g
//D3DXVECTOR3 g_posResultScore[MAX_SCORE];					// ���U���g�X�R�A�̈ʒu

//==============================================================================
// ���U���g��ʂ̏���������
//==============================================================================
HRESULT InitResult(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�L�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice, 
		"data/TEXTURE/result/result_bg.jpg", 
		&g_pTextureResult[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/result/1p.png",
		&g_pTextureResult[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/result/2p.png",
		&g_pTextureResult[2]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/result/winner.png",
		&g_pTextureResult[3]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/result/loser.png",
		&g_pTextureResult[4]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * RESULT_POLYGON,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,								// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	g_posResult[0] = D3DXVECTOR3(SCREEN_CENTERX, SCREEN_CENTERY, 0.0f);
	g_posResult[1] = P_POS_1;
	g_posResult[2] = P_POS_2;
	g_posResult[3] = WL_POS_1;
	g_posResult[4] = WL_POS_2;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < RESULT_POLYGON; nCnt++,pVtx += 4)
	{
		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�			
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	bool bResultbgm = RESULT_BGM;
	if (bResultbgm == true)
	{
		// BGM�̍Đ�
		PlaySound(SOUND_LABEL_RESULT);
	}

	return S_OK;
}

//==============================================================================
// ���U���g��ʂ̏I������
//==============================================================================
void UninitResult(void)
{
	// �T�E���h�̒�~����
	StopSound();

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < TEXTURE_RESULT; nCnt++)
	{
		if (g_pTextureResult[nCnt] != NULL)
		{
			g_pTextureResult[nCnt]->Release();
			g_pTextureResult[nCnt] = NULL;
		}
	}
}

//==============================================================================
// ���U���g��ʂ̍X�V����
//==============================================================================
void UpdateResult(void)
{
	// ���[�J���ϐ��錾
	FADE fade = GetFade();

	for (int nCnt = 0; nCnt < RESULT_POLYGON; nCnt++)
	{
		SetVtxResult(nCnt);
	}
	
	// �����L���O��ʂւ̐؂�ւ�
	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}

//==============================================================================
// ���U���g��ʂ̕`�揈��
//==============================================================================
void DrawResult(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	HP *pHP = GetHp();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffResult,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < RESULT_POLYGON; nCnt++)
	{
		if (nCnt <= 2)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResult[nCnt]);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			if (pHP->fBar >= HP_LIMIT)
			{
				if (nCnt == 3)
				{
					pDevice->SetTexture(0, g_pTextureResult[4]);
				}
				else
				{
					pDevice->SetTexture(0, g_pTextureResult[3]);
				}
			}
			else
			{
				if (nCnt == 3)
				{
					pDevice->SetTexture(0, g_pTextureResult[3]);
				}
				else
				{
					pDevice->SetTexture(0, g_pTextureResult[4]);
				}
			}
		}

		

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}			
}

//==============================================================================
// ���_���W�X�V
//==============================================================================
void SetVtxResult(int nCnt)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCnt;

	switch (nCnt)
	{
	case 0:	// �w�i
		pVtx[0].pos = D3DXVECTOR3(g_posResult[nCnt].x - SCREEN_CENTERX, g_posResult[nCnt].y + SCREEN_CENTERY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posResult[nCnt].x - SCREEN_CENTERX, g_posResult[nCnt].y - SCREEN_CENTERY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posResult[nCnt].x + SCREEN_CENTERX, g_posResult[nCnt].y + SCREEN_CENTERY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posResult[nCnt].x + SCREEN_CENTERX, g_posResult[nCnt].y - SCREEN_CENTERY, 0.0f);
		break;

	case 1:
		pVtx[0].pos = D3DXVECTOR3(g_posResult[nCnt].x - P_SIZE.x, g_posResult[nCnt].y + P_SIZE.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posResult[nCnt].x - P_SIZE.x, g_posResult[nCnt].y - P_SIZE.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posResult[nCnt].x + P_SIZE.x, g_posResult[nCnt].y + P_SIZE.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posResult[nCnt].x + P_SIZE.x, g_posResult[nCnt].y - P_SIZE.y, 0.0f);
		break;

	case 2:
		pVtx[0].pos = D3DXVECTOR3(g_posResult[nCnt].x - P_SIZE.x, g_posResult[nCnt].y + P_SIZE.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posResult[nCnt].x - P_SIZE.x, g_posResult[nCnt].y - P_SIZE.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posResult[nCnt].x + P_SIZE.x, g_posResult[nCnt].y + P_SIZE.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posResult[nCnt].x + P_SIZE.x, g_posResult[nCnt].y - P_SIZE.y, 0.0f);
		break;

	case 3:
		pVtx[0].pos = D3DXVECTOR3(g_posResult[nCnt].x - WL_SIZE.x, g_posResult[nCnt].y + WL_SIZE.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posResult[nCnt].x - WL_SIZE.x, g_posResult[nCnt].y - WL_SIZE.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posResult[nCnt].x + WL_SIZE.x, g_posResult[nCnt].y + WL_SIZE.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posResult[nCnt].x + WL_SIZE.x, g_posResult[nCnt].y - WL_SIZE.y, 0.0f);
		break;

	case 4:
		pVtx[0].pos = D3DXVECTOR3(g_posResult[nCnt].x - WL_SIZE.x, g_posResult[nCnt].y + WL_SIZE.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posResult[nCnt].x - WL_SIZE.x, g_posResult[nCnt].y - WL_SIZE.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posResult[nCnt].x + WL_SIZE.x, g_posResult[nCnt].y + WL_SIZE.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posResult[nCnt].x + WL_SIZE.x, g_posResult[nCnt].y - WL_SIZE.y, 0.0f);
		break;

	default:
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();
}