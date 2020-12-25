//==============================================================================
//
// UI�̕`��kui.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "ui.h"
#include "player.h"
#include "input.h"
//#include "enemy.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_UI		(3)		// UI�̐�
#define UI_SIZEX	(50.0f)	// UI�̕�
#define UI_SIZEY	(30.0f)	// UI�̍���
#define UI_LIFE		(D3DXVECTOR3(60.0f, 40.0f, 0.0f))	// LIFE��UI�̈ʒu
#define UI_TIME		(D3DXVECTOR3(520.0f, 50.0f, 0.0f))	// TIME��UI�̈ʒu
#define UI_SCORE	(D3DXVECTOR3(1025.0f, 40.0f, 0.0f))	// SCORE��UI�̈ʒu

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureUI[MAX_UI] = {};	// UI�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;	// �o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_posUI[MAX_UI];					// UI�̔z�u

//==============================================================================
// UI�̏���������
//==============================================================================
HRESULT InitUI(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/ui_life.png",
		&g_pTextureUI[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/ui_time.png",
		&g_pTextureUI[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/ui_score.png",
		&g_pTextureUI[2]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_UI,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL)))
	{
		return E_FAIL;
	}

	// UI�|���S���̏����z�u
	SetInitUI();

	return S_OK;
}

//==============================================================================
// UI�̏I������
//==============================================================================
void UninitUI(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAX_UI; nCnt++)
	{
		if (g_pTextureUI[nCnt] != NULL)
		{
			g_pTextureUI[nCnt]->Release();
			g_pTextureUI[nCnt] = NULL;
		}
	}
}

//==============================================================================
// UI�̍X�V����
//==============================================================================
void UpdateUI(void)
{
}

//==============================================================================
// UI�̕`�揈��
//==============================================================================
void DrawUI(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffUI,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCnt = 0; nCnt < MAX_UI; nCnt++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureUI[nCnt]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}

//==============================================================================
// UI�̃|���S���̏����ݒ�
//==============================================================================
void SetInitUI(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffUI->Lock(0, 0, (void**)&pVtx, 0);

	// UI�̒��S���W
	g_posUI[0] = UI_LIFE;	// LIFE��UI�ʒu
	g_posUI[1] = UI_TIME;	// TIME��UI�ʒu
	g_posUI[2] = UI_SCORE;	// SCORE��UI�ʒu

	for (int nCnt = 0; nCnt < MAX_UI; nCnt++, pVtx += 4)
	{
		// UI�̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_posUI[nCnt].x - UI_SIZEX, g_posUI[nCnt].y + UI_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posUI[nCnt].x - UI_SIZEX, g_posUI[nCnt].y - UI_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posUI[nCnt].x + UI_SIZEX, g_posUI[nCnt].y + UI_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posUI[nCnt].x + UI_SIZEX, g_posUI[nCnt].y - UI_SIZEY, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		if (nCnt == 0)
		{
			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);
		}
		else
		{
			// �e���_�J���[�̐ݒ�
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}


		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffUI->Unlock();
}