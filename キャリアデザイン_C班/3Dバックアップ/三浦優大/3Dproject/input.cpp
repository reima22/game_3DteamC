#include "input.h"

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyBoard = NULL;
BYTE g_aKeyState[256];
BYTE g_aKeyStateTrigger[256];

//���̓f�o�C�X�i�L�[�{�[�h�j�|�C���^
//�L�[�{�[�h�ւ̏��
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DIRECTIPUT�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyBoard,NULL)))
	{
		return E_FAIL;
	}
	
	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_pDevKeyBoard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	
	//�������[�h�̐ݒ�
	if (FAILED(g_pDevKeyBoard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�A�N�Z�X���̎擾
	g_pDevKeyBoard->Acquire();
	return S_OK;
}
void UninitKeyboard(void)
{
	if (g_pDevKeyBoard != NULL)
	{
		//�A�N�Z�X���̔j��
		g_pDevKeyBoard->Unacquire();
		g_pDevKeyBoard->Release();
		g_pDevKeyBoard = NULL;
	}
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
void UpdateKeyboard(void)
{
	BYTE aKeystate[256];
	//�f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyBoard->GetDeviceState(sizeof(aKeystate), &aKeystate[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			g_aKeyStateTrigger[nKey] = (g_aKeyState[nKey] & aKeystate[nKey])^ aKeystate[nKey];
			g_aKeyState[nKey] = aKeystate[nKey];
		}
	}
	//�A�N�Z�X���̎擾
	g_pDevKeyBoard->Acquire();
}
bool GetKeyboardPress(int nKey)
{
	//�L�[�{�[�h���̎擾
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
bool GetKeyboardTrigger(int nKey)
{
	//�L�[�{�[�h���̎擾
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}



