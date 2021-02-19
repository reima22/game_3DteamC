//==============================================================================
//
// ���͏����i�Q�[���p�b�h�j�kgamepad.cpp�l
// AUTHOR : TAKAHASHI
//
//==============================================================================
#include "input.h"
#include "gamepad.h"

//�Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X�񋓂̌��ʂ��󂯎��\����
typedef struct
{
	LPDIRECTINPUTDEVICE8* GamePadDevice;
	int FindCount;
}DeviceEnumParameter;

//==============================================================================
// �O���[�o���ϐ�
//==============================================================================
static LPDIRECTINPUT8 g_InputInterface;
static LPDIRECTINPUTDEVICE8 device;						// ���̓f�o�C�X�ւ̃|�C���^
static ButtonState g_ButtonStates[KEYINFO::KEYINFO_MAX];

//==============================================================================
// �p�b�h���͂̏���������
//==============================================================================
HRESULT InitGamepad(HINSTANCE hInstance, HWND hWnd)
{
	// IDirectInput8�C���^�[�t�F�[�X�̍쐬
	if (FAILED(DirectInput8Create(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&g_InputInterface,
		NULL)))
	{
		return E_FAIL;
	}

	DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &device;

	if (FAILED(g_InputInterface->EnumDevices(
		DI8DEVTYPE_GAMEPAD,
		DeviceFindCallBack,
		&parameter,
		DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	if (FAILED(g_InputInterface->EnumDevices(
		DI8DEVTYPE_JOYSTICK,
		DeviceFindCallBack,
		&parameter,
		DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�̐���
	if (FAILED(g_InputInterface->CreateDevice(
		GUID_Joystick,
		&device,
		NULL)))
	{
		return E_FAIL;
	}

	// ���͏��̏�����
	for (int nCnt = 0; nCnt < KEYINFO::KEYINFO_MAX; nCnt++)
	{
		g_ButtonStates[nCnt] = ButtonState::ButtonStateNone;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(device->SetDataFormat(
		&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;	// ��Βl���[�h�̎w��(DPROPAXISMODE_REL�ɂ����瑊�Βl)

										// �����[�h��ύX
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.diph.dwObj = DIJOFS_X;
	diprg.lMin = -1000;
	diprg.lMax = 1000;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// �������[�h�̐ݒ�
	if (FAILED(device->SetCooperativeLevel(
		hWnd,
		(DISCL_FOREGROUND | DISCL_EXCLUSIVE))))
	{
		return E_FAIL;
	}

	return S_OK;
}

//==============================================================================
// �p�b�h���͂̏I������
//==============================================================================
void UninitGamepad(void)
{
	if (device != NULL)
	{
		// �A�N�Z�X���̔j��
		device->Unacquire();

		device->Release();
		device = NULL;
	}

	if (g_InputInterface != NULL)
	{
		g_InputInterface->Release();
		g_InputInterface = NULL;
	}
}

//==============================================================================
// �p�b�h���͂̍X�V����
//==============================================================================
void UpdateGamepad(void)
{
	if (device == nullptr)
	{
		return;
	}

	DIJOYSTATE pad_data;

	HRESULT hr = device->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		if (FAILED(device->Acquire()))
		{
			for (int nCnt = 0; nCnt < KEYINFO::KEYINFO_MAX; nCnt++)
			{
				g_ButtonStates[nCnt] = ButtonState::ButtonStateNone;
			}
			device->Poll();
		}
		return;
	}

	bool is_push[KEYINFO::KEYINFO_MAX];

	int unresponsive_range = 200;

	if (pad_data.lX < -unresponsive_range)
	{// ���ɌX����
		is_push[KEYINFO::KEYINFO_LEFT] = true;
	}
	else if (pad_data.lX > unresponsive_range)
	{// �E�ɌX����
		is_push[KEYINFO::KEYINFO_RIGHT] = true;
	}

	if (pad_data.lY < -unresponsive_range)
	{// ��ɌX����
		is_push[KEYINFO::KEYINFO_UP] = true;
	}
	else if (pad_data.lY > unresponsive_range)
	{// ���ɌX����
		is_push[KEYINFO::KEYINFO_DOWN] = true;
	}

	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		// 8�����ł̐���
		switch (pad_data.rgdwPOV[0])
		{
			// ��
		case 0:
			is_push[KEYINFO::KEYINFO_UP] = true;
			break;
			// �E��
		case 4500:
			is_push[KEYINFO::KEYINFO_UP] = true;
			is_push[KEYINFO::KEYINFO_RIGHT] = true;
			break;
			// �E
		case 9000:
			is_push[KEYINFO::KEYINFO_RIGHT] = true;
			break;
			// �E��
		case 13500:
			is_push[KEYINFO::KEYINFO_DOWN] = true;
			is_push[KEYINFO::KEYINFO_RIGHT] = true;
			break;
			// ��
		case 18000:
			is_push[KEYINFO::KEYINFO_DOWN] = true;
			break;
			// ����
		case 22500:
			is_push[KEYINFO::KEYINFO_DOWN] = true;
			is_push[KEYINFO::KEYINFO_LEFT] = true;
			break;
			// ��
		case 27000:
			is_push[KEYINFO::KEYINFO_LEFT] = true;
			break;
			// ����
		case 31500:
			is_push[KEYINFO::KEYINFO_UP] = true;
			is_push[KEYINFO::KEYINFO_LEFT] = true;
			break;
		}
	}

	for (int nCnt = 0; nCnt < 32; nCnt++)
	{
		if (!(pad_data.rgbButtons[nCnt] & 0x80))
		{
			continue;
		}

		switch (nCnt)
		{
		case 2:
			is_push[KEYINFO::KEYINFO_A] = true;
			break;

		case 3:
			is_push[KEYINFO::KEYINFO_B] = true;
			break;
		
		case 4:
			is_push[KEYINFO::KEYINFO_L1] = true;
			break;

		case 5:
			is_push[KEYINFO::KEYINFO_R1] = true;
			break;

		case 11:
			is_push[KEYINFO::KEYINFO_PAUSE] = true;
			break;
		}
	}

	// ���͏�񂩂�{�^���̏�Ԃ��X�V����
	for (int nCnt = 0; nCnt < KEYINFO::KEYINFO_MAX; nCnt++)
	{
		if (is_push[nCnt] == true)
		{
			if (g_ButtonStates[nCnt] == ButtonState::ButtonStateNone)
			{
				g_ButtonStates[nCnt] = ButtonState::ButtonStateDown;
			}
			else
			{
				g_ButtonStates[nCnt] = ButtonState::ButtonStatePush;
			}
		}
		else
		{
			if (g_ButtonStates[nCnt] == ButtonState::ButtonStatePush)
			{
				g_ButtonStates[nCnt] = ButtonState::ButtonStateUp;
			}
			else
			{
				g_ButtonStates[nCnt] = ButtonState::ButtonStateNone;
			}
		}
	}
}

// �f�o�C�X�񋓃R�[���o�b�N�֐�
BOOL CALLBACK DeviceFindCallBack(
	LPCDIDEVICEINSTANCE ipddi,
	LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	// ���ɔ������Ă���Ȃ�I��
	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	// ���������J�E���g
	parameter->FindCount++;

	return DIENUM_CONTINUE;
}

bool IsButtonPush(KEYINFO button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStatePush)
	{
		return true;
	}

	return false;
}

bool IsButtonUp(KEYINFO button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateUp)
	{
		return true;
	}

	return false;
}

bool IsButtonDown(KEYINFO button)
{
	if (g_ButtonStates[button] == ButtonState::ButtonStateDown)
	{
		return true;
	}

	return false;
}