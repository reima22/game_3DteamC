//==============================================================================
//
// �e�̕`��kbullet.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "bullet.h"
#include "player.h"
//#include "enemy.h"
//#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "input.h"
#include "particle.h"
#include "gamepad.h"
#include "block.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define ATK_BULLETA		(3)		// �eA�̍U����
#define BULLETA_SIZEX	(5)		// �eA�̕�
#define BULLETA_SIZEY	(10)	// �eA�̍���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;	// �e�e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// �e�o�b�t�@�ւ̃|�C���^
BULLET g_aBullet[BULLETNUM];							// �e�̏��
//SETBULLET State;										// �e�̏��
//int g_nCntType;											// �e�̑��U��ԃJ�E���g
//D3DXVECTOR3 g_rotMissile;								// �~�T�C���̉�]�p
//float g_fLengthMissile;									// �~�T�C���̑Ίp���̒���
//float g_fAngleMissile;									// �~�T�C���̑Ίp���̊p�x

//==============================================================================
// �e�̏���������
//==============================================================================
HRESULT InitBullet(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/bullet000.png",
		&g_pTextureBullet);

	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet001.png",
	//	&g_pTextureBullet[1]);
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet002.png",
	//	&g_pTextureBullet[2]);
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet003.png",
	//	&g_pTextureBullet[3]);
	//D3DXCreateTextureFromFile(
	//	pDevice,
	//	"data/TEXTURE/bullet_enemy000.png",
	//	&g_pTextureBullet[4]);

	// �ϐ��̏���������
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// ���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * BULLETNUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++)
	{
		// �e�̒��S���W�̐ݒ�
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f ,0.0f);

		// �e�̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y + BULLETA_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y - BULLETA_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y + BULLETA_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y - BULLETA_SIZEY, 0.0f);

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

		pVtx += 4;	// ���_�|�C���^��4���i�߂�
	}
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//==============================================================================
// �e�̏I������
//==============================================================================
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//==============================================================================
// �e�̍X�V����
//==============================================================================
void UpdateBullet(void)
{
	// ���[�J���ϐ��錾
	//PLAYER *Player;

	// �v���C���[�̎擾
	//Player = GetPlayer();

	// �e�̖�������
	HitBullet();
}

//==============================================================================
// �e�̕`�揈��
//==============================================================================
void DrawBullet(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	BULLET *pBullet;

	// �e�̎擾
	pBullet = &g_aBullet[0];

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffBullet,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++,pBullet++)
	{
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		// �|���S���̐���
		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCntBullet * 4,			// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}	
	}					
}

//==============================================================================
// �e�̐ݒ�
//==============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	BULLET *pBullet;

	// �e�̎擾
	pBullet = &g_aBullet[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	// �e�̐ݒ�
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			// �ʒu��ݒ�
			pBullet->pos = pos;

			// �ړ��ʂ�ݒ�
			pBullet->move = move;

			// ������ݒ�
			pBullet->nLife = nLife;

			// ���_���W��ݒ�
			SetVertexBullet(nCntBullet);

			// �e���g�p����
			pBullet->bUse = true;
			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//==============================================================================
// �e�̖���
//==============================================================================
void HitBullet(void)
{
	// ���[�J���ϐ��錾
	BULLET *pBullet;
	BLOCK *pBlock;
	PLAYER *Player;
	int nScore = 0;

	// �e�̎擾
	pBullet = &g_aBullet[0];

	// �G�̎擾
	pBlock = GetBlock();

	// �v���C���[�̎擾
	Player = GetPlayer();

	// �e�̓����蔻��ƓG�����̔���
	for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{ // �e���g�p����Ă����ꍇ
			// �p�[�e�B�N���̐ݒ�
			SetEffect(pBullet->pos, 0.0f, D3DXCOLOR(0.9f, 0.01f, 0.01f, 1.0f), 7.0f, 0.15f);

			// �ʒu�̍X�V
			pBullet->pos += pBullet->move;

			// �ǂƂ̓����蔻��
			for (int nCntBlock = 0; nCntBlock < BLOCK_MAX; nCntBlock++, pBlock++)
			{
				if (pBlock->bUse == true)
				{ // �ǂ��L���̏ꍇ
					if (pBullet->pos.y - BULLETA_SIZEY <= pBlock->pos.y + BLOCK_SIZEY &&
						pBullet->pos.x + BULLETA_SIZEX >= pBlock->pos.x - BLOCK_SIZEX &&
						pBullet->pos.x - BULLETA_SIZEX <= pBlock->pos.x + BLOCK_SIZEX &&
						pBullet->pos.y + BULLETA_SIZEY >= pBlock->pos.y - BLOCK_SIZEY)
					{ // �ʏ�G�̖����͈�
						if (pBlock->bBreak == true)
						{
							// �j�󏈗�
							HitBlock(nCntBlock, 1);
						}

						// �e�̔j��
						pBullet->bUse = false;
					}
				}
			}

			// �G���̍X�V
			//pEnemy = GetEnemy();

			// ���_���W�̍X�V
			SetVertexBullet(nCntBullet);

			// �����`�F�b�N
			pBullet->nLife -= 2;
			if (pBullet->nLife <= 0)
			{
				pBullet->bUse = false;
			}

			// ��ʊO�`�F�b�N
			if (pBullet->pos.y <= 0.0f || pBullet->pos.y >= SCREEN_HEIGHT || pBullet->pos.x <= 0.0f || pBullet->pos.x >= SCREEN_WIDTH)
			{
				pBullet->bUse = false;
			}
		}
	}
}

//==============================================================================
// �e�̒��_���W�̐ݒ�
//==============================================================================
void SetVertexBullet(int nIdx)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	BULLET *pBullet;

	// �e�̎擾
	pBullet = &g_aBullet[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0,0,(void**)&pVtx,0);

	// ���_�|�C���^��4���i�߂�
	pVtx += 4 * nIdx;

	// �o���b�g�|�C���^��i�߂�
	pBullet += nIdx;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETA_SIZEX, g_aBullet[nIdx].pos.y + BULLETA_SIZEY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETA_SIZEX, g_aBullet[nIdx].pos.y - BULLETA_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETA_SIZEX, g_aBullet[nIdx].pos.y + BULLETA_SIZEY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETA_SIZEX, g_aBullet[nIdx].pos.y - BULLETA_SIZEY, 0.0f);
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}