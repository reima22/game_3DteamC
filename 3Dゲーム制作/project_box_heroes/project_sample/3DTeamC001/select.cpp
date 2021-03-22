//==============================================================================
//
// �I����ʂ̕`��kselect.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "select.h"
#include "input.h"
#include "fade.h"
#include "gamepad.h"
#include "select_cursor.h"
#include "sound.h"
#include <stdio.h>

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureSelect[ALL_TEX] = {};		// �I����ʃe�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;	// �o�b�t�@�ւ̃|�C���^
Select g_select;

//==============================================================================
// �I����ʂ̏���������
//==============================================================================
HRESULT InitSelect(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	LoadSelect();

	TexSetSelect();

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * ALL_SET,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL)))
	{
		return E_FAIL;
	}

	// �ϐ��̏�����
	for (int nCnt = 0; nCnt < ALL_SET; nCnt++)
	{
		g_select.selectInfo[nCnt].move = D3DXVECTOR3(0.0f, -0.0f, 0.0f);
	}
	g_select.mode = PLAYMODE_0;
	//g_select.chara = CHARA_0;
	g_select.stage = STAGE_0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < ALL_SET; nCnt++, pVtx += 4)
	{
		// �|���S���̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_select.selectInfo[nCnt].pos.x, g_select.selectInfo[nCnt].pos.y + g_select.selectInfo[nCnt].fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_select.selectInfo[nCnt].pos.x, g_select.selectInfo[nCnt].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_select.selectInfo[nCnt].pos.x + g_select.selectInfo[nCnt].fWidth, g_select.selectInfo[nCnt].pos.y + g_select.selectInfo[nCnt].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_select.selectInfo[nCnt].pos.x + g_select.selectInfo[nCnt].fWidth, g_select.selectInfo[nCnt].pos.y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = g_select.selectInfo[nCnt].col;
		pVtx[1].col = g_select.selectInfo[nCnt].col;
		pVtx[2].col = g_select.selectInfo[nCnt].col;
		pVtx[3].col = g_select.selectInfo[nCnt].col;

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0, 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0, 0.0);
		pVtx[2].tex = D3DXVECTOR2(1.0, 1.0);
		pVtx[3].tex = D3DXVECTOR2(1.0, 0.0);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

	// ���̍Đ�
	PlaySound(SOUND_LABEL_BGM006);

	return S_OK;
}

