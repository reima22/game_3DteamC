//==============================================================================
//
// �e�̕`��kbullet.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "bullet.h"
#include "camera.h"
#include "model.h"
#include "input.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define BULLETNUM		(256)	// �e�̍ő吔
//#define ATK_BULLETA		(3)		// �eA�̍U����
//#define ATK_BULLETB		(2)		// �eB�̍U����
//#define ATK_BULLETC		(4)		// �eC�̍U����
//#define ATK_BULLETD		(2)		// �eD�̍U����
#define BULLETA_SIZEX	(2)	// �eA�̕�
#define BULLETA_SIZEY	(2)	// �eA�̍���
//#define BULLETB_SIZEX	(25)	// �eB�̕�
//#define BULLETB_SIZEY	(10)	// �eB�̍���
//#define BULLETC_SIZEX	(5)		// �eC�̕�
//#define BULLETC_SIZEY	(10)	// �eC�̍���
//#define BULLETD_SIZEX	(25)	// �eD�̕�
//#define BULLETD_SIZEY	(10)	// �eD�̍���
//#define ENEMY_BULLETX	(10)	// �G�̒e�̕�
//#define ENEMY_BULLETY	(10)	// �G�̒e�̍���

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;	// �e�e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// �e�o�b�t�@�ւ̃|�C���^
BULLET g_aBullet[BULLETNUM];							// �e�̏��
D3DXVECTOR3 g_aTest[1];

//==============================================================================
// �e�̏���������
//==============================================================================
HRESULT InitBullet(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/bullet_enemy000.png",
		&g_pTextureBullet);

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
		sizeof(VERTEX_3D) * 4 * BULLETNUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
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
		// �e�̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y - BULLETA_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y + BULLETA_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y - BULLETA_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLETA_SIZEX, g_aBullet[nCntBullet].pos.y + BULLETA_SIZEY, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// �e���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

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
	for (int nCnt = 0; nCnt < BULLETNUM; nCnt++)
	{
		if (g_aBullet[nCnt].bUse == true)
		{
			//// ���_���W�̍X�V
			//SetVertexBullet(nCnt);

			// �ʒu�̍X�V
			g_aBullet[nCnt].pos += g_aBullet[nCnt].move;

			g_aBullet[nCnt].nLife -= 1;

			if (g_aBullet[nCnt].nLife <= 0)
			{
				g_aBullet[nCnt].bUse = false;
			}
		}

	}
}

