//-----------------------------------------------------------------------------
//
// �`���[�g���A����ʂ̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------
#include "Tutorial.h"
#include "input.h"
#include "fade.h"
//#include "sound.h"

//�}�N����`
#define MAX_TUTORIAL (3)					//�^�C�g���̉摜�̐�
#define TUTORIAL_BG_SIZE_X (860)			//�^�C�g����ʂ̉���
#define TUTORIAL_BG_SIZE_Y (440)			//�^�C�g����ʂ̗���
#define TUTORIAL_SIZE_X (500)				//�`���[�g���A������
#define TUTORIAL_SIZE_Y (75)				//�`���[�g���A������
#define TUTORIAL_ENTER_SIZE_X (100)			//�v���X�G���^�[�̉���
#define TUTORIAL_ENTER_SIZE_Y (50)			//�v���X�G���^�[�̗���
#define TUTORIAL_BG_POS_X (960)				//�w�i�̏ꏊX
#define TUTORIAL_BG_POS_Y (575)				//�w�i�̏ꏊY
#define TUTORIAL_POS_X (960)				//�`���[�g���A���̏ꏊX
#define TUTORIAL_POS_Y (75)					//�`���[�g���A���̏ꏊY
#define PRESSENTER_POS_X (1800)				//�v���X�G���^�[�̏ꏊX
#define PRESSENTER_POS_Y (1000)				//�v���X�G���^�[�̏ꏊY


//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;		//���_���
LPDIRECT3DTEXTURE9 g_pTextureTutorial[MAX_TUTORIAL] = {};	//�e�N�X�`��
TUTORIAL g_aTutorial[MAX_TUTORIAL];
int g_nCounterTutorial = 30;
int g_TutorialFadeCounter;
int g_nTutorialCounter;
bool g_bTutorialEnter;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitTutorial(void)
{

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/", &g_pTextureTutorial[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pressenter.png", &g_pTextureTutorial[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gametutorial.png", &g_pTextureTutorial[2]);


	g_nCounterTutorial = 30;
	g_bTutorialEnter = false;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TUTORIAL, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTutorial, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntTutorial = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++)
	{
		g_aTutorial[nCntTutorial].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCntTutorial].bDisp = true;
	}
	
	g_TutorialFadeCounter = 0;
	
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTutorial = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++, pVtx += 4)
	{

		SetVertexTutorial(nCntTutorial);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTutorial->Unlock();

	}
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitTutorial(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	//�e�N�X�`���̊J��
	for (int nCntTutorial = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++)
	{
		if (g_pTextureTutorial[nCntTutorial] != NULL)
		{
			g_pTextureTutorial[nCntTutorial]->Release();
			g_pTextureTutorial[nCntTutorial] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateTutorial(void)
{
	FADE *pFade;
	pFade = GetFade();

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//pVtx += 4;

	g_nTutorialCounter++;

	if ((g_nTutorialCounter % g_nCounterTutorial) == 0)
	{
		g_aTutorial[1].bDisp = g_aTutorial[1].bDisp ? false : true;	//�v���X�G���^�[�̓_��
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{

		if (g_bTutorialEnter == false)
		{//�_�ł𑁂�
			g_nCounterTutorial -= 25;
			//PlaySound(SOUND_LABEL_SE_DESICION);
			g_bTutorialEnter = true;
		}
	}

	if (g_bTutorialEnter == true)
	{//�t�F�[�h�܂ł̎��ԉ��Z
		if ((g_nTutorialCounter % 2) == 0)
		{
			g_TutorialFadeCounter++;

		}
	}

	//�t�F�[�h
	if (g_TutorialFadeCounter == 30)
	{		
		SetFade(FADE_OUT, MODE_GAME);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorial->Unlock();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawTutorial(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTutorial = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTutorial]);

		if (g_aTutorial[nCntTutorial].bDisp == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTutorial * 4, 2);
		}
	}

}

//-----------------------------------------------------------------------------
// �^�C�g���̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexTutorial(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	if (nIdx == 0)
	{
	//�w�i
		g_aTutorial[nIdx].pos = D3DXVECTOR3(TUTORIAL_BG_POS_X, TUTORIAL_BG_POS_Y ,0.0f);
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x - TUTORIAL_BG_SIZE_X, g_aTutorial[nIdx].pos.y + TUTORIAL_BG_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x - TUTORIAL_BG_SIZE_X, g_aTutorial[nIdx].pos.y - TUTORIAL_BG_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x + TUTORIAL_BG_SIZE_X, g_aTutorial[nIdx].pos.y + TUTORIAL_BG_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x + TUTORIAL_BG_SIZE_X, g_aTutorial[nIdx].pos.y - TUTORIAL_BG_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	if (nIdx == 1)
	{//�v���X�G���^�[
		g_aTutorial[nIdx].pos = D3DXVECTOR3(PRESSENTER_POS_X, PRESSENTER_POS_Y, 0.0f);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x - TUTORIAL_ENTER_SIZE_X, g_aTutorial[nIdx].pos.y + TUTORIAL_ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x - TUTORIAL_ENTER_SIZE_X, g_aTutorial[nIdx].pos.y - TUTORIAL_ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x + TUTORIAL_ENTER_SIZE_X, g_aTutorial[nIdx].pos.y + TUTORIAL_ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x + TUTORIAL_ENTER_SIZE_X, g_aTutorial[nIdx].pos.y - TUTORIAL_ENTER_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255,255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255,255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255,255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255,255, 255, 255);

	}

	if (nIdx == 2)
	{//�`���[�g���A��
		g_aTutorial[nIdx].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x - TUTORIAL_SIZE_X, g_aTutorial[nIdx].pos.y + TUTORIAL_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x - TUTORIAL_SIZE_X, g_aTutorial[nIdx].pos.y - TUTORIAL_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x + TUTORIAL_SIZE_X, g_aTutorial[nIdx].pos.y + TUTORIAL_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nIdx].pos.x + TUTORIAL_SIZE_X, g_aTutorial[nIdx].pos.y - TUTORIAL_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	}
}