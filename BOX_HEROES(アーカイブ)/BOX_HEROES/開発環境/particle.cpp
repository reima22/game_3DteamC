//==============================================================================
//
// �p�[�e�B�N���̕`��kparticle.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "particle.h"
//#include "enemy.h"
#include "player.h"
#include "time.h"
#include "stdlib.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define MAX_PARTICLE	(4096)	// �G�t�F�N�g�|���S�����̍ő�l

//==============================================================================
// �p�[�e�B�N���̍\����
//==============================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ�
	D3DXCOLOR color;	// �F�E�����x
	float fRadius;		// ���a
	float fAlphaDown;	// �����x�ቺ
	int nLife;			// ����
	bool bUse;			// �g�p���Ă��邩�ǂ���
	D3DXMATRIX mtxWorld;
	int nPattern;
} PARTICLE;

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;		// �o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;			// �p�[�e�B�N���e�N�X�`���[�ւ̃|�C���^
PARTICLE g_aParticle[MAX_PARTICLE];						// �p�[�e�B�N���̍\����

//==============================================================================
// �p�[�e�B�N���̏���������
//==============================================================================
HRESULT InitParticle(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;

	// �����������猻���������O
	srand((unsigned int)time(0));

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/effect000.jpg",
		&g_pTextureParticle);

	// �\���̂̏�����
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].fAlphaDown = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;
		g_aParticle[nCntParticle].nPattern = 0;
	}

	// ���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		// �ʒu�ƐF�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, 0.0f);

		// �@���x�N�g���̐ݒ�
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
	g_pVtxBuffParticle->Unlock();



	return S_OK;
}

//==============================================================================
// �p�[�e�B�N���̏I������
//==============================================================================
void UninitParticle(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}
}

//==============================================================================
// �p�[�e�B�N���̍X�V����
//==============================================================================
void UpdateParticle(void)
{
	// ���[�J���ϐ��錾
	PARTICLE *pParticle;
	VERTEX_3D *pVtx;

	// �p�[�e�B�N���̎擾
	pParticle = &g_aParticle[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pVtx += 4, pParticle++)
	{
		if (pParticle->bUse == true)
		{ // �G�t�F�N�g���g�p����Ă����ꍇ
			if(pParticle->nPattern == 0)
			{
				// �g�U�̗}��
				pParticle->move.x *= 0.9f;
				pParticle->move.y *= 0.9f;
				pParticle->move.z *= 0.9f;
			}

			// �ړ��X�V
			pParticle->pos += pParticle->move;

			// �����x�̌���
			pParticle->color.a -= pParticle->fAlphaDown;

			// �ʒu�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-pParticle->fRadius, -pParticle->fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(-pParticle->fRadius, pParticle->fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pParticle->fRadius, -pParticle->fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pParticle->fRadius, pParticle->fRadius, 0.0f);

			// �e���_�J���[�̐ݒ�
			pVtx[0].col = pParticle->color;
			pVtx[1].col = pParticle->color;
			pVtx[2].col = pParticle->color;
			pVtx[3].col = pParticle->color;

			// �p�[�e�B�N���̖�����
			if (pParticle->color.a <= 0)
			{
				pParticle->color.a = 0.0f;
				pParticle->bUse = false;
			}

			// �����̊Ǘ�
			pParticle->nLife--;
			if (pParticle->nLife <= 0)
			{
				pParticle->bUse = false;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}

//==============================================================================
// �p�[�e�B�N���̕`�揈��
//==============================================================================
void DrawParticle(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	PARTICLE *pParticle = &g_aParticle[0];
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���Z�����ɂ��A���t�@�u�����f�B���O
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�e�X�g�̍X�V
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���C�g���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++,pParticle++)
	{
		// �|���S���̐���
		if (pParticle->bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pParticle->mtxWorld);

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pParticle->mtxWorld, NULL, &mtxView);
			pParticle->mtxWorld._41 = 0.0f;
			pParticle->mtxWorld._42 = 0.0f;
			pParticle->mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pParticle->pos.x, pParticle->pos.y, pParticle->pos.z);
			D3DXMatrixMultiply(&pParticle->mtxWorld, &pParticle->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pParticle->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle);

			// �|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}
	
	// ���C�g���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���ɖ߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �ʏ�̃A���t�@�u�����f�B���O
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//==============================================================================
// �G�t�F�N�g�̐ݒ�
//==============================================================================
void SetEffect(D3DXVECTOR3 pos, float fMove, D3DXCOLOR color, float fRadius, float fAlphaDown,int nEffect)
{
	// ���[�J���ϐ��錾
	PARTICLE *pParticle;

	// �p�[�e�B�N���̎擾
	pParticle = &g_aParticle[0];

	for (int nCntAppear = 0; nCntAppear < nEffect; nCntAppear++)
	{
		for (int nCntParticle = 0; nCntParticle < nEffect; nCntParticle++, pParticle++)
		{
			if (pParticle->bUse == false/* && pParticle->nPattern == 0*/)
			{ // �g�p����Ă��Ȃ��ꍇ
				// �ʒu��ݒ�
				pParticle->pos = pos;

				// �p�[�e�B�N���̊p�x�Ɠ���
				float fAngle;
				fAngle = (float)((rand() % 628) - 314) / 100.0f;
				pParticle->move.x = (sinf(fAngle) * (float)(rand() % 500 + 1) * fMove);
				pParticle->move.y = (cosf(fAngle) * (float)(rand() % 500 + 1) * fMove);
				pParticle->move.z = (cosf(fAngle) * (float)(rand() % 500 + 1) * fMove);

				// �p�[�e�B�N���̐F�ݒ�
				pParticle->color = color;

				// �p�[�e�B�N��1�̑傫��
 				pParticle->fRadius = fRadius;

				// �p�[�e�B�N���̓����x�����l
				pParticle->fAlphaDown = fAlphaDown;

				// �p�[�e�B�N���̎����ݒ�
				pParticle->nLife = 200;
				
				// �p�[�e�B�N���̗L����
				pParticle->bUse = true;
				break;
			}
		}
	}
}

//==============================================================================
// �����L���O�G�t�F�N�g�̐ݒ�
//==============================================================================
void SetEffect1(D3DXVECTOR3 pos, float fMove, D3DXCOLOR color, float fRadius, float fAlphaDown, int nEffect,int nPattern)
{
	// ���[�J���ϐ��錾
	PARTICLE *pParticle;

	// �p�[�e�B�N���̎擾
	pParticle = &g_aParticle[0];

	for (int nCntAppear = 0; nCntAppear < nEffect; nCntAppear++)
	{
		for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++, pParticle++)
		{
			if (pParticle->bUse == false)
			{ // �g�p����Ă��Ȃ��ꍇ
			  // �ʒu��ݒ�
				pParticle->pos = pos;
				pParticle->nPattern = nPattern;

				// �ړ���
				pParticle->move.z = fMove;

				// �p�[�e�B�N���̐F�ݒ�
				pParticle->color = color;

				// �p�[�e�B�N��1�̑傫��
				pParticle->fRadius = fRadius;

				// �p�[�e�B�N���̓����x�����l
				pParticle->fAlphaDown = fAlphaDown;

				// �p�[�e�B�N���̎����ݒ�
				pParticle->nLife = 200;

				// �p�[�e�B�N���̗L����
				pParticle->bUse = true;
				break;
			}
		}
	}
}