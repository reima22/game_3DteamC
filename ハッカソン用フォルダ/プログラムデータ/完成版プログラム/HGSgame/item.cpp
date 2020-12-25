//==============================================================================
//
// �A�C�e���̕`��kitem.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "item.h"
#include "score.h"

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECT3DTEXTURE9 g_apTextureItem[MAX_TYPE_ITEM] = {};	// �A�C�e���e�N�X�`���[�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;			// �o�b�t�@�ւ̃|�C���^
ITEM g_aItem[MAX_ITEM];									// �A�C�e���̏��

//==============================================================================
// �A�C�e���̏���������
//==============================================================================
HRESULT InitItem(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	LPDIRECT3DDEVICE9 pDevice;
	ITEM *pItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̎擾
	pItem = &g_aItem[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/item000.png",
		&g_apTextureItem[0]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/item001.png",
		&g_apTextureItem[1]);

	D3DXCreateTextureFromFile(
		pDevice,
		"data/TEXTURE/item002.png",
		&g_apTextureItem[2]);

	// �ϐ��̏�����
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		pItem->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pItem->nType = NULL;
		pItem->bUse = false;
	}

	// ���_���̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		// �G�̒��S���W�̐ݒ�
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �G�̒��_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_SIZEX, g_aItem[nCntItem].pos.y + ITEM_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - ITEM_SIZEX, g_aItem[nCntItem].pos.y - ITEM_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_SIZEX, g_aItem[nCntItem].pos.y + ITEM_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + ITEM_SIZEX, g_aItem[nCntItem].pos.y - ITEM_SIZEY, 0.0f);

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
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

//==============================================================================
// �A�C�e���̏I������
//==============================================================================
void UninitItem(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}

	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAX_TYPE_ITEM; nCnt++)
	{
		if (g_apTextureItem[nCnt] != NULL)
		{
			g_apTextureItem[nCnt]->Release();
			g_apTextureItem[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �A�C�e���̍X�V����
//==============================================================================
void UpdateItem(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	ITEM *pItem;

	// �A�C�e���̎擾
	pItem = &g_aItem[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++, pVtx = pVtx + 4)
	{
		if (pItem->bUse == true)
		{ // �A�C�e�����g�p����Ă���(����Ă���)�ꍇ
		  // �ʒu�̍X�V
			pItem->pos.y += 3.0f;

			// ���_���W�̍X�V
			SetVertexItem(nCntItem);

			// ��ʊO�ł̃A�C�e���̏���
			if (pItem->pos.y >= SCREEN_HEIGHT)
			{
				pItem->bUse = false;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//==============================================================================
// �A�C�e���̕`�揈��
//==============================================================================
void DrawItem(void)
{
	// ���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;
	ITEM *pItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̎擾
	pItem = &g_aItem[0];

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffItem,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
 			pDevice->SetTexture(0, g_apTextureItem[pItem->nType]);

			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
				nCntItem * 4,			// �`����J�n���钸�_�C���f�b�N�X
				2);						// �`�悷��v���~�e�B�u��
		}
	}
}

//==============================================================================
// �A�C�e���̐ݒ�
//==============================================================================
void SetItem(D3DXVECTOR3 pos, int nType)
{
	// ���[�J���ϐ��錾
	ITEM *pItem;
	VERTEX_2D *pVtx;

	// �A�C�e���̎擾
	pItem = &g_aItem[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < 56; nCntItem++, pItem++)
	{
		if (pItem->bUse == false)
		{ // �A�C�e�����g�p����Ă��Ȃ��ꍇ
			// �ʒu��ݒ�
			pItem->pos = pos;

			// ���_���W��ݒ�
			SetVertexItem(nCntItem);

			// ��ނ̐ݒ�
			pItem->nType = nType;

			// �A�C�e���̗L����
			pItem->bUse = true;
			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//==============================================================================
// �A�C�e���̒��_���W�擾����
//==============================================================================
void SetVertexItem(int nIdx)
{
	// ���[�J���ϐ��錾
	VERTEX_2D *pVtx;
	ITEM *pItem;

	// �A�C�e���̎擾
	pItem = &g_aItem[0];

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�|�C���^��4���i�߂�
	pVtx += nIdx * 4;

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y + ITEM_SIZEY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y + ITEM_SIZEY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//==============================================================================
// �G�̎擾
//==============================================================================
ITEM *GetItem(void)
{
	return &g_aItem[0];
}