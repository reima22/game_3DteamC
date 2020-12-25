//==============================================================================
//
// �u���b�N�̕`��kblock.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "block.h"
#include "player.h"
#include "input.h"
#include "sound.h"
#include "gamepad.h"
#include "score.h"
#include "particle.h"
#include "time.h"
#include "stdlib.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			// �u���b�N�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;		// �o�b�t�@�ւ̃|�C���^
BLOCK g_aBlock[BLOCK_MAX];							// �u���b�N�̏��
int g_nSetBlock;
int g_nCntBreak;

//==============================================================================
// �u���b�N�̏���������
//==============================================================================
HRESULT InitBlock(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �����Z�o���猻���������O
	srand((unsigned int)time(0));

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/block000.jpg",
		&g_pTextureBlock);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * BLOCK_MAX,	// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL)))
	{
		return E_FAIL;
	}

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		g_aBlock[nCnt].bUse = false;
		g_aBlock[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCnt].nLife = 3;
	}

	g_nSetBlock = 0;
	g_nCntBreak = 0;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++, pVtx += 4)
	{
		// �u���b�N�̒��S���W
		g_aBlock[nCnt].pos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);

		// �u���b�N�̊e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y + BLOCK_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x, g_aBlock[nCnt].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + BLOCK_SIZEX, g_aBlock[nCnt].pos.y + BLOCK_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCnt].pos.x + BLOCK_SIZEX, g_aBlock[nCnt].pos.y, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//==============================================================================
// �u���b�N�̏I������
//==============================================================================
void UninitBlock(void)
{
	//// ���[�J���ϐ��錾
	//BLOCK *pBlock;
	//// �u���b�N�̎擾
	//pBlock = &g_aBlock[0];
	//// �u���b�N�̈ړ�
	//for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++, pBlock++)
	//{
	//	if (pBlock->bUse == true)
	//	{
	//		pBlock->bUse = false;
	//	}
	//}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
}

//==============================================================================
// �u���b�N�̍X�V����
//==============================================================================
void UpdateBlock(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	BLOCK *pBlock;
	int nBreak = 0;

	// �u���b�N�̎擾
	pBlock = &g_aBlock[0];

	g_nSetBlock++;
	g_nCntBreak++;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// �u���b�N�̈ړ�
	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++, pBlock++, pVtx += 4)
	{
		if (pBlock->bUse == true)
		{
			pBlock->pos += pBlock->move;

			// �u���b�N�̒��_���W�擾
			SetVertexBlock(nCnt);

			if (pBlock->pos.y >= SCREEN_HEIGHT)
			{
				pBlock->bUse = false;
			}

			if (pBlock->bBreak == true)
			{
				if (g_nCntBreak % 40 == 0)
				{
					// �e���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				else if (g_nCntBreak % 20 == 0 && g_nCntBreak % 40 != 0)
				{
					// �e���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(2, 255, 2, 255);
					pVtx[1].col = D3DCOLOR_RGBA(2, 255, 2, 255);
					pVtx[2].col = D3DCOLOR_RGBA(2, 255, 2, 255);
					pVtx[3].col = D3DCOLOR_RGBA(2, 255, 2, 255);
				}
			}

			// �G�̏��
			switch (g_aBlock[nCnt].state)
			{
			case BLOCKSTATE_DAMAGE:
				// �J�E���g���s
				g_aBlock[nCnt].nCntState--;

				// �J�E���g�I��
				if (g_aBlock[nCnt].nCntState <= 0)
				{
					// �ʏ��Ԃֈڍs
					g_aBlock[nCnt].state = BLOCKSTATE_NORMAL;

					// �e���_�J���[�̐ݒ�
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;

			default:
				break;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	nBreak = rand() % BLOCK_SET;

	if (g_nSetBlock == 10 || g_nSetBlock % 400 == 0)
	{
		for (int nCnt = 0; nCnt < BLOCK_SET; nCnt++)
		{
			if (nCnt == nBreak)
			{
				SetBlock(D3DXVECTOR3(40.0f + (nCnt * 80.0f), -20.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 40.0f, 40.0f, 3, true);
			}
			else
			{
				SetBlock(D3DXVECTOR3(40.0f + (nCnt * 80.0f), -20.0f, 0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 40.0f, 40.0f, 0, false);
			}	
		}
	}
}

//==============================================================================
// �u���b�N�̕`�揈��
//==============================================================================
void DrawBlock(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	BLOCK *pBlock;
	pBlock = GetBlock();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffBlock,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBlock);

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++,pBlock++)
	{
		if (pBlock->bUse == true)
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================================
// �u���b�N�̐ݒ�
//==============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight,int nLife,bool bBreak)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < BLOCK_MAX; nCnt++)
	{
		if (g_aBlock[nCnt].bUse == false)
		{
			// �ʒu��ݒ�
			g_aBlock[nCnt].pos = pos;

			// �ړ��͂�ݒ�
			g_aBlock[nCnt].move = move;

			// ���̐ݒ�
			g_aBlock[nCnt].fWidth = fWidth;

			// �����̐ݒ�
			g_aBlock[nCnt].fHeight = fHeight;

			// �ϋv�͂̐ݒ�
			g_aBlock[nCnt].nLife = nLife;

			// �j��̉�
			g_aBlock[nCnt].bBreak = bBreak;

			// ���_���W��ݒ�
			SetVertexBlock(nCnt);

			// �g�p��Ԃֈڍs
			g_aBlock[nCnt].bUse = true;

			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//==============================================================================
// �u���b�N�̒��_���W�擾����
//==============================================================================
void SetVertexBlock(int nIdx)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	BLOCK *pBlock;

	// �G�̎擾
	pBlock = &g_aBlock[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�|�C���^��4���i�߂�
	pVtx += nIdx * 4;

	pBlock += nIdx;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x - g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x - g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y - g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y - g_aBlock[nIdx].fHeight, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//==============================================================================
// �u���b�N�̏��擾
//==============================================================================
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}

//==============================================================================
// �u���b�N�̔j�󔻒�
//==============================================================================
bool HitBlock(int nIdx, int nDamage)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	BLOCK *pBlock;
	int nScore = 0;

	// �G�̎擾
	pBlock = &g_aBlock[0];

	g_aBlock[nIdx].nLife -= nDamage;
	
	// �c��̗͂ɂ�鏈��
	if (g_aBlock[nIdx].nLife <= 0)
	{
		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_EXPLOSION000);

		// �p�[�e�B�N���̔���
		SetEffect(g_aBlock[nIdx].pos, 0.05f, D3DXCOLOR(0.9f, 0.4f, 0.1f, 1.0f), 15.0f, 0.015f);

		// �X�R�A�̐ݒ�
		nScore = 1000;

		//// ���j�����ʒu�̍����ɂ��X�R�A�̔{��
		//if (pEnemy->pos.y >= LOW_SCORE && pEnemy->pos.y < MIDDLE_SCORE)
		//{
		//	nScore *= 2;
		//}
		//else if (pEnemy->pos.y >= MIDDLE_SCORE && pEnemy->pos.y < HIGH_SCORE)
		//{
		//	nScore *= 3;
		//}
		//else if (pEnemy->pos.y >= HIGH_SCORE && pEnemy->pos.y < WINDOW_LOWEST)
		//{
		//	nScore *= 4;
		//}

		// �X�R�A�̉��Z
		AddScore(nScore);

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		// �ǂ̔j��
		g_aBlock[nIdx].bBreak = false;
		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBlock->Unlock();

		g_aBlock[nIdx].bUse = false;

		return true;
	}
	else
	{
		// �G�̏�Ԃ̕ω�
		g_aBlock[nIdx].state = BLOCKSTATE_DAMAGE;
		g_aBlock[nIdx].nCntState = 5;

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_EXPLOSION000);

		// �p�[�e�B�N���̔���
		SetEffect(g_aBlock[nIdx].pos, 0.01f, D3DXCOLOR(0.9f, 0.1f, 0.1f, 1.0f), 3.0f, 0.015f);

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nIdx * 4;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBlock->Unlock();

		return false;
	}
}