//==============================================================================
//
// ���U���g��ʂ̕`��kresult.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "result.h"
#include "input.h"
#include "player.h"
//#include "score.h"
#include "sound.h"
#include "fade.h"
#include "gamepad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define RESULT_POLYGON		(11)		// �ő�|���S����
#define TEXTURE_RESULT		(4)			// �e�N�X�`���̐�
#define RESULTLOGO_POSX		(640.0f)	// ���U���g���S�̒��SX���W
#define RESULTLOGO_POSY		(200.0f)	// ���U���g���S�̒��SY���W
#define RESULTLOGO_SIZEX	(240.0f)	// ���U���g���S�̒��S����̕�
#define RESULTLOGO_SIZEY	(40.0f)		// ���U���g���S�̒��S����̍���
#define RESULT_PLATE_SIZEX	(240.0f)	// ���U���g�X�R�A�v���[�g�̕�
#define RESULT_PLATE_SIZEY	(40.0f)		// ���U���g�X�R�A�v���[�g�̍���
#define RESULT_SCOREX		(500)		// ���U���g�X�R�A�̏�ꌅ�ڂ�X���W
#define RESULT_SCOREY		(360)		// ���U���g�X�R�A�̏�ꌅ�ڂ�Y���W
#define RESULT_SCORE_SIZEX	(20.0f)		// ���U���g�X�R�A�̈ꌅ�̕�
#define RESULT_SCORE_SIZEY	(30.0f)		// ���U���g�X�R�A�̈ꌅ�̍���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureResult[TEXTURE_RESULT] = {};	// ���U���g��ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;			// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posResult;									// ���U���g��ʂ̈ʒu
D3DXVECTOR3 g_posResultlogo;								// ���U���g���S�̈ʒu
D3DXVECTOR3 g_posResultPlate;								// �X�R�A�̃v���[�g
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

	bool bResultbgm = RESULT_BGM;
	if (bResultbgm == true)
	{
		//if (Player->state == PLAYERSTATE_GAMEOVER)
		//{
		//	// BGM�̍Đ�
		//	PlaySound(SOUND_LABEL_BGM003);
		//}
		//else
		//{
			// BGM�̍Đ�
			PlaySound(SOUND_LABEL_BGM002);
		//}
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
	VERTEX_2D *pVtx;
	FADE fade = GetFade();
	
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
		else if(nCnt == 2)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResult[2]);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureResult[3]);
		}

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}			
}