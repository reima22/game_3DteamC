//==============================================================================
//
// �w�i�|���S���̕`��kbg.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "bg.h"
#include "player.h"
#include "input.h"
#include "game.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_BG		(2)			// �w�i�̎��
#define MTNPOSY		(620.0f)	// �R�w�i��Y���W
#define MTNSIZEY	(100.0f)	// �R�w�i�̍���

//==============================================================================
// �w�i�̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 posBg;	// ��w�i�̈ʒu
	D3DXVECTOR3 posMtn;	// �R�w�i�̈ʒu
	D3DXCOLOR colBg;	// ��w�i�̐F
	D3DXCOLOR colMtn;	// �R�w�i�̐F
	float fMoveBgX;		// �w�i��X���ړ���
	int nCntAnim;		// �A�j���[�V�����J�E���^�[
} BG;

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_apTextureBg[MAX_BG] = {};	// �w�i�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	// �o�b�t�@�ւ̃|�C���^
BG Bg;
//D3DXVECTOR3 g_posBg;							// �w�i�̈ʒu
//D3DXVECTOR3 g_posMtn;							// �R�̈ʒu
//int g_nCntAnim;								// �A�j���[�V�����J�E���^�[
//float g_fMoveBgX;								// ��w�i�̈ړ���X

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
		"data/TEXTURE/sky000.jpg",
		&g_apTextureBg[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/mountain000.png",
		&g_apTextureBg[1]);

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
	Bg.colBg = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Bg.colMtn = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	// �w�i�̒��S���W
	Bg.posBg = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(Bg.posBg.x - (SCREEN_WIDTH / 2), Bg.posBg.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Bg.posBg.x - (SCREEN_WIDTH / 2), Bg.posBg.y - (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Bg.posBg.x + (SCREEN_WIDTH / 2), Bg.posBg.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Bg.posBg.x + (SCREEN_WIDTH / 2), Bg.posBg.y - (SCREEN_HEIGHT / 2), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = Bg.colBg;
	pVtx[1].col = Bg.colBg;
	pVtx[2].col = Bg.colBg;
	pVtx[3].col = Bg.colBg;

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f / 4.0f, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	// �w�i�̒��S���W
	Bg.posMtn = D3DXVECTOR3(SCREEN_WIDTH / 2, MTNPOSY, 0.0f);

	// �|���S���̊e���_���W
	pVtx[4].pos = D3DXVECTOR3(Bg.posMtn.x - (SCREEN_WIDTH / 2), Bg.posMtn.y + MTNSIZEY, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(Bg.posMtn.x - (SCREEN_WIDTH / 2), Bg.posMtn.y - MTNSIZEY, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(Bg.posMtn.x + (SCREEN_WIDTH / 2), Bg.posMtn.y + MTNSIZEY, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(Bg.posMtn.x + (SCREEN_WIDTH / 2), Bg.posMtn.y - MTNSIZEY, 0.0f);

	// rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[4].col = Bg.colMtn;
	pVtx[5].col = Bg.colMtn;
	pVtx[6].col = Bg.colMtn;
	pVtx[7].col = Bg.colMtn;

	// ���_���W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.25f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.75f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.75f, 0.0f);

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
	int nStage = GetStage();	// �X�e�[�W�̎擾

	StageBg(nStage);	// �X�e�[�W���Ƃ̔w�i�̐ݒ�

	Bg.nCntAnim++;		// �A�j���[�V�����J�E���^�[�X�V

	// �e�N�X�`���̍X�V
	if ((Bg.nCntAnim % 2) == 0)
	{
		// �e�N�X�`���̃p�^�[���̍X�V
		Bg.fMoveBgX += 0.0002f;

		// ���_�o�b�t�@�����b�N����
		g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`���̒��_���W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(0.0f + Bg.fMoveBgX, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + Bg.fMoveBgX, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((1.0f / 4.0f) + Bg.fMoveBgX, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((1.0f / 4.0f) + Bg.fMoveBgX, 0.0f);
		
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

//==============================================================================
// �X�e�[�W���Ƃ̔w�i�F�ݒ�
//==============================================================================
void StageBg(int nStage)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	if (nStage == 1)
	{
		Bg.colBg = D3DXCOLOR(0.8f, 0.5f, 0.3f, 1.0f);
		Bg.colMtn = D3DXCOLOR(0.8f, 0.5f, 0.3f, 1.0f);
	}
	else if (nStage == 2)
	{
		Bg.colBg = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		Bg.colMtn.a = 0.0f;
	}

	// ���_�o�b�t�@�����b�N����
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = Bg.colBg;
	pVtx[1].col = Bg.colBg;
	pVtx[2].col = Bg.colBg;
	pVtx[3].col = Bg.colBg;

	pVtx[4].col = Bg.colMtn;
	pVtx[5].col = Bg.colMtn;
	pVtx[6].col = Bg.colMtn;
	pVtx[7].col = Bg.colMtn;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBg->Unlock();
}