//==============================================================================
// �e�̕`�揈��
//==============================================================================
void DrawBullet(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���C�g���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g�̍X�V
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	for (int nCnt = 0; nCnt < BULLETNUM; nCnt++)
	{
		// �|���S���̐���
		if (g_aBullet[nCnt].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aBullet[nCnt].mtxWorld);

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aBullet[nCnt].mtxWorld, NULL, &mtxView);
			g_aBullet[nCnt].mtxWorld._41 = 0.0f;
			g_aBullet[nCnt].mtxWorld._42 = 0.0f;
			g_aBullet[nCnt].mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCnt].pos.x, g_aBullet[nCnt].pos.y, g_aBullet[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aBullet[nCnt].mtxWorld, &g_aBullet[nCnt].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCnt].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(
				0,
				g_pVtxBuffBullet,
				0,
				sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}

	//// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(
	//	0,
	//	g_pVtxBuffBullet,
	//	0,
	//	sizeof(VERTEX_3D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_3D);

	//for (int nCnt = 0; nCnt < BULLETNUM; nCnt++)
	//{
	//	// �|���S���̐���
	//	if (g_aBullet[nCnt].bUse == true)
	//	{
	//		// �e�N�X�`���̐ݒ�
	//		pDevice->SetTexture(0, g_pTextureBullet);

	//		pDevice->DrawPrimitive(
	//			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
	//			nCnt * 4,			// �`����J�n���钸�_�C���f�b�N�X
	//			2);						// �`�悷��v���~�e�B�u��
	//	}
	//}

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���C�g���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//==============================================================================
// �e�̐ݒ�
//==============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
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

			//pBullet->pos.x /= 2.0f;

			// �ړ��͂�ݒ�
			pBullet->move = move;

			// ������ݒ�
			pBullet->nLife = nLife;

			//// ���_���W��ݒ�
			//SetVertexBullet(nCntBullet);

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
	//// ���[�J���ϐ��錾
	//BULLET *pBullet;
	//int nScore = 0;

	//// �e�̎擾
	//pBullet = &g_aBullet[0];

	//// �e�̓����蔻��ƓG�����̔���
	//for (int nCntBullet = 0; nCntBullet < BULLETNUM; nCntBullet++, pBullet++)
	//{
	//	if (pBullet->bUse == true)
	//	{ // �e���g�p����Ă����ꍇ
	//		if (pBullet->nType == 0)
	//		{ // �eA(�ʏ�e)�̏ꍇ
	//		  // �p�[�e�B�N���̐ݒ�
	//			SetEffect(pBullet->pos, 0.0f, D3DXCOLOR(0.9f, 0.01f, 0.01f, 1.0f), 7.0f, 0.15f);

	//			// �ʒu�̍X�V
	//			pBullet->pos += pBullet->move;

	//			// �G�Ƃ̓����蔻��
	//			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	//			{
	//				if (pEnemy->bUse == true)
	//				{ // �G���L���̏ꍇ
	//					if (pBullet->pos.y - BULLETA_SIZEY <= pEnemy->pos.y + ENEMY_SIZEY &&
	//						pBullet->pos.x + BULLETA_SIZEX >= pEnemy->pos.x - ENEMY_SIZEX &&
	//						pBullet->pos.x - BULLETA_SIZEX <= pEnemy->pos.x + ENEMY_SIZEX &&
	//						pBullet->pos.y + BULLETA_SIZEY >= pEnemy->pos.y - ENEMY_SIZEY &&
	//						pEnemy->nType != 5)
	//					{ // �ʏ�G�̖����͈�
	//						if (pBullet->type == BULLETTYPE_PLAYER)
	//						{
	//							// �G�̓����蔻��ƃ_���[�W
	//							HitEnemy(nCntEnemy, ATK_BULLETA);

	//							// �e�̔j��
	//							pBullet->bUse = false;
	//						}
	//					}

	//					if (pBullet->pos.y - BULLETA_SIZEY <= pEnemy->pos.y + BIGENEMY_SIZEY &&
	//						pBullet->pos.x + BULLETA_SIZEX >= pEnemy->pos.x - BIGENEMY_SIZEX &&
	//						pBullet->pos.x - BULLETA_SIZEX <= pEnemy->pos.x + BIGENEMY_SIZEX &&
	//						pBullet->pos.y + BULLETA_SIZEY >= pEnemy->pos.y - BIGENEMY_SIZEY &&
	//						pEnemy->nType == 5 && pEnemy->pos.y == 120)
	//					{ // �{�X�G�̖����͈�
	//						if (pBullet->type == BULLETTYPE_PLAYER)
	//						{
	//							// �G�̓����蔻��ƃ_���[�W
	//							HitEnemy(nCntEnemy, ATK_BULLETA);

	//							// �e�̔j��
	//							pBullet->bUse = false;
	//						}
	//					}
	//				}
	//			}
	//		}
	//		else if (pBullet->nType == 1)
	//		{ // �eB(�E�F�[�u)�̏ꍇ
	//		  // �p�[�e�B�N���̐ݒ�
	//			SetEffect(pBullet->pos, 0.0f, D3DXCOLOR(0.9f, 0.7f, 0.2f, 0.01f), 15.0f, 0.001f);

	//			// �ʒu�̍X�V
	//			pBullet->pos += pBullet->move;

	//			// �G�Ƃ̓����蔻��
	//			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	//			{
	//				if (pEnemy->bUse == true)
	//				{ // �G���L���̏ꍇ
	//					if (pBullet->pos.y - BULLETB_SIZEY <= pEnemy->pos.y + ENEMY_SIZEY &&
	//						pBullet->pos.x + 10 >= pEnemy->pos.x - ENEMY_SIZEX &&
	//						pBullet->pos.x - 10 <= pEnemy->pos.x + ENEMY_SIZEX &&
	//						pBullet->pos.y + BULLETB_SIZEY >= pEnemy->pos.y - ENEMY_SIZEY &&
	//						pEnemy->nType != 5)
	//					{ // �ʏ�G�̖����͈�
	//						// �G�̓����蔻��ƃ_���[�W
	//						HitEnemy(nCntEnemy, ATK_BULLETB);

	//						// �e�̔j��
	//						pBullet->bUse = false;
	//					}
	//				}

	//				if (pBullet->pos.y - BULLETB_SIZEY <= pEnemy->pos.y + BIGENEMY_SIZEY &&
	//					pBullet->pos.x + 10 >= pEnemy->pos.x - BIGENEMY_SIZEX &&
	//					pBullet->pos.x - 10 <= pEnemy->pos.x + BIGENEMY_SIZEX &&
	//					pBullet->pos.y + BULLETB_SIZEY >= pEnemy->pos.y - BIGENEMY_SIZEY &&
	//					pEnemy->nType == 5 && pEnemy->pos.y == 120)
	//				{ // �{�X�G�̖����͈�
	//					if (pBullet->type == BULLETTYPE_PLAYER)
	//					{
	//						// �G�̓����蔻��ƃ_���[�W
	//						HitEnemy(nCntEnemy, ATK_BULLETA);

	//						// �e�̔j��
	//						pBullet->bUse = false;
	//					}
	//				}
	//			}
	//		}
	//		else if (pBullet->nType == 2)
	//		{ // �eC(�~�T�C��)�̏ꍇ
	//		  // �p�[�e�B�N���̐ݒ�
	//			SetEffect(pBullet->pos, 0.009f, D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f), 2.0f, 0.1f);

	//			// �ʒu�̍X�V
	//			pBullet->pos += pBullet->move;

	//			// �G�Ƃ̓����蔻��
	//			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	//			{
	//				if (pEnemy->bUse == true)
	//				{ // �G���L���̏ꍇ
	//					if (pBullet->pos.y - BULLETC_SIZEY <= pEnemy->pos.y + ENEMY_SIZEY &&
	//						pBullet->pos.x + BULLETC_SIZEX >= pEnemy->pos.x - ENEMY_SIZEX &&
	//						pBullet->pos.x - BULLETC_SIZEX <= pEnemy->pos.x + ENEMY_SIZEX &&
	//						pBullet->pos.y + BULLETC_SIZEY >= pEnemy->pos.y - ENEMY_SIZEY &&
	//						pEnemy->nType != 5)
	//					{ // �ʏ�G�̖����͈�
	//						// �G�̓����蔻��ƃ_���[�W
	//						HitEnemy(nCntEnemy, ATK_BULLETC);

	//						// �e�̔j��
	//						pBullet->bUse = false;
	//					}
	//				}

	//				if (pBullet->pos.y - BULLETC_SIZEY <= pEnemy->pos.y + BIGENEMY_SIZEY &&
	//					pBullet->pos.x + BULLETC_SIZEX >= pEnemy->pos.x - BIGENEMY_SIZEX &&
	//					pBullet->pos.x - BULLETC_SIZEX <= pEnemy->pos.x + BIGENEMY_SIZEX &&
	//					pBullet->pos.y + BULLETC_SIZEY >= pEnemy->pos.y - BIGENEMY_SIZEY &&
	//					pEnemy->nType == 5 && pEnemy->pos.y == 120)
	//				{ // �{�X�G�̖����͈�
	//					if (pBullet->type == BULLETTYPE_PLAYER)
	//					{
	//						// �G�̓����蔻��ƃ_���[�W
	//						HitEnemy(nCntEnemy, ATK_BULLETA);

	//						// �e�̔j��
	//						pBullet->bUse = false;
	//					}
	//				}
	//			}
	//		}
	//		else if (pBullet->nType == 3)
	//		{ // �eD(�t�E�F�[�u)�̏ꍇ
	//		  // �p�[�e�B�N���̐ݒ�
	//			SetEffect(pBullet->pos, 0.0f, D3DXCOLOR(0.01f, 0.01f, 0.9f, 1.0f), 15.0f, 0.09f);

	//			// �ʒu�̍X�V
	//			pBullet->pos += pBullet->move;

	//			// �G�Ƃ̓����蔻��
	//			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	//			{
	//				if (pEnemy->bUse == true)
	//				{ // �G���L���̏ꍇ
	//					if (pBullet->pos.y - BULLETD_SIZEY <= pEnemy->pos.y + ENEMY_SIZEY &&
	//						pBullet->pos.x + BULLETD_SIZEX >= pEnemy->pos.x - ENEMY_SIZEX &&
	//						pBullet->pos.x - BULLETD_SIZEX <= pEnemy->pos.x + ENEMY_SIZEX &&
	//						pBullet->pos.y + BULLETD_SIZEY >= pEnemy->pos.y - ENEMY_SIZEY &&
	//						pEnemy->nType != 5)
	//					{ // �ʏ�G�̖����͈�
	//						// �G�̓����蔻��ƃ_���[�W
	//						HitEnemy(nCntEnemy, ATK_BULLETD);

	//						// �e�̔j��
	//						pBullet->bUse = false;
	//					}

	//					if (pBullet->pos.y - BULLETD_SIZEY <= pEnemy->pos.y + BIGENEMY_SIZEY &&
	//						pBullet->pos.x + BULLETD_SIZEX >= pEnemy->pos.x - BIGENEMY_SIZEX &&
	//						pBullet->pos.x - BULLETD_SIZEX <= pEnemy->pos.x + BIGENEMY_SIZEX &&
	//						pBullet->pos.y + BULLETD_SIZEY >= pEnemy->pos.y - BIGENEMY_SIZEY &&
	//						pEnemy->nType == 5 && pEnemy->pos.y == 120)
	//					{ // �{�X�G�̖����͈�
	//						if (pBullet->type == BULLETTYPE_PLAYER)
	//						{
	//							// �G�̓����蔻��ƃ_���[�W
	//							HitEnemy(nCntEnemy, ATK_BULLETA);

	//							// �e�̔j��
	//							pBullet->bUse = false;
	//						}
	//					}
	//				}
	//			}
	//		}
	//		else if (pBullet->nType == 4)
	//		{ // �G�̒e�̏ꍇ
	//		  // �ʒu�̍X�V
	//			pBullet->pos += pBullet->move;

	//			// ���@�Ƃ̓����蔻��
	//			if (Player->state == PLAYERSTATE_NORMAL)
	//			{ // �G���L���̏ꍇ
	//				if (pBullet->pos.y - 10 <= Player->pos.y + 20 &&
	//					pBullet->pos.x + 10 >= Player->pos.x - 20 &&
	//					pBullet->pos.x - 10 <= Player->pos.x + 20 &&
	//					pBullet->pos.y + 10 >= Player->pos.y - 20)
	//				{
	//					// �G�̓����蔻��ƃ_���[�W
	//					HitPlayer(1);

	//					// �e�̔j��
	//					pBullet->bUse = false;
	//				}
	//			}
	//		}

	//		// �G���̍X�V
	//		pEnemy = GetEnemy();

	//		// ���_���W�̍X�V
	//		SetVertexBullet(nCntBullet);

	//		// �����`�F�b�N
	//		pBullet->nLife -= 1;
	//		if (pBullet->nLife <= 0)
	//		{
	//			SetExplosion(pBullet->pos);
	//			pBullet->bUse = false;
	//		}

	//		// ��ʊO�`�F�b�N
	//		if (pBullet->pos.y <= 0.0f || pBullet->pos.y >= SCREEN_HEIGHT || pBullet->pos.x <= 0.0f || pBullet->pos.x >= SCREEN_WIDTH)
	//		{
	//			pBullet->bUse = false;
	//		}
	//	}
	//}
}

