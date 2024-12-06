#include "MouseInput.h"
#include "defines.h"

CMouseInput::CMouseInput(HWND hWnd)
{
	//NOTA : Inicialización del device de ratón utilizando DirectInput8 de DirectX
	HRESULT l_HR;
	DWORD l_CoopFlags = 0;

	if (FAILED(l_HR = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_DI, NULL)))
		return;
	if (FAILED(l_HR = m_DI->CreateDevice(GUID_SysMouse, &m_Mouse, NULL)))
		return;
	if (FAILED(l_HR = m_Mouse->SetDataFormat(&c_dfDIMouse2)))
		return;
	if (FAILED(l_HR = m_Mouse->SetCooperativeLevel(hWnd, l_CoopFlags)))
		return;

	if (m_Mouse != NULL)
		m_Mouse->Acquire();
	else
		MessageBox(hWnd, L"Problem with de mouse input!", L"Mouse", MB_ICONERROR | MB_OK);
}

CMouseInput::~CMouseInput()
{
	if (m_Mouse)
	{
		m_Mouse->Unacquire();
	}
	CHECKED_RELEASE(m_Mouse);
	CHECKED_RELEASE(m_DI);
}

bool CMouseInput::Update()
{
	DIMOUSESTATE2 l_DIMouseState;

	if (m_Mouse == NULL)
		return false;

	ZeroMemory(&l_DIMouseState, sizeof(l_DIMouseState));

	//NOTA : El siguiente fragmento de código recoge el estado del ratón actual utilizando la función de DirectX GetDeviceState, a continuación comprueba si el ratón se ha desconectado; en caso de estar desconectado espera a que se vuelva a reconectar
	HRESULT l_HR = m_Mouse->GetDeviceState(sizeof(DIMOUSESTATE2), &l_DIMouseState);
	if (FAILED(l_HR))
	{
		l_HR = m_Mouse->Acquire();
		while (l_HR == DIERR_INPUTLOST)
			l_HR = m_Mouse->Acquire();
		return true;
	}

	m_MovementX = l_DIMouseState.lX;
	m_MovementY = l_DIMouseState.lY;
	m_MovementZ = l_DIMouseState.lZ;

	m_PreviousButtonLeft = m_ButtonLeft;
	m_PreviousButtonMiddle = m_ButtonMiddle;
	m_PreviousButtonRight = m_ButtonRight;

	//NOTA : Asigna en la variable miembro m_ButtonRight si el botón derecho del ratón con Id 1 está pulsado

	m_ButtonRight = (l_DIMouseState.rgbButtons[1] & 0x80) != 0;
	m_ButtonLeft = (l_DIMouseState.rgbButtons[0] & 0x80) != 0;
	m_ButtonMiddle = (l_DIMouseState.rgbButtons[2] & 0x80) != 0;

	return true;
}

int CMouseInput::GetMovementX() const
{
	return m_MovementX;
}

int CMouseInput::GetMovementY() const
{
	return m_MovementY;
}

int CMouseInput::GetMovementZ() const
{
	return m_MovementZ;
}

bool CMouseInput::IsRightButtonPressed() const
{
	return m_ButtonRight;
}

bool CMouseInput::IsLeftButtonPressed() const
{
	return m_ButtonLeft;
}

bool CMouseInput::IsMiddleButtonPressed() const
{
	return m_ButtonMiddle;
}

bool CMouseInput::LeftButtonBecomesPressed() const
{
	return m_ButtonLeft && !m_PreviousButtonLeft;
}

bool CMouseInput::MiddleButtonBecomesPressed() const
{
	return m_ButtonMiddle && !m_PreviousButtonMiddle;
}

bool CMouseInput::RightButtonBecomesPressed() const
{
	return m_ButtonRight && !m_PreviousButtonRight;
}

bool CMouseInput::LeftButtonBecomesReleased() const
{
	return !m_ButtonLeft && m_PreviousButtonLeft;
}

bool CMouseInput::MiddleButtonBecomesReleased() const
{
	return !m_ButtonMiddle && m_PreviousButtonMiddle;
}

bool CMouseInput::RightButtonBecomesReleased() const
{
	return !m_ButtonRight && m_PreviousButtonRight;
}
