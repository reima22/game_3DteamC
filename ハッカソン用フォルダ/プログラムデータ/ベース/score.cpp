//==============================================================================
//
// �X�R�A�̕`��kscore.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "score.h"
#include "game.h"
#include "math.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define POS_SCOREX	(1100.0f)	// �X�R�A�̏�ꌅ�̒��SX���W
#define POS_SCOREY	(40.0f)	// �X�R�A�̏�ꌅ�̒��SY���W

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;			// �X�R�A�e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// �X�R�A�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3 g_aScore[MAX_SCORE];					// �X�R�A�̈ʒu���
int g_nScore;										// �X�R�A�̐��l

//==============================================================================
// �X�R�A�̏���������
//==============================================================================
HRESULT InitScore(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	int nStage = GetStage();

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/number000.png",
		&g_pTextureScore);

	// �X�R�A�̈ʒu���W�̏�����
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		g_aScore[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// �X�R�A�l�̏�����
	if (nStage == START_NUM)
	{
		g_nScore = 0;
	}

	// ���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		// �X�R�A�̒��S���W�̐ݒ�
		g_aScore[nCnt] = D3DXVECTOR3(POS_SCOREX + ((float)nCnt * 20.0f), POS_SCOREY, 0.0f);

		//�X�R�A�̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3((float)g_aScore[nCnt].x - 10.0f, (float)g_aScore[nCnt].y + 20.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((float)g_aScore[nCnt].x - 10.0f, (float)g_aScore[nCnt].y - 20.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((float)g_aScore[nCnt].x + 10.0f, (float)g_aScore[nCnt].y + 20.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((float)g_aScore[nCnt].x + 10.0f, (float)g_aScore[nCnt].y - 20.0f, 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		pVtx += 4;	// ���_�|�C���^��4���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//==============================================================================
// �X�R�A�̏I������
//==============================================================================
void UninitScore(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//==============================================================================
// �X�R�A�̍X�V����
//==============================================================================
void UpdateScore(void)
{
	// ���[�J���ϐ��錾
	int aNumber[MAX_SCORE];
	int nData = (int)pow(10, (MAX_SCORE - 1));

	// �e���̌v�Z�ƃe�N�X�`���̐؂�ւ�
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		aNumber[nCnt] = (g_nScore / nData) % 10;
		nData /= 10;
		SetVertexScore(nCnt, aNumber[nCnt]);
	}
}

//==============================================================================
// �X�R�A�̕`�揈��
//==============================================================================
void DrawScore(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffScore,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (int nCnt = 0; nCnt < MAX_SCORE; nCnt++)
	{
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
			nCnt * 4,				// �`����J�n���钸�_�C���f�b�N�X
			2);						// �`�悷��v���~�e�B�u��
	}
}

//==============================================================================
// �X�R�A�̉��Z����
//==============================================================================
void AddScore(int nValue)
{
	g_nScore += nValue;	// �X�R�A�����Z����
}

//==============================================================================
// �X�R�A�̒��_���W�擾����
//==============================================================================
void SetVertexScore(int nIdx,int nNumber)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�|�C���^��4���i�߂�
	pVtx += 4 * nIdx;

	// �e�N�X�`���̒��_���W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + ((float)nNumber / 10), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + ((float)nNumber / 10), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//==============================================================================
// �X�R�A�̎擾
//==============================================================================
int GetScore(void)
{
	return g_nScore;	// �X�R�A�̒l���擾����
}