//==============================================================================
// �e�̒��_���W�̐ݒ�
//==============================================================================
void SetVertexBullet(int nIdx)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0,0,(void**)&pVtx,0);

	// ���_�|�C���^��4���i�߂�
	pVtx += 4 * nIdx;

	// �o���b�g�|�C���^��i�߂�
	pBullet += nIdx;

	pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - BULLETA_SIZEX, pBullet->pos.y - BULLETA_SIZEY, pBullet->pos.z);
	pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x - BULLETA_SIZEX, pBullet->pos.y + BULLETA_SIZEY, pBullet->pos.z);
	pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x + BULLETA_SIZEX, pBullet->pos.y - BULLETA_SIZEY, pBullet->pos.z);
	pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + BULLETA_SIZEX, pBullet->pos.y + BULLETA_SIZEY, pBullet->pos.z);
	
	//g_aTest[0] = pVtx[0].pos;

	//// �e�̎�ނɉ����đ傫����ω�
	//if (pBullet->nType == 0)
	//{ // �eA(�ʏ�e)�̏ꍇ
	//	// ���_���W�̐ݒ�
	//	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETA_SIZEX, g_aBullet[nIdx].pos.y + BULLETA_SIZEY, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETA_SIZEX, g_aBullet[nIdx].pos.y - BULLETA_SIZEY, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETA_SIZEX, g_aBullet[nIdx].pos.y + BULLETA_SIZEY, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETA_SIZEX, g_aBullet[nIdx].pos.y - BULLETA_SIZEY, 0.0f);
	//}
	//else if (pBullet->nType == 1)
	//{ // �eB(�E�F�[�u)�̏ꍇ
	//	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETB_SIZEX, g_aBullet[nIdx].pos.y + BULLETB_SIZEY, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETB_SIZEX, g_aBullet[nIdx].pos.y - BULLETB_SIZEY, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETB_SIZEX, g_aBullet[nIdx].pos.y + BULLETB_SIZEY, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETB_SIZEX, g_aBullet[nIdx].pos.y - BULLETB_SIZEY, 0.0f);
	//}
	//else if (pBullet->nType == 2)
	//{ // �eC(�~�T�C��)�̏ꍇ
	//	// �~�T�C���̊e���_���W
	//	if (g_aBullet[nIdx].move.x > 0)
	//	{
	//		g_rotMissile.z = -D3DX_PI / 6;
	//	}
	//	else if (g_aBullet[nIdx].move.x < 0)
	//	{
	//		g_rotMissile.z = D3DX_PI / 6;
	//	}

	//	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + sinf(-g_fAngleMissile + g_rotMissile.z) * g_fLengthMissile, g_aBullet[nIdx].pos.y + cosf(-g_fAngleMissile + g_rotMissile.z) * g_fLengthMissile, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + sinf(g_fAngleMissile - D3DX_PI + g_rotMissile.z) * g_fLengthMissile, g_aBullet[nIdx].pos.y + cosf(g_fAngleMissile - D3DX_PI + g_rotMissile.z) * g_fLengthMissile, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + sinf(g_fAngleMissile + g_rotMissile.z) * g_fLengthMissile, g_aBullet[nIdx].pos.y + cosf(g_fAngleMissile + g_rotMissile.z) * g_fLengthMissile, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + sinf(-g_fAngleMissile + D3DX_PI + g_rotMissile.z) * g_fLengthMissile, g_aBullet[nIdx].pos.y + cosf(-g_fAngleMissile + D3DX_PI + g_rotMissile.z) * g_fLengthMissile, 0.0f);		
	//}
	//else if (pBullet->nType == 3)
	//{ // �eD(���o�[�X�E�F�[�u)�̏ꍇ
	//	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETD_SIZEX, g_aBullet[nIdx].pos.y + BULLETD_SIZEY, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLETD_SIZEX, g_aBullet[nIdx].pos.y - BULLETD_SIZEY, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETD_SIZEX, g_aBullet[nIdx].pos.y + BULLETD_SIZEY, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLETD_SIZEX, g_aBullet[nIdx].pos.y - BULLETD_SIZEY, 0.0f);
	//}
	//else if (pBullet->nType == 4)
	//{ // �G�̒e�̏ꍇ
	//	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - ENEMY_BULLETX, g_aBullet[nIdx].pos.y + ENEMY_BULLETY, 0.0f);
	//	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - ENEMY_BULLETX, g_aBullet[nIdx].pos.y - ENEMY_BULLETY, 0.0f);
	//	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + ENEMY_BULLETX, g_aBullet[nIdx].pos.y + ENEMY_BULLETY, 0.0f);
	//	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + ENEMY_BULLETX, g_aBullet[nIdx].pos.y - ENEMY_BULLETY, 0.0f);
	//}
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}