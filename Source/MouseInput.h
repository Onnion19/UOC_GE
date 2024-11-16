#ifndef INC_MOUSE_H_
#define INC_MOUSE_H_

#include <dinput.h>

class CMouseInput
{
private:
	LPDIRECTINPUT8						m_DI;
	LPDIRECTINPUTDEVICE8				m_Mouse;	

	int									m_MovementX = 0;
	int									m_MovementY = 0;
	int									m_MovementZ = 0;
	bool								m_ButtonRight = false;
	bool								m_PreviousButtonRight = false;
	bool								m_ButtonLeft = false;
	bool								m_PreviousButtonLeft = false;
	bool								m_ButtonMiddle = false;
	bool								m_PreviousButtonMiddle = false;

public:
	CMouseInput(HWND hWnd);
	virtual ~CMouseInput();
	
	bool Update();
	int GetMovementX() const;
	int GetMovementY() const;
	int GetMovementZ() const;
	bool IsLeftButtonPressed() const;
	bool IsMiddleButtonPressed() const;
	bool IsRightButtonPressed() const;

	bool LeftButtonBecomesPressed() const;
	bool MiddleButtonBecomesPressed() const;
	bool RightButtonBecomesPressed() const;

	bool LeftButtonBecomesReleased() const;
	bool MiddleButtonBecomesReleased() const;
	bool RightButtonBecomesReleased() const;
};

#endif
