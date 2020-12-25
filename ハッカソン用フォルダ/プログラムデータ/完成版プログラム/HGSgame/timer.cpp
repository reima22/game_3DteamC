//==============================================================================
//
// �^�C�}�[�̕`��ktimer.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "timer.h"
#include "score.h"
#include "player.h"
#include "sound.h"
#include "game.h"
//#include "nodamage.h"
#include "input.h"
#include "gamepad.h"
#include "math.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define POS_TIMERX	(600.0f)	// �^�C�}�[�̏�ꌅ�̒��SX���W
#define POS_TIMERY	(50.0f)		// �^�C�}�[�̏�ꌅ�̒��SY���W
#define TIMER_SIZEX	(20.0f)		// �^�C�}�[�̐����̕�
#define TIMER_SIZEY	(40.0f)		// �^�C�}�[�̐����̍���
#define TIMER_0		(100)		// �X�e�[�W1�̃^�C�}�[
//#define TIMER_1		(80)		// �X�e�[�W2�̃^�C�}�[
//#define TIMER_2		(120)		// �X�e�[�W3�̃^�C�}�[

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;			// �X�R�A�e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;		// �X�R�A�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aTimer[MAX_TIMER];					// �X�R�A�̈ʒu���
int g_nTimer;										// �X�R�A�̐��l
int g_nCntDownTimer;								// �^�C�}�[�����J�E���^�[
int g_nClearCnt;									// �N���A���̑ҋ@�J�E���^�[

//==============================================================================
// �^�C�}�[�̏���������
//==============================================================================
HRESULT InitTimer(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureTimer);

	// �^�C�}�[�̏�����
	g_nTimer = 120;
	g_nCntDownTimer = 1;
	g_nClearCnt = 0;

	// ���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TIMER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		// �X�R�A�̒��S���W�̐ݒ�
		g_aTimer[nCnt] = D3DXVECTOR3(POS_TIMERX + ((float)nCnt * 40.0f), POS_TIMERY, 0.0f);

		//�X�R�A�̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((float)g_aTimer[nCnt].x - TIMER_SIZEX, (float)g_aTimer[nCnt].y + TIMER_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)g_aTimer[nCnt].x - TIMER_SIZEX, (float)g_aTimer[nCnt].y - TIMER_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((float)g_aTimer[nCnt].x + TIMER_SIZEX, (float)g_aTimer[nCnt].y + TIMER_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)g_aTimer[nCnt].x + TIMER_SIZEX, (float)g_aTimer[nCnt].y - TIMER_SIZEY, 0.0f);

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

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;	// ���_�|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();

	return S_OK;
}

//==============================================================================
// �^�C�}�[�̏I������
//==============================================================================
void UninitTimer(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}
}

//==============================================================================
// �^�C�}�[�̍X�V����
//==============================================================================
void UpdateTimer(void)
{
	// ���[�J���ϐ��錾
	int aNumber[MAX_TIMER];
	int nData = (int)pow(10, (MAX_TIMER - 1));
	PLAYER *Player;
	Player = GetPlayer();

	g_nCntDownTimer++;

	// 1�b���ƂɌ���
	if (g_nCntDownTimer % 60 == 0 && g_nTimer > 0)
	{
		g_nTimer--;
	}

	// �e���̌v�Z�ƃe�N�X�`���̐؂�ւ�
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		aNumber[nCnt] = (g_nTimer / nData) % 10;
		nData /= 10;
		SetVertexTimer(nCnt, aNumber[nCnt]);
	}
}

//==============================================================================
// �^�C�}�[�̕`�揈��
//==============================================================================
void DrawTimer(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffTimer,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTimer);

	// �|���S���̕`��
	for (int nCnt = 0; nCnt < MAX_TIMER; nCnt++)
	{
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}

//==============================================================================
// �^�C�}�[�̒��_���W�擾����
//==============================================================================
void SetVertexTimer(int nIdx, int nNumber)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�|�C���^��4���i�߂�
	pVtx += 4 * nIdx;

	// �e�N�X�`���̒��_���W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTimer->Unlock();
}

//==============================================================================
// �^�C�}�[�̎擾
//==============================================================================
int GetTimer(void)
{
	return g_nTimer;	// �^�C�}�[�̒l���擾����
}

////==============================================================================
//// �X�e�[�W���Ƃ̃^�C�}�[�̐ݒ�
////==============================================================================
//void SetTimer(void)
//{
//	// ���[�J���ϐ��錾
//	int nStage = GetStage();
//
//	switch (nStage)
//	{
//	case 0:
//		g_nTimer = TIMER_0;
//
//		break;
//
//	case 1:
//		g_nTimer = TIMER_1;
//
//		break;
//
//	case 2:
//		g_nTimer = TIMER_2;
//
//		break;
//
//	default:
//		break;
//	}
//	
//}