//==============================================================================
//
// �w�i�|���S���̕`��kbg.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "bg.h"
#include "player.h"
//#include "enemy.h"
#include "input.h"
#include "warning.h"
#include "gamepad.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_BG		(3)			// �w�i�̎��
#define MOVE_BG_A	(0.0005f)	// �w�iA�̑���ړ���
#define MOVE_BG_B	(0.001f)	// �w�iB�̑���ړ��� 
#define MOVE_BG_C	(0.0015f)	// �w�iC�̑���ړ���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_apTextureBg[MAX_BG] = {};	// �w�i�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posBg[MAX_BG];					// �w�i�̈ʒu
int g_nCntAnim;									// �A�j���[�V�����J�E���^�[
float g_fPatternAnim[MAX_BG];					// �A�j���[�V�����p�^�[��
float g_fMoveBgX[MAX_BG];						// ����ɂ��ړ���X
float g_fMoveBgY[MAX_BG];						// ����ɂ��ړ���Y

//==============================================================================
// �w�i�|���S���̏���������
//==============================================================================
HRESULT InitBg(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/bg100.png",
		&g_apTextureBg[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/bg101.png",
		&g_apTextureBg[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/bg102.png",
		&g_apTextureBg[2]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BG,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBg,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		g_posBg[nCnt].x = SCREEN_WIDTH / 2;
		g_posBg[nCnt].y = SCREEN_HEIGHT / 2;
		g_fMoveBgX[nCnt] = 0.0f;
		g_fMoveBgY[nCnt] = 0.0f;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		// �w�i�̒��S���W
		g_posBg[nCnt] = D3DXVECTOR3(g_posBg[nCnt].x, g_posBg[nCnt].y, 0.0f);

		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posBg[nCnt].x - (SCREEN_WIDTH / 2), g_posBg[nCnt].y + (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posBg[nCnt].x - (SCREEN_WIDTH / 2), g_posBg[nCnt].y - (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posBg[nCnt].x + (SCREEN_WIDTH / 2), g_posBg[nCnt].y + (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posBg[nCnt].x + (SCREEN_WIDTH / 2), g_posBg[nCnt].y - (SCREEN_HEIGHT / 2), 0.0f);

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

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();

	return S_OK;
}

//==============================================================================
// �w�i�|���S���̏I������
//==============================================================================
void UninitBg(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (g_apTextureBg[nCnt] != NULL)
		{
			g_apTextureBg[nCnt]->Release();
			g_apTextureBg[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �w�i�|���S���̍X�V����
//==============================================================================
void UpdateBg(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	//ENEMYINFO info = GetInfo();		// �G�S�̏��̎擾
	//PHASESTATE phase = GetPhase();	// �x����Ԃ̎擾

	g_nCntAnim++;	// �A�j���[�V�����J�E���^�[�X�V

					// �v���C���[�̈ړ��ɍ��킹�Ĕw�i�e�N�X�`���̍X�V
	if (GetKeyboardPress(KEYINFO_UP) == true || IsButtonPush(KEYINFO::KEYINFO_UP) == true)
	{ // ���
		g_fMoveBgY[0] -= MOVE_BG_A;
		g_fMoveBgY[1] -= MOVE_BG_B;
		g_fMoveBgY[2] -= MOVE_BG_C;

		if (GetKeyboardPress(KEYINFO_LEFT) == true || IsButtonPush(KEYINFO::KEYINFO_LEFT) == true)
		{
			g_fMoveBgX[0] -= MOVE_BG_A;
			g_fMoveBgX[1] -= MOVE_BG_B;
			g_fMoveBgX[2] -= MOVE_BG_C;
			//g_fMoveBgY[0] -= MOVE_BG_A;
			//g_fMoveBgY[1] -= MOVE_BG_B;
			//g_fMoveBgY[2] -= MOVE_BG_C;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
		{
			g_fMoveBgX[0] += MOVE_BG_A;
			g_fMoveBgX[1] += MOVE_BG_B;
			g_fMoveBgX[2] += MOVE_BG_C;
		}
		else if (GetKeyboardPress(KEYINFO_DOWN) == true || IsButtonPush(KEYINFO::KEYINFO_DOWN) == true)
		{
			g_fMoveBgY[0] += MOVE_BG_A;
			g_fMoveBgY[1] += MOVE_BG_B;
			g_fMoveBgY[2] += MOVE_BG_C;
		}
	}
	else if (GetKeyboardPress(KEYINFO_DOWN) == true || IsButtonPush(KEYINFO::KEYINFO_DOWN) == true)
	{ // ����
		g_fMoveBgY[0] += MOVE_BG_A;
		g_fMoveBgY[1] += MOVE_BG_B;
		g_fMoveBgY[2] += MOVE_BG_C;

		if (GetKeyboardPress(KEYINFO_LEFT) == true || IsButtonPush(KEYINFO::KEYINFO_LEFT) == true)
		{
			g_fMoveBgX[0] -= MOVE_BG_A;
			g_fMoveBgX[1] -= MOVE_BG_B;
			g_fMoveBgX[2] -= MOVE_BG_C;
		}
		else if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
		{
			g_fMoveBgX[0] += MOVE_BG_A;
			g_fMoveBgX[1] += MOVE_BG_B;
			g_fMoveBgX[2] += MOVE_BG_C;
		}
	}
	else if (GetKeyboardPress(KEYINFO_LEFT) == true || IsButtonPush(KEYINFO::KEYINFO_LEFT) == true)
	{ // ����
		g_fMoveBgX[0] -= MOVE_BG_A;
		g_fMoveBgX[1] -= MOVE_BG_B;
		g_fMoveBgX[2] -= MOVE_BG_C;

		if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
		{
			g_fMoveBgX[0] += MOVE_BG_A;
			g_fMoveBgX[1] += MOVE_BG_B;
			g_fMoveBgX[2] += MOVE_BG_C;
		}
	}
	else if (GetKeyboardPress(KEYINFO_RIGHT) == true || IsButtonPush(KEYINFO::KEYINFO_RIGHT) == true)
	{ // �E��
		g_fMoveBgX[0] += MOVE_BG_A;
		g_fMoveBgX[1] += MOVE_BG_B;
		g_fMoveBgX[2] += MOVE_BG_C;
	}

	// �e�N�X�`���̍X�V
	if ((g_nCntAnim % 2) == 0)
	{
		// �e�N�X�`���̃p�^�[���̍X�V
		g_fPatternAnim[0] -= 0.001f;
		g_fPatternAnim[1] -= 0.003f;
		g_fPatternAnim[2] -= 0.005f;

		// ���_�o�b�t�@�����b�N����
		g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCnt = 0; nCnt < MAX_BG; nCnt++, pVtx = pVtx + 4)
		{
			// �e�N�X�`���̒��_���W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_fMoveBgX[nCnt], g_fPatternAnim[nCnt] + g_fMoveBgY[nCnt]);
			pVtx[1].tex = D3DXVECTOR2(0.0f + g_fMoveBgX[nCnt], g_fPatternAnim[nCnt] + g_fMoveBgY[nCnt] - 1.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f + g_fMoveBgX[nCnt], g_fPatternAnim[nCnt] + g_fMoveBgY[nCnt]);
			pVtx[3].tex = D3DXVECTOR2(1.0f + g_fMoveBgX[nCnt], g_fPatternAnim[nCnt] + g_fMoveBgY[nCnt] - 1.0f);
		}
		
		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBg->Unlock();
	}
}

//==============================================================================
// �w�i�|���S���̕`�揈��
//==============================================================================
void DrawBg(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffBg,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBg[nCnt]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}