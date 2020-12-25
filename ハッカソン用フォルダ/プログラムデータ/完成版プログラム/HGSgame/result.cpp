//==============================================================================
//
// ���U���g��ʂ̕`��kresult.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "result.h"
#include "input.h"
#include "player.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "gamepad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define RESULT_POLYGON		(10)		// �ő�|���S����
#define TEXTURE_RESULT		(3)			// �e�N�X�`���̐�
#define RESULTLOGO_POSX		(640.0f)	// ���U���g���S�̒��SX���W
#define RESULTLOGO_POSY		(200.0f)	// ���U���g���S�̒��SY���W
#define RESULTLOGO_SIZEX	(240.0f)	// ���U���g���S�̒��S����̕�
#define RESULTLOGO_SIZEY	(40.0f)		// ���U���g���S�̒��S����̍���
#define RESULT_SCOREX		(500)		// ���U���g�X�R�A�̏�ꌅ�ڂ�X���W
#define RESULT_SCOREY		(360)		// ���U���g�X�R�A�̏�ꌅ�ڂ�Y���W
#define RESULT_SCORE_SIZEX	(20.0f)		// ���U���g�X�R�A�̈ꌅ�̕�
#define RESULT_SCORE_SIZEY	(30.0f)		// ���U���g�X�R�A�̈ꌅ�̍���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[TEXTURE_RESULT] = {};	// ���U���g��ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureGameoverlogo = NULL;			// �Q�[���I�[�o�[���S�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posResult;									// ���U���g��ʂ̈ʒu
D3DXVECTOR3 g_posResultlogo;								// ���U���g���S�̈ʒu
D3DXVECTOR3 g_posResultScore[MAX_SCORE];					// ���U���g�X�R�A�̈ʒu

//==============================================================================
// ���U���g��ʂ̏���������
//==============================================================================
HRESULT InitResult(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	PLAYER *Player;

	// �v���C���[�̎擾
	Player = GetPlayer();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	
	// �w�i�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/result.png",
		&g_pTextureResult[0]);

	// ���S�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/gameend.png",
		&g_pTextureResult[1]);

	// �X�R�A�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureResult[2]);

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

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		g_posResultScore[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���U���g��ʂ̒��S���W
	g_posResult = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(g_posResult.x - (SCREEN_WIDTH / 2), g_posResult.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posResult.x - (SCREEN_WIDTH / 2), g_posResult.y - (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posResult.x + (SCREEN_WIDTH / 2), g_posResult.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posResult.x + (SCREEN_WIDTH / 2), g_posResult.y - (SCREEN_HEIGHT / 2), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// ���U���g�̒��S���W
	g_posResult = D3DXVECTOR3(RESULTLOGO_POSX, RESULTLOGO_POSY, 0.0f);

	// �|���S���̊e���_���W
	pVtx[4].pos = D3DXVECTOR3(g_posResult.x - RESULTLOGO_SIZEX, g_posResult.y + RESULTLOGO_SIZEY, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(g_posResult.x - RESULTLOGO_SIZEX, g_posResult.y - RESULTLOGO_SIZEY, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(g_posResult.x + RESULTLOGO_SIZEX, g_posResult.y + RESULTLOGO_SIZEY, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(g_posResult.x + RESULTLOGO_SIZEX, g_posResult.y - RESULTLOGO_SIZEY, 0.0f);

	// rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_���W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[5].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[6].tex = D3DXVECTOR2(1.0, 1.0);
	pVtx[7].tex = D3DXVECTOR2(1.0, 0.0);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// �X�R�A�̒��S���W�̐ݒ�
		g_posResultScore[nCnt] = D3DXVECTOR3(RESULT_SCOREX + ((float)nCnt * 40.0f), RESULT_SCOREY, 0.0f);

		//�X�R�A�̒��_���W�̐ݒ�
		pVtx[8].pos = D3DXVECTOR3(g_posResultScore[nCnt].x - RESULT_SCORE_SIZEX, g_posResultScore[nCnt].y + RESULT_SCORE_SIZEY, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(g_posResultScore[nCnt].x - RESULT_SCORE_SIZEX, g_posResultScore[nCnt].y - RESULT_SCORE_SIZEY, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(g_posResultScore[nCnt].x + RESULT_SCORE_SIZEX, g_posResultScore[nCnt].y + RESULT_SCORE_SIZEY, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(g_posResultScore[nCnt].x + RESULT_SCORE_SIZEX, g_posResultScore[nCnt].y - RESULT_SCORE_SIZEY, 0.0f);

		// rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;	// ���_�|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	// BGM�̍Đ�
	PlaySound(SOUND_LABEL_BGM002);

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
	VERTEX_2D *pVtx;
	FADE fade;
	float fResult = 0.0f;
	int nScore = GetScore();	// �X�R�A�̎擾
	int aNumber[MAX_SCORE];
	int nData = (int)pow(10, MAX_SCORE - 1);

	// �t�F�[�h�̎擾
	fade = GetFade();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`���̐؂�ւ�
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		aNumber[nCnt] = (nScore / nData) % 10;
		nData /= 10;

		// �e�N�X�`���̒��_���W�̍X�V
		pVtx[8].tex = D3DXVECTOR2(0.0f + ((float)aNumber[nCnt] / 10), 1.0f);
		pVtx[9].tex = D3DXVECTOR2(0.0f + ((float)aNumber[nCnt] / 10), 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.1f + ((float)aNumber[nCnt] / 10), 1.0f);
		pVtx[11].tex = D3DXVECTOR2(0.1f + ((float)aNumber[nCnt] / 10), 0.0f);

		// ���_�|�C���^��4���i�߂�
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResult->Unlock();

	// �����L���O��ʂւ̐؂�ւ�
	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_SHOT) == true)
		{
			SetFade(FADE_OUT, MODE_RANKING);
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
		if (nCnt == 0)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResult[0]);
		}
		else if (nCnt == 1)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResult[1]);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResult[2]);
		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}			
}