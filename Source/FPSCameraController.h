#ifndef INC_CAMERAFPSHOOTER_H_
#define INC_CAMERAFPSHOOTER_H_

#include "CameraController.h"

class CCamera;

class CFPSCameraController : public CCameraController
{
private:
	static constexpr float m_YawSpeed = 100.f;
	static constexpr float m_PitchSpeed = 60.f;
	static constexpr float m_Speed = 5.f;
	static constexpr float m_FastSpeed = 10.f;
public:
	CFPSCameraController();

	
	void Move(float Strafe, float Forward, bool Speed, float ElapsedTime);
	void SetCamera(CCamera *Camera) const;
	void AddYaw(float Radians);
	void AddPitch(float Radians);
	XMFLOAT3 GetDirection() const;
};

#endif
