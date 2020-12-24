//==============================================================================
//
// �t�F�[�h�̕`��kfade.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "fade.h"
#include "input.h"
#include "gamepad.h"

//==============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// �t�F�[�h�̃o�b�t�@�ւ̃|�C���^
FADE g_fade;									// �t�F�[�h�̏��
MODE g_modeNext;								// ���̃��[�h
D3DXCOLOR g_colorFade;							// �t�F�[�h�F
D3DXVECTOR3 g_posFade;							// �t�F�[�h��ʂ̈ʒu

//==============================================================================
// �t�F�[�h�̏���������
//==============================================================================
HRESULT InitFade(MODE modeNext)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// �t�F�[�h����|���S���̒��S���W
	g_posFade = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	// �|���S���̊e���_���W
	pVtx[0].pos = D3DXVECTOR3(g_posFade.x - (SCREEN_WIDTH / 2), g_posFade.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_posFade.x - (SCREEN_WIDTH / 2), g_posFade.y - (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_posFade.x + (SCREEN_WIDTH / 2), g_posFade.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_posFade.x + (SCREEN_WIDTH / 2), g_posFade.y - (SCREEN_HEIGHT / 2), 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// �e���_�J���[�̐ݒ�
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	return S_OK;
}

//==============================================================================
// �t�F�[�h�̏I������
//==============================================================================
void UninitFade(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//==============================================================================
// �t�F�[�h�̍X�V����
//==============================================================================
void UpdateFade(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	MODE mode;

	// ���[�h�̎擾
	mode = GetMode();

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();

	if (g_fade == FADE_IN)
	{
		g_colorFade.a -= 0.01f;

		if (g_colorFade.a <= 0.0f || GetKeyboardTrigger(KEYINFO_OK) == true || IsButtonDown(KEYINFO::KEYINFO_OK) == true)
		{
			if (mode != MODE_GAME)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
			else
			{
				if (g_colorFade <= 0.0f)
				{
					g_fade = FADE_NONE;
				}
			}
		}
	}
	else if (g_fade == FADE_OUT)
	{
		g_colorFade.a += 0.01f;

		if (g_colorFade.a >= 1.0f)
		{
			g_colorFade.a = 1.0f;
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
}

//==============================================================================
// �t�F�[�h�̕`�揈��
//==============================================================================
void DrawFade(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffFade,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,						// �`����J�n���钸�_�C���f�b�N�X
		2);						// �`�悷��v���~�e�B�u��
}

//==============================================================================
// �t�F�[�h�̐ݒ�
//==============================================================================
void SetFade(FADE fade, MODE modeNext)
{
	g_fade = fade;
	g_modeNext = modeNext;
}

//==============================================================================
// �t�F�[�h���̎擾
//==============================================================================
FADE GetFade(void)
{
	return g_fade;
}