//==============================================================================
// �I����ʂ̏I������
//==============================================================================
void UninitSelect(void)
{
	// �T�E���h�̒�~����
	StopSound();

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < ALL_TEX; nCnt++)
	{
		if (g_pTextureSelect[nCnt] != NULL)
		{
			g_pTextureSelect[nCnt]->Release();
			g_pTextureSelect[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �I����ʂ̍X�V����
//==============================================================================
void UpdateSelect(void)
{
	SelectManager();
}

//==============================================================================
// �I����ʂ̕`�揈��
//==============================================================================
void DrawSelect(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	SelectInfo *pSelect = &g_select.selectInfo[0];

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffSelect,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCnt = 0; nCnt < ALL_SET; nCnt++,pSelect++)
	{
		if (pSelect->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureSelect[pSelect->nType]);

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================================
// �I����ʂ̊Ǘ�
//==============================================================================
void SelectManager(void)
{
	// ���[�J���ϐ��錾
	FADE fade = GetFade();							// �t�F�[�h�̎擾
	SelectInfo *pSelect = &g_select.selectInfo[0];	// �I����ʏ��̎擾
	Cursor *pCursor = &GetCursorS();

	// �ړ����s
	if (g_select.bMove == true)
	{
		// �J�E���g����
		g_select.nMoveCnt++;

		// �ړ��I���ƃ��Z�b�g
		if (g_select.nMoveCnt > (int)SCREEN_HEIGHT / 10)
		{
			g_select.nMoveCnt = 0;
			g_select.bMove = false;
			g_select.bDecide[0] = false;
			g_select.bDecide[1] = false;

			if (g_select.bBack == false)
			{
				g_select.nCntPage++;
			}
			else if (g_select.bBack == true)
			{
				g_select.nCntPage--;
				g_select.bBack = false;
			}
		}

		// �ړ�����
		for (int nCnt = 0; nCnt < ALL_SET; nCnt++, pSelect++)
		{
			if (pSelect->bUse == true && pSelect->st != 0)
			{// �I����ʓ��̃|���S���ړ�
				if (g_select.bBack == false)
				{// �ʏ�ɑI�����ꂽ�Ƃ��̈ړ���
					pSelect->move.y = -SELECT_MOVE;
				}
				else if (g_select.bBack == true)
				{// �L�����Z�����ꂽ�Ƃ��̈ړ�
					pSelect->move.y = SELECT_MOVE;
				}

				if (g_select.bMove == true)
				{// �ړ��͂̉��Z
					pSelect->pos += pSelect->move;
				}
			}
			SetVertexSelect(nCnt);	// ���_���W�̍X�V
		}
	}

	if (fade == FADE_NONE)
	{// �t�F�[�h���Ă��Ȃ��Ƃ�
		switch (g_select.nCntPage)
		{
		case 0:
			if (pCursor->cursor[CURSORTYPE_PLAYER1].nCntBlink >= 60)
			{
				g_select.bMove = true;	// �ړ��J�n
			}

			if (g_select.bDecide[CURSORTYPE_PLAYER1] == false)
			{
				if (BuDo(KEYINFO::KEYINFO_OK, 0) == true)
				{
					PlaySound(SOUND_LABEL_SE_MODESELECT);

					g_select.bDecide[0] = true;

					if (g_select.mode == PLAYMODE_1)
					{
						g_select.b2PlayerOn = true;
					}
				}
			}
			break;

		case 1:
			if (pCursor->cursor[CURSORTYPE_PLAYER1].nCntBlink >= 60)
			{
				if (pCursor->cursor[CURSORTYPE_PLAYER2].nCntBlink >= 60 ||
					pCursor->cursor[CURSORTYPE_CPU].nCntBlink >= 60)
				{
					g_select.bMove = true;
				}
			}

			if (g_select.bDecide[0] == false)
			{
				if (BuDo(KEYINFO::KEYINFO_OK, 0) == true)
				{
					PlaySound(SOUND_LABEL_SE_MODESELECT);

					g_select.bDecide[0] = true;
				}
			}

			if (pCursor->cursor[CURSORTYPE_PLAYER2].bUse == true)
			{
				if (BuDo(KEYINFO::KEYINFO_OK, 1) == true)
				{
					PlaySound(SOUND_LABEL_SE_MODESELECT);

					g_select.bDecide[1] = true;
				}
			}
			else if (pCursor->cursor[CURSORTYPE_CPU].bUse == true)
			{
				if (BuDo(KEYINFO::KEYINFO_OK, 0) == true)
				{
					PlaySound(SOUND_LABEL_SE_MODESELECT);

					g_select.bDecide[1] = true;
				}
			}

			break;

		case 2:

			if (BuDo(KEYINFO::KEYINFO_OK, 0) == true)
			{
				PlaySound(SOUND_LABEL_SE_MODESELECT);

				g_select.bDecide[0] = true;

				SetFade(FADE_OUT, MODE_TUTORIAL);	// ��ʑJ��
			}
			break;
		default:
			break;
		}

		if (g_select.nCntPage > 0)
		{// �L�����Z������
		 

			if (g_select.bMove == false) 
			{
				// ���̍Đ�
				if (GetKeyboardTrigger(KEYINFO_CANCEL) == true || BuDo(KEYINFO::KEYINFO_CANCEL, 0) == true)
				{
					PlaySound(SOUND_LABEL_SE_CANCEL);
					g_select.bMove = true;	// �ړ��J�n
					g_select.bBack = true;	// �L�����Z��
				}

				if (pCursor->cursor[CURSORTYPE_PLAYER2].bUse == true)
				{
					if (BuDo(KEYINFO::KEYINFO_CANCEL, 1) == true)
					{
						PlaySound(SOUND_LABEL_SE_CANCEL);
						g_select.bMove = true;	// �ړ��J�n
						g_select.bBack = true;	// �L�����Z��
					}
				}
			}
			
		}

		//// �I�𖈂̈ړ�����
		//switch (g_select.nCntPage)
		//{
		//case 0:
		//	if (pCursor->cursor[CURSORTYPE_PLAYER1].nCntBlink >= 60)
		//	{
		//		g_select.bMove = true;	// �ړ��J�n
		//	}
		//	break;

		//case 1:
		//	break;

		//case 2:
		//	g_select.bMove = true;
		//	break;

		//default:
		//	break;
		//}

		//if (g_select.b2PlayerOn == true && g_select.nCntPage == 1)
		//{
		//	if (BuDo(KEYINFO::KEYINFO_OK, 1) == true)
		//	{
		//		g_select.bDecide[1] = true;
		//	}
		//}

		CursorManager();
		
		g_select.SType = (SelectType)g_select.nCntPage;

		SelectCursor(g_select.SType);	// �J�[�\������
	}
}

//==============================================================================
// �e�N�X�`���̐ݒ�
//==============================================================================
void TexSetSelect(void)
{
	// ���[�J���ϐ��錾
	//VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �w�i�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < g_select.nNumSelect; nCnt++)
	{
		D3DXCreateTextureFromFile(
			pDevice,
			g_select.selectInfo[nCnt].aFileName,
			&g_pTextureSelect[nCnt]);
	}
}

//==============================================================================
// �e�L�X�g���[�h
//==============================================================================
void LoadSelect(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile;
	char aEqual[2] = { NULL };				// �u=�v�ǂݎ��p�ϐ�
	int nCntFile = 0;						// X�t�@�C���̐�
	int nIdx = 0;							// �p�[�c��
	bool bComment = false;					// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = { NULL };		// �e�L�X�g�ǂݎ��p�ϐ�
	char aSelect[TEXT_LENGTH] = { NULL };	// �|���S�����ǂݍ��ݗp�ϐ�
	char aState[TEXT_LENGTH] = { NULL };	// �ڍ׏��ǂݎ��p�ϐ�

	// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];
	char *pSelect = &aSelect[0];
	char *pState = &aState[0];

	// �f�[�^�̓ǂݍ���
	pFile = fopen("data/TEXT/select.txt", "r");
	if (pFile != NULL)
	{ //�t�@�C���W�J�\
		while (strcmp("END_SCRIPT", pText) != 0)
		{
			aText[0] = { NULL };
			if (bComment == false)
			{// �R�����g�A�E�g���Ă��Ȃ�
				fscanf(pFile, "%s", &aText[0]);

				if (aText[0] == '#')
				{// ������̐擪���u#�v�Ȃ�΃R�����g�A�E�g��
					bComment = true;
				}
				else
				{// �ʏ펞
					if (strcmp("NUM_SELECT", pText) == 0)
					{// ���f���̐�
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &g_select.nNumSelect);
					}
					else if (strcmp("SELECT_FILENAME", pText) == 0)
					{// X�t�@�C�����̓ǂݍ���
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%s", &g_select.selectInfo[nCntFile].aFileName[0]);
						nCntFile++;
					}
					else if (strcmp("SELECT_SET", pText) == 0)
					{// �z�u���
						aSelect[0] = {};
						while (strcmp("END_SELECT_SET", pSelect) != 0)
						{// �z�u���̓ǂݎ��
							fscanf(pFile, "%s", &aSelect[0]);
							if (strcmp("POLYGONSET", pSelect) == 0)
							{
								aState[0] = {};
								while (strcmp("END_POLYGONSET", pState) != 0)
								{
									fscanf(pFile, "%s", &aState[0]);

									if (strcmp("POS", pState) == 0)
									{// �ʒu���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].pos.x);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].pos.y);
										if (g_select.selectInfo[nIdx].st > 1)
										{
											//g_select.selectInfo[nIdx].pos.x += SCREEN_HEIGHT * g_select.selectInfo[nIdx].st;
											g_select.selectInfo[nIdx].pos.y += SCREEN_HEIGHT * (g_select.selectInfo[nIdx].st - 1);
										}
									}
									else if (strcmp("COL", pState) == 0)
									{// �F���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].col.r);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].col.g);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].col.b);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].col.a);
									}
									else if (strcmp("WIDTH", pState) == 0)
									{// ��
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].fWidth);
									}
									else if (strcmp("HEIGHT", pState) == 0)
									{// ����
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &g_select.selectInfo[nIdx].fHeight);
									}
									else if (strcmp("TEXTYPE", pState) == 0)
									{
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &g_select.selectInfo[nIdx].nType);
									}
									else if (strcmp("SELECTTYPE", pState) == 0)
									{
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &g_select.selectInfo[nIdx].st);
									}
								}
								g_select.selectInfo[nIdx].bUse = true;
								nIdx++;
							}
						}
					}
				}
			}
			else if (bComment == true)
			{// �R�����g�A�E�g����
			 // ���[�J���ϐ��錾
				char a = NULL;
				char b = NULL;
				fscanf(pFile, "%c", &a);
				while (a != '\n' && b != '\n')
				{
					fscanf(pFile, "%s", &aText[0]);
					fscanf(pFile, "%c", &b);
				}
				bComment = false;
			}
		}
		g_select.nNumTexSelect = nCntFile;
		fclose(pFile);
	}
	else
	{ // �t�@�C���W�J�s��
	}
}

//==============================================================================
// ���_���X�V
//==============================================================================
void SetVertexSelect(int nIdx)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�|�C���^��4���i�߂�
	pVtx += 4 * nIdx;

	// �e�N�X�`���̒��_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(g_select.selectInfo[nIdx].pos.x, g_select.selectInfo[nIdx].pos.y + g_select.selectInfo[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_select.selectInfo[nIdx].pos.x, g_select.selectInfo[nIdx].pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_select.selectInfo[nIdx].pos.x + g_select.selectInfo[nIdx].fWidth, g_select.selectInfo[nIdx].pos.y + g_select.selectInfo[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_select.selectInfo[nIdx].pos.x + g_select.selectInfo[nIdx].fWidth, g_select.selectInfo[nIdx].pos.y, 0.0f);

	pVtx[0].col = g_select.selectInfo[nIdx].col;
	pVtx[1].col = g_select.selectInfo[nIdx].col;
	pVtx[2].col = g_select.selectInfo[nIdx].col;
	pVtx[3].col = g_select.selectInfo[nIdx].col;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();
}

//==============================================================================
// �I�����[�h�J�[�\���̐���
//==============================================================================
void SelectCursor(SelectType ST)
{
	Cursor *pCursor = &GetCursorS();

	if (g_select.bMove == false)
	{
		switch (ST)
		{
		case SELECTTYPE_MODE:	// �v���C���[�h�I��
			if (g_select.bDecide[0] == false)
			{
				if (GetKeyboardTrigger(KEYINFO_LEFT) == true || BuDo(KEYINFO::KEYINFO_LEFT, 0) == true)
				{
					// ���̍Đ�
					PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

					if (g_select.mode == PLAYMODE_0)
					{
						g_select.mode = PLAYMODE_1;
					}
					else
					{
						g_select.mode = PLAYMODE_0;
					}
				}
				else if (GetKeyboardTrigger(KEYINFO_RIGHT) == true || BuDo(KEYINFO::KEYINFO_RIGHT, 0) == true)
				{
					// ���̍Đ�
					PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

					if (g_select.mode == PLAYMODE_0)
					{
						g_select.mode = PLAYMODE_1;
					}
					else
					{
						g_select.mode = PLAYMODE_0;
					}
				}
			}
			break;

		case SELECTTYPE_CHARA:	// �L�����N�^�[�I��
			if (g_select.bDecide[0] == false)
			{
				if (GetKeyboardTrigger(KEYINFO_LEFT) == true || BuDo(KEYINFO::KEYINFO_LEFT, 0) == true)
				{
					// ���̍Đ�
					PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

					if (g_select.chara[0] == CHARA_0)
					{
						g_select.chara[0] = CHARA_2;
					}
					else if (g_select.chara[0] == CHARA_1)
					{
						g_select.chara[0] = CHARA_0;
					}
					else
					{
						g_select.chara[0] = CHARA_1;
					}
				}
				else if (GetKeyboardTrigger(KEYINFO_RIGHT) == true || BuDo(KEYINFO::KEYINFO_RIGHT, 0) == true)
				{
					// ���̍Đ�
					PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

					if (g_select.chara[0] == CHARA_0)
					{
						g_select.chara[0] = CHARA_1;
					}
					else if (g_select.chara[0] == CHARA_1)
					{
						g_select.chara[0] = CHARA_2;
					}
					else
					{
						g_select.chara[0] = CHARA_0;
					}
				}
			}

			if (g_select.bDecide[1] == false)
			{
				if (pCursor->cursor[CURSORTYPE_PLAYER2].bUse == true)
				{
					if (BuDo(KEYINFO::KEYINFO_LEFT, 1) == true)
					{
						// ���̍Đ�
						PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

						if (g_select.chara[1] == CHARA_0)
						{
							g_select.chara[1] = CHARA_2;
						}
						else if (g_select.chara[1] == CHARA_1)
						{
							g_select.chara[1] = CHARA_0;
						}
						else
						{
							g_select.chara[1] = CHARA_1;
						}
					}
					else if (BuDo(KEYINFO::KEYINFO_RIGHT, 1) == true)
					{
						// ���̍Đ�
						PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

						if (g_select.chara[1] == CHARA_0)
						{
							g_select.chara[1] = CHARA_1;
						}
						else if (g_select.chara[1] == CHARA_1)
						{
							g_select.chara[1] = CHARA_2;
						}
						else
						{
							g_select.chara[1] = CHARA_0;
						}
					}
				}
				else if (pCursor->cursor[CURSORTYPE_CPU].bUse == true)
				{
					if (BuDo(KEYINFO::KEYINFO_LEFT, 0) == true)
					{
						// ���̍Đ�
						PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

						if (g_select.chara[1] == CHARA_0)
						{
							g_select.chara[1] = CHARA_2;
						}
						else if (g_select.chara[1] == CHARA_1)
						{
							g_select.chara[1] = CHARA_0;
						}
						else
						{
							g_select.chara[1] = CHARA_1;
						}
					}
					else if (BuDo(KEYINFO::KEYINFO_RIGHT, 0) == true)
					{
						// ���̍Đ�
						PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

						if (g_select.chara[1] == CHARA_0)
						{
							g_select.chara[1] = CHARA_1;
						}
						else if (g_select.chara[1] == CHARA_1)
						{
							g_select.chara[1] = CHARA_2;
						}
						else
						{
							g_select.chara[1] = CHARA_0;
						}
					}
				}
			}
			
			break;

		case SELECTTYPE_STAGE:	// �X�e�[�W�I��
			if (GetKeyboardTrigger(KEYINFO_LEFT) == true || BuDo(KEYINFO::KEYINFO_LEFT, 0) == true)
			{
				// ���̍Đ�
				PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

				if (g_select.stage == STAGE_0)
				{
					g_select.stage = STAGE_2;
				}
				else if (g_select.stage == STAGE_1)
				{
					g_select.stage = STAGE_0;
				}
				else
				{
					g_select.stage = STAGE_1;
				}
			}
			else if (GetKeyboardTrigger(KEYINFO_RIGHT) == true || BuDo(KEYINFO::KEYINFO_RIGHT, 0) == true)
			{
				// ���̍Đ�
				PlaySound(SOUND_LABEL_SE_PAUSE_SELECT);

				if (g_select.stage == STAGE_0)
				{
					g_select.stage = STAGE_1;
				}
				else if (g_select.stage == STAGE_1)
				{
					g_select.stage = STAGE_2;
				}
				else
				{
					g_select.stage = STAGE_0;
				}
			}
			break;

		default:
			break;
		}
	}
}

//==============================================================================
// �I����ʂ̎擾
//==============================================================================
Select *GetSelect(void)
{
	return &g_select;
}