#ifndef PLAYER_H
#define PLAYER_H

#include "defines.h"

class CFPSCameraController;

class CPlayer 
{
private:
	XMFLOAT3				m_Position{ 0.0f, 1.75f, -10.0f };
	float					m_Speed = 10.f;
	float					m_FastSpeed = 20.f;
	float					m_VerticalSpeed = 0.0f;
	float					m_VerticalSpeedJump = 8.f;

	CFPSCameraController	*m_FPSCameraController;
public:
	CPlayer();
	virtual ~CPlayer() = default;
	
	void Update(float ElapsedTime);
	void Move(float Strafe, float Forward, bool Fast, float ElapsedTime);
	void Jump();
};

#endif
