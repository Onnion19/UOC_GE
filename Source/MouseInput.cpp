#include "MouseInput.h"
#include "defines.h"

CMouseInput::CMouseInput(HWND hWnd)
//TO DO : Inicializar a cero la variable miembro m_MovementX
//TO DO : Inicializar a cero la variable miembro m_MovementY
//TO DO : Inicializar a cero la variable miembro m_MovementZ
//TO DO : Inicializar a false la variable miembro m_ButtonLeft
//TO DO : Inicializar a false la variable miembro m_ButtonMiddle
//TO DO : Inicializar a false la variable miembro m_ButtonRight
//TO DO : Inicializar a false la variable miembro m_PreviousButtonLeft
//TO DO : Inicializar a false la variable miembro m_PreviousButtonMiddle
//TO DO : Inicializar a false la variable miembro m_PreviousButtonRight
{
	//NOTA : Inicialización del device de ratón utilizando DirectInput8 de DirectX
	HRESULT l_HR;
	DWORD l_CoopFlags=0;
    
	if(FAILED(l_HR=DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&m_DI, NULL)))
        return;
    if(FAILED(l_HR=m_DI->CreateDevice(GUID_SysMouse, &m_Mouse, NULL)))
		return;
    if(FAILED(l_HR=m_Mouse->SetDataFormat(&c_dfDIMouse2)))
		return;
	if(FAILED(l_HR=m_Mouse->SetCooperativeLevel(hWnd, l_CoopFlags)))
		return;
   
	if(m_Mouse!=NULL) 
		m_Mouse->Acquire();
	else
		MessageBox(hWnd, L"Problem with de mouse input!", L"Mouse", MB_ICONERROR | MB_OK );
}

CMouseInput::~CMouseInput()
{
	//TO DO : Si la variable miembro m_Mouse es diferente de NULL llamar al método Unacquire de m_Mouse
	//TO DO : Destruye la variable miembro m_Mouse utilizando la macro CHECKED_RELEASE
	//TO DO : Destruye la variable miembro m_DI utilizando la macro CHECKED_RELEASE
}

bool CMouseInput::Update()
{
	DIMOUSESTATE2 l_DIMouseState;

    if(m_Mouse==NULL)
        return false;
    
	//TO DO : Inicializar a cero la memoria utilizando la función ZeroMemory la variable l_DIMouseState

	//NOTA : El siguiente fragmento de código recoge el estado del ratón actual utilizando la función de DirectX GetDeviceState, a continuación comprueba si el ratón se ha desconectado; en caso de estar desconectado espera a que se vuelva a reconectar
    HRESULT l_HR=m_Mouse->GetDeviceState( sizeof(DIMOUSESTATE2), &l_DIMouseState);
    if(FAILED(l_HR))
    {
        l_HR=m_Mouse->Acquire();
        while(l_HR==DIERR_INPUTLOST)
            l_HR=m_Mouse->Acquire();
        return true;
    }
    
	//TO DO : Establecer en la variable miembro m_MovementX el valor de l_DIMouseState.lX
	//TO DO : Establecer en la variable miembro m_MovementY el valor de l_DIMouseState.lY
	//TO DO : Establecer en la variable miembro m_MovementZ el valor de l_DIMouseState.lZ

	//TO DO : Establecer en la variable miembro m_PreviousButtonLeft el valor de m_ButtonLeft
	//TO DO : Establecer en la variable miembro m_PreviousButtonMiddle el valor de m_ButtonMiddle
	//TO DO : Establecer en la variable miembro m_PreviousButtonRight el valor de m_ButtonRight

	//NOTA : Asigna en la variable miembro m_ButtonRight si el botón derecho del ratón con Id 1 está pulsado

	m_ButtonRight=(l_DIMouseState.rgbButtons[1] & 0x80)!=0;
	//TO DO : Establecer en la variable miembro m_ButtonLeft si el botón izquierdo del ratón con Id 0 está pulsado. Basarse en cómo asigna el valor a la variable miembro m_ButtonRight
	//TO DO : Establecer en la variable miembro m_ButtonMiddle si el botón izquierdo del ratón con Id 2 está pulsado. Basarse en cómo asigna el valor a la variable miembro m_ButtonRight

	return true;
}

int CMouseInput::GetMovementX() const
{
	//TO DO : Devolver el valor de m_MovementX
}

int CMouseInput::GetMovementY() const
{
	//TO DO : Devolver el valor de m_MovementY
}

int CMouseInput::GetMovementZ() const
{
	//TO DO : Devolver el valor de m_MovementZ
}

bool CMouseInput::IsRightButtonPressed() const
{
	//TO DO : Devolver el valor de m_ButtonRight
}

bool CMouseInput::IsLeftButtonPressed() const
{
	//TO DO : Devolver el valor de m_ButtonLeft
}

bool CMouseInput::IsMiddleButtonPressed() const
{
	//TO DO : Devolver el valor de m_ButtonMiddle
}

bool CMouseInput::LeftButtonBecomesPressed() const
{
	//TO DO : Devolver verdadero si el botón izquierdo del ratón está pulsado actualmente y no estaba pulsado anteriormente utilizando las variables miembro m_ButtonLeft y m_PreviousButtonLeft
}

bool CMouseInput::MiddleButtonBecomesPressed() const
{
	//TO DO : Devolver verdadero si el botón intermedio del ratón está pulsado actualmente y no estaba pulsado anteriormente utilizando las variables miembro m_ButtonMiddle y m_PreviousButtonMiddle
}

bool CMouseInput::RightButtonBecomesPressed() const
{
	//TO DO : Devolver verdadero si el botón derecho del ratón está pulsado actualmente y no estaba pulsado anteriormente utilizando las variables miembro m_ButtonRight y m_PreviousButtonRight
}

bool CMouseInput::LeftButtonBecomesReleased() const
{
	//TO DO : Devolver verdadero si el botón izquierdo del ratón no está pulsado actualmente y estaba pulsado anteriormente utilizando las variables miembro m_ButtonLeft y m_PreviousButtonLeft
}

bool CMouseInput::MiddleButtonBecomesReleased() const
{
	//TO DO : Devolver verdadero si el botón intermedio del ratón no está pulsado actualmente y estaba pulsado anteriormente utilizando las variables miembro m_ButtonMiddle y m_PreviousButtonMiddle
}

bool CMouseInput::RightButtonBecomesReleased() const
{
	//TO DO : Devolver verdadero si el botón derecho del ratón no está pulsado actualmente y estaba pulsado anteriormente utilizando las variables miembro m_ButtonRight y m_PreviousButtonRight
}
