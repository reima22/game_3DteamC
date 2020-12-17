//==============================================================================
//
// ���͏����i�L�[�{�[�h�j�kinput.cpp�l
// AUTHOR : MARE HORIAI
//
//==============================================================================
#include "input.h"

//==============================================================================
// �}�N����`
//==============================================================================
#define KEY_STATE	(256)	// ���͏��

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
LPDIRECTINPUT8 g_pInput = NULL;					// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;		// ���̓f�o�C�X�ւ̃|�C���^
BYTE g_aKeyState[KEY_STATE];					// �L�[�{�[�h�̓��͏��
BYTE g_aKeyStateTrigger[KEY_STATE];				// �L�[�g���K�[���
BYTE g_aKeyStateRelease[KEY_STATE];				// �L�[�����[�X���
BYTE g_aKeyStateRepeat[KEY_STATE];				// �L�[���s�[�g���
int g_aCountRepeat[KEY_STATE];					// �L�[���s�[�g�J�E���^�[
int g_aKeyInfo[] =
{
	DIK_RETURN,
	DIK_X,
	DIK_W,
	DIK_S,
	DIK_A,
	DIK_D,
	DIK_T,
	DIK_B,
	DIK_Z,
	DIK_C,
	DIK_Y,
	DIK_N,
	DIK_I,
	DIK_K,
	DIK_LSHIFT,
	DIK_RSHIFT,
	DIK_SPACE,
	DIK_U,
	DIK_M,
	DIK_Q,
	DIK_E
};

//==============================================================================
// ���͂̏���������
//==============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_pInput,
		NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(
		GUID_SysKeyboard,
		&g_pDevKeyboard,
		NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(
		&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h�̐ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(
		hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �A�N�Z�X���̎擾
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//==============================================================================
// ���͂̏I������
//==============================================================================
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{
		// �A�N�Z�X���̔j��
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//==============================================================================
// ���͂̍X�V����
//==============================================================================
void UpdateKeyboard(void)
{
	// ���[�J���ϐ��錾
	BYTE aKeyState[KEY_STATE];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(
		sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (int nKey = 0; nKey < KEY_STATE; nKey++)
		{
			g_aKeyStateTrigger[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) & aKeyState[nKey];
			g_aKeyStateRelease[nKey] = (g_aKeyState[nKey] ^ aKeyState[nKey]) | aKeyState[nKey];
			g_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		// �A�N�Z�X���̎擾
		g_pDevKeyboard->Acquire();
	}
}

//==============================================================================
// �L�[�{�[�h���̎擾
//==============================================================================
bool GetKeyboardPress(int nKey)
{
	// �L�[�{�[�h���̎擾
	return (g_aKeyState[g_aKeyInfo[nKey]] & 0x80) ? true : false;
}

//==============================================================================
// �L�[�{�[�h���g���K�[�̎擾
//==============================================================================
bool GetKeyboardTrigger(int nKey)
{
	// �L�[�{�[�h���̎擾
	return (g_aKeyStateTrigger[g_aKeyInfo[nKey]] & 0x80) ? true : false;
}

//==============================================================================
// �L�[�{�[�h��񃊃��[�X�̎擾
//==============================================================================
bool GetKeyboardRelease(int nKey)
{
	// �L�[�{�[�h���̎擾
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}