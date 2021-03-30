//==============================================================================
//
// �I���J�[�\���̕`��kselect_cursor.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
//#define _CRT_SECURE_NO_WARNINGS
#include "select.h"
#include "select_cursor.h"
#include "gamepad.h"
#include "fade.h"
#include "sound.h"

#define CURSOR_NUM	(3)		// �J�[�\���̐�
#define CURSOR_SIZE (75.0f)	// �J�[�\���̃T�C�Y

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureCursor[CURSOR_NUM] = {};		// �I����ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffCursor = NULL;			// �o�b�t�@�ւ̃|�C���^
Cursor g_Cursor/*[CURSOR_NUM]*/;								// �J�[�\���̍\����

//==============================================================================
// �I����ʂ̏���������
//==============================================================================
HRESULT InitCursor(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/cursor0.png",
		&g_pTextureCursor[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/cursor1.png",
		&g_pTextureCursor[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/cursor2.png",
		&g_pTextureCursor[2]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * CURSOR_NUM,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffCursor,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < CURSOR_NUM; nCnt++)
	{
		g_Cursor.cursor[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Cursor.cursor[nCnt].col = D3DXCOLOR(1.0f, 1.0f,1.0f, 1.0f);
		g_Cursor.cursor[nCnt].fWidth = CURSOR_SIZE;
		g_Cursor.cursor[nCnt].fHeight = CURSOR_SIZE;
		g_Cursor.cursor[nCnt].cursorType = (CURSORTYPE)nCnt;
	}
	g_Cursor.cursor[0].bUse = false;	// 1P�J�[�\��
	g_Cursor.cursor[1].bUse = false;	// 2P�J�[�\��
	g_Cursor.cursor[2].bUse = false;	// CPU�J�[�\��
	g_Cursor.nCharNum = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < CURSOR_NUM; nCnt++, pVtx += 4)
	{
		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Cursor.cursor[nCnt].pos.x, g_Cursor.cursor[nCnt].pos.y + g_Cursor.cursor[nCnt].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Cursor.cursor[nCnt].pos.x, g_Cursor.cursor[nCnt].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Cursor.cursor[nCnt].pos.x + g_Cursor.cursor[nCnt].fWidth, g_Cursor.cursor[nCnt].pos.y + g_Cursor.cursor[nCnt].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Cursor.cursor[nCnt].pos.x + g_Cursor.cursor[nCnt].fWidth, g_Cursor.cursor[nCnt].pos.y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = g_Cursor.cursor[nCnt].col;
		pVtx[1].col = g_Cursor.cursor[nCnt].col;
		pVtx[2].col = g_Cursor.cursor[nCnt].col;
		pVtx[3].col = g_Cursor.cursor[nCnt].col;

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCursor->Unlock();

	return S_OK;
}

//==============================================================================
// �I����ʂ̏I������
//==============================================================================
void UninitCursor(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffCursor != NULL)
	{
		g_pVtxBuffCursor->Release();
		g_pVtxBuffCursor = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < CURSOR_NUM; nCnt++)
	{
		if (g_pTextureCursor[nCnt] != NULL)
		{
			g_pTextureCursor[nCnt]->Release();
			g_pTextureCursor[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �I����ʂ̍X�V����
//==============================================================================
void UpdateCursor(void)
{
	// ���[�J���ϐ��錾
	Select select = *GetSelect();
	FADE fade = GetFade();							// �t�F�[�h�̎擾

	if (fade == FADE_NONE)
	{// �t�F�[�h���Ă��Ȃ��Ƃ�
		g_Cursor.cursor[CURSORTYPE_PLAYER1].bUse = true;	// 1P�J�[�\���̗L����

		switch (select.nCntPage)
		{// �e�I�����̃J�[�\��
		case 0:	// ���[�h�I��
			g_Cursor.nCharNum = 0;
			if (GetKeyboardTrigger(KEYINFO_OK) == true || BuDo(KEYINFO::KEYINFO_OK, 0) == true)
			{
				g_Cursor.cursor[CURSORTYPE_PLAYER1].state = CURSORSTATE_BLINK;
			}
			
			break;

		case 1:	// �L�����N�^�[�I��
			if (select.mode == PLAYMODE_1)
			{
				g_Cursor.cursor[CURSORTYPE_PLAYER2].bUse = true;	// 2P�J�[�\���̗L����
			}

			// 1P��CPU�̎��̑I��
			if (g_Cursor.nCharNum == 0)
			{
				if (BuDo(KEYINFO::KEYINFO_OK, 0) == true)
				{
					g_Cursor.cursor[CURSORTYPE_PLAYER1].state = CURSORSTATE_BLINK;

					if (select.mode == PLAYMODE_0)
					{
						g_Cursor.cursor[CURSORTYPE_CPU].bUse = true;
					}

					g_Cursor.nCharNum++;
				}
			}
			else
			{
				if (g_Cursor.cursor[CURSORTYPE_CPU].bUse == true)
				{
					if (BuDo(KEYINFO::KEYINFO_OK, 0) == true)
					{
						g_Cursor.cursor[CURSORTYPE_CPU].state = CURSORSTATE_BLINK;
					}
				}
			}

			if (g_Cursor.cursor[CURSORTYPE_PLAYER2].bUse == true)
			{
				if (BuDo(KEYINFO::KEYINFO_OK, 1) == true)
				{
					g_Cursor.cursor[CURSORTYPE_PLAYER2].state = CURSORSTATE_BLINK;
				}
			}

			break;

		case 2:
			g_Cursor.nCharNum = 0;
			g_Cursor.cursor[CURSORTYPE_PLAYER2].bUse = false;
			g_Cursor.cursor[CURSORTYPE_CPU].bUse = false;

			break;

		default:
			break;
		}

		if (select.bBack == true)
		{
			g_Cursor.cursor[CURSORTYPE_PLAYER1].state = CURSORSTATE_ERASE;
			g_Cursor.cursor[CURSORTYPE_PLAYER2].state = CURSORSTATE_ERASE;
			g_Cursor.cursor[CURSORTYPE_CPU].state = CURSORSTATE_ERASE;
			g_Cursor.cursor[CURSORTYPE_PLAYER2].bUse = false;
			g_Cursor.cursor[CURSORTYPE_CPU].bUse = false;
		}

	}

	//if (g_Cursor.cursor[CURSORTYPE_PLAYER1].nCntBlink >= 60)
	//{
	//	select.bMove = true;
	//}

	CursorState();

	//if (GetKeyboardTrigger(KEYINFO_CANCEL) == true && select.nCntPage > 0)
	//{// �L�����Z������
	// // ���̍Đ�
	//	PlaySound(SOUND_LABEL_SE_CANCEL);
	//	for (int nCnt = 0; nCnt < CURSORTYPE_MAX; nCnt++)
	//	{
	//		g_Cursor.cursor[nCnt].state = CURSORSTATE_ERASE;
	//	}
	//}

	// ���_���W�X�V
	for (int nCnt = 0; nCnt < CURSORTYPE_MAX; nCnt++)
	{
		if (g_Cursor.cursor[nCnt].bUse == true)
		{
			SetVertexCursor(nCnt);
		}
	}
}


//==============================================================================
// �I����ʂ̕`�揈��
//==============================================================================
void DrawCursor(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CursorInfo *pCursor = &g_Cursor.cursor[0];

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffCursor,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < CURSOR_NUM; nCnt++,pCursor++)
	{
		if (pCursor->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureCursor[nCnt]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================================
// ���_���X�V
//==============================================================================
void SetVertexCursor(int nIdx)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffCursor->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�|�C���^��4���i�߂�
	pVtx += 4 * nIdx;

	// �e�N�X�`���̒��_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_Cursor.cursor[nIdx].pos.x, g_Cursor.cursor[nIdx].pos.y + g_Cursor.cursor[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Cursor.cursor[nIdx].pos.x, g_Cursor.cursor[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Cursor.cursor[nIdx].pos.x + g_Cursor.cursor[nIdx].fWidth, g_Cursor.cursor[nIdx].pos.y + g_Cursor.cursor[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Cursor.cursor[nIdx].pos.x + g_Cursor.cursor[nIdx].fWidth, g_Cursor.cursor[nIdx].pos.y, 0.0f);

	pVtx[0].col = g_Cursor.cursor[nIdx].col;
	pVtx[1].col = g_Cursor.cursor[nIdx].col;
	pVtx[2].col = g_Cursor.cursor[nIdx].col;
	pVtx[3].col = g_Cursor.cursor[nIdx].col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffCursor->Unlock();
}

// �J�[�\���̐���
void CursorManager(void)
{
	Select select = *GetSelect();

	switch (select.nCntPage)
	{
	case 0:	// ���[�h�I����
		switch (select.mode)
		{
		case PLAYMODE_0:
			g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(240.0f, 150.0f, 0.0f);
			break;

		case PLAYMODE_1:
			g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(820.0f, 150.0f, 0.0f);
			break;

		default:
			break;
		}
		break;

	case 1:	// �L�����I����
		if (select.mode == PLAYMODE_0)
		{// 1�l�v���C���[�h
			switch (select.chara[0])
			{
			case CHARA_0:
				g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(240.0f, 150.0f, 0.0f);
				break;

			case CHARA_1:
				g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(530.0f, 150.0f, 0.0f);
				break;

			case CHARA_2:
				g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(820.0f, 150.0f, 0.0f);
				break;

			default:
				break;
			}

			if (select.bDecide[CURSORTYPE_PLAYER1] == true)
			{// 1P�L�����N�^�[���莞
				g_Cursor.cursor[CURSORTYPE_CPU].bUse = true;
				switch (select.chara[1])
				{// CPU�J�[�\��
				case CHARA_0:
					g_Cursor.cursor[CURSORTYPE_CPU].pos = D3DXVECTOR3(385.0f, 150.0f, 0.0f);
					break;

				case CHARA_1:
					g_Cursor.cursor[CURSORTYPE_CPU].pos = D3DXVECTOR3(675.0f, 150.0f, 0.0f);
					break;

				case CHARA_2:
					g_Cursor.cursor[CURSORTYPE_CPU].pos = D3DXVECTOR3(965.0f, 150.0f, 0.0f);
					break;

				default:
					break;
				}
			}
		}
		else
		{	// ��l�v���C
			g_Cursor.cursor[CURSORTYPE_PLAYER2].bUse = true;

			switch (select.chara[0])
			{
			case CHARA_0:
				g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(240.0f, 150.0f, 0.0f);
				break;

			case CHARA_1:
				g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(530.0f, 150.0f, 0.0f);
				break;

			case CHARA_2:
				g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(820.0f, 150.0f, 0.0f);
				break;

			default:
				break;
			}

			switch (select.chara[1])
			{// CPU�J�[�\��
			case CHARA_0:
				g_Cursor.cursor[CURSORTYPE_PLAYER2].pos = D3DXVECTOR3(385.0f, 150.0f, 0.0f);
				break;

			case CHARA_1:
				g_Cursor.cursor[CURSORTYPE_PLAYER2].pos = D3DXVECTOR3(675.0f, 150.0f, 0.0f);
				break;

			case CHARA_2:
				g_Cursor.cursor[CURSORTYPE_PLAYER2].pos = D3DXVECTOR3(965.0f, 150.0f, 0.0f);
				break;

			default:
				break;
			}
		}


		break;

	case 2:	// �X�e�[�W�I����
		switch (select.stage)
		{
		case STAGE_0:
			g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(240.0f, 150.0f, 0.0f);
			break;

		case STAGE_1:
			g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(530.0f, 150.0f, 0.0f);
			break;

		case STAGE_2:
			g_Cursor.cursor[CURSORTYPE_PLAYER1].pos = D3DXVECTOR3(820.0f, 150.0f, 0.0f);
			break;

		default:
			break;
		}

		break;

	default:
		break;
	}
}

// �J�[�\���̎擾
Cursor GetCursorS(void)
{
	return g_Cursor;
}

// �J�[�\���̏��
void CursorState(void)
{
	// ���[�J���ϐ��錾
	CursorInfo *pCursor = &g_Cursor.cursor[0];
	Select select = *GetSelect();

	for (int nCnt = 0; nCnt < CURSORTYPE_MAX; nCnt++,pCursor++)
	{
		switch (pCursor->state)
		{
		case CURSORSTATE_NORMAL:	// �ʏ펞
			pCursor->col.a = 1.0f;
			break;

		case CURSORSTATE_BLINK:		// �_�Ŏ�
			pCursor->nCntBlink++;
			if (pCursor->nCntBlink % 2 == 0)
			{
				pCursor->col.a = 1.0f;	// �o��
			}
			else
			{
				pCursor->col.a = 0.0f;	// ����
			}

			if (select.bMove == true)
			{
				g_Cursor.bBlinkEnd = true;
			}

			if (g_Cursor.bBlinkEnd == true)
			{
				pCursor->nCntBlink = 0;
				pCursor->state = CURSORSTATE_ERASE;	// ���ŏ�Ԃ�
			}

			break;
			
		case CURSORSTATE_ERASE:		// ���Ŏ�
			pCursor->col.a = 0.0f;	
			g_Cursor.bBlinkEnd = false;

			if (select.bMove == false)
			{	
				pCursor->state = CURSORSTATE_NORMAL;	// �ʏ��Ԃ�
			}

			break;

		default:
			break;
		}
	}
}