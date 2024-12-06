#ifndef _APPLICATION_DX_H
#define _APPLICATION_DX_H


#include "defines.h"
#include <memory>
#include "Player.h"


class CApplicationDX
{
private:
	std::unique_ptr<CPlayer> m_Player;
public:
	CApplicationDX() = default;
	~CApplicationDX();

	LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void Init(HWND hWnd, int Width, int Height);
	void Update();
	void Render();
	CPlayer* GetPlayer() const;
};

#endif
