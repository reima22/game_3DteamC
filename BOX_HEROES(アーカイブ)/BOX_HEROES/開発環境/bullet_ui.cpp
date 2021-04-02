//==============================================================================
//
// �X�R�A�̕`��kscore.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "bullet_ui.h"
#include "player.h"
#include "game.h"
#include "math.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define UI_SIZE		(D3DXVECTOR3(100.0f,60.0f,0.0f))
#define NUM_SIZE	(D3DXVECTOR3(20.0f,60.0f,0.0f))

#define POS_1P		(D3DXVECTOR3(0.0f,660.0f,0.0f))
#define POS_2P		(D3DXVECTOR3(640.0f,660.0f,0.0f))

#define POS_1P_NUM	(D3DXVECTOR3(110.0f,660.0f,0.0f))
#define POS_2P_NUM	(D3DXVECTOR3(750.0f,660.0f,0.0f)) 

#define POS_SCOREX	(1100.0f)	// �X�R�A�̏�ꌅ�̒��SX���W
#define POS_SCOREY	(40.0f)	// �X�R�A�̏�ꌅ�̒��SY���W

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBulletUI[TEX_BULLET_UI] = {};	// �e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBulletUI = NULL;			// �o�b�t�@�ւ̃|�C���^
BulletUI bu[PLAYERNUM_MAX];
										
//==============================================================================
// �X�R�A�̏���������
//==============================================================================
HRESULT InitBulletUI(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer = GetPlayer();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/bullet_ui.png",
		&g_pTextureBulletUI[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureBulletUI[1]);

	// �X�R�A�̈ʒu���W�̏�����
	for (int nCnt = 0; nCnt < PLAYERNUM_MAX; nCnt++)
	{
		for (int nCntUI = 0; nCntUI < MAX_UI_NUM; nCntUI++)
		{
			bu[nCnt].posNum[nCntUI] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}



	bu[0].posLogo = POS_1P;
	bu[1].posLogo = POS_2P;

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		bu[0].posNum[nCnt] = D3DXVECTOR3(POS_1P_NUM.x + nCnt * 30.0f, POS_1P_NUM.y, 0.0f);
		bu[1].posNum[nCnt] = D3DXVECTOR3(POS_2P_NUM.x + nCnt * 30.0f, POS_2P_NUM.y, 0.0f);
	}

	// ���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBulletUI,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET_UI; nCnt++,pVtx += 4)
	{
		if (nCnt <= 1)
		{
			//�X�R�A�̒��_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(bu[nCnt].posLogo.x, bu[nCnt].posLogo.y + UI_SIZE.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(bu[nCnt].posLogo.x, bu[nCnt].posLogo.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(bu[nCnt].posLogo.x + UI_SIZE.x, bu[nCnt].posLogo.y + UI_SIZE.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(bu[nCnt].posLogo.x + UI_SIZE.x, bu[nCnt].posLogo.y, 0.0f);
		}
		else
		{
			if (nCnt == 2)
			{
				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(bu[0].posNum[0].x, bu[0].posNum[0].y + NUM_SIZE.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(bu[0].posNum[0].x, bu[0].posNum[0].y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(bu[0].posNum[0].x + NUM_SIZE.x, bu[0].posNum[0].y + NUM_SIZE.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(bu[0].posNum[0].x + NUM_SIZE.x, bu[0].posNum[0].y, 0.0f);
			}																 
			else if (nCnt == 3)
			{
				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(bu[0].posNum[1].x, bu[0].posNum[1].y + NUM_SIZE.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(bu[0].posNum[1].x, bu[0].posNum[1].y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(bu[0].posNum[1].x + NUM_SIZE.x, bu[0].posNum[1].y + NUM_SIZE.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(bu[0].posNum[1].x + NUM_SIZE.x, bu[0].posNum[1].y, 0.0f);
			}
			else if (nCnt == 4)
			{
				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(bu[0].posNum[2].x, bu[0].posNum[2].y + NUM_SIZE.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(bu[0].posNum[2].x, bu[0].posNum[2].y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(bu[0].posNum[2].x + NUM_SIZE.x, bu[0].posNum[2].y + NUM_SIZE.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(bu[0].posNum[2].x + NUM_SIZE.x, bu[0].posNum[2].y, 0.0f);
			}
			else if (nCnt == 5)
			{
				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(bu[1].posNum[0].x, bu[1].posNum[0].y + NUM_SIZE.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(bu[1].posNum[0].x, bu[1].posNum[0].y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(bu[1].posNum[0].x + NUM_SIZE.x, bu[1].posNum[0].y + NUM_SIZE.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(bu[1].posNum[0].x + NUM_SIZE.x, bu[1].posNum[0].y, 0.0f);
			}
			else if (nCnt == 6)
			{
				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(bu[1].posNum[1].x, bu[1].posNum[1].y + NUM_SIZE.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(bu[1].posNum[1].x, bu[1].posNum[1].y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(bu[1].posNum[1].x + NUM_SIZE.x, bu[1].posNum[1].y + NUM_SIZE.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(bu[1].posNum[1].x + NUM_SIZE.x, bu[1].posNum[1].y, 0.0f);
			}
			else
			{
				//�X�R�A�̒��_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(bu[1].posNum[2].x, bu[1].posNum[2].y + NUM_SIZE.y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(bu[1].posNum[2].x, bu[1].posNum[2].y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(bu[1].posNum[2].x + NUM_SIZE.x, bu[1].posNum[2].y + NUM_SIZE.y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(bu[1].posNum[2].x + NUM_SIZE.x, bu[1].posNum[2].y, 0.0f);
			}

		}


		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

		// �e�N�X�`�����_���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBulletUI->Unlock();

	return S_OK;
}

//==============================================================================
// �X�R�A�̏I������
//==============================================================================
void UninitBulletUI(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBulletUI != NULL)
	{
		g_pVtxBuffBulletUI->Release();
		g_pVtxBuffBulletUI = NULL;
	}

	for (int nCnt = 0; nCnt < TEX_BULLET_UI; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (g_pTextureBulletUI[nCnt] != NULL)
		{
			g_pTextureBulletUI[nCnt]->Release();
			g_pTextureBulletUI[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �X�R�A�̍X�V����
//==============================================================================
void UpdateBulletUI(void)
{
	// ���[�J���ϐ��錾
	int aNumber[MAX_UI_NUM];
	int nData = (int)pow(10, (MAX_UI_NUM - 1));
	Player *pPlayer = GetPlayer();

	bu[0].nBullet = pPlayer->nBullet;
	pPlayer++;
	bu[1].nBullet = pPlayer->nBullet;

	// �e���̌v�Z�ƃe�N�X�`���̐؂�ւ�
	for (int nCntUI = 0; nCntUI < PLAYERNUM_MAX; nCntUI++)
	{
		nData = (int)pow(10, (MAX_UI_NUM - 1));

		for (int nCnt = 0; nCnt < MAX_UI_NUM; nCnt++)
		{
			aNumber[nCnt] = (bu[nCntUI].nBullet / nData) % 10;
			nData /= 10;
			SetVertexBulletUI(nCnt, aNumber[nCnt], nCntUI);
		}
	}
}

//==============================================================================
// �X�R�A�̕`�揈��
//==============================================================================
void DrawBulletUI(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffBulletUI,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCnt = 0; nCnt < MAX_BULLET_UI; nCnt++)
	{
		if (nCnt <= 1)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBulletUI[0]);
		}
		else
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBulletUI[1]);
		}


		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}

//==============================================================================
// �X�R�A�̒��_���W�擾����
//==============================================================================
void SetVertexBulletUI(int nIdx, int nNumber, int nCnt)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�|�C���^��4���i�߂�
	pVtx += 4 * (nIdx + 2);

	if (nCnt == 1)
	{
		pVtx += 4 * 3;
	}

	// �e�N�X�`���̒��_���W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBulletUI->Unlock();
}