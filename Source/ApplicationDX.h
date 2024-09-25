#ifndef _APPLICATION_DX_H
#define _APPLICATION_DX_H

#include "defines.h"

class CPlayer;

class CApplicationDX
{
private:
	CPlayer 				*m_Player;
public:	
	CApplicationDX();
	~CApplicationDX();
	
	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Init(HWND hWnd, int Width, int Height);
	void Update();
	void Render();
	CPlayer * GetPlayer() const {return m_Player;}
};

#endif
