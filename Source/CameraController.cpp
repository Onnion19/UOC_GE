#include "CameraController.h"
#include <algorithm>
#include <iostream>
#include <format>

XMFLOAT3 CCameraController::GetRight() const
{
	float yawRight = m_Yaw - DEG2RAD(90.0f);
	return { cosf(yawRight), 0.0f, sinf(yawRight) };
}

XMFLOAT3 CCameraController::GetUp() const
{
	/*return {
		-sinf(m_Yaw) * sinf(m_Pitch),
		cosf(m_Pitch),
		cosf(m_Yaw) * sinf(m_Pitch)
	};*/

	return { 0,1,0 };
}

CCameraController::~CCameraController()
{
}

void CCameraController::AddYaw(float Radians)
{
	static constexpr float circle = DEG2RAD(360);
	static constexpr float range = circle * 2;

	m_Yaw += Radians;

	if (m_Yaw < -circle)
	{
		m_Yaw += range;
	}
	else if (m_Yaw > circle)
	{
		m_Yaw -= range;
	}
#if !NDEBUG
	std::cerr << std::format("Yaw: {}", RAD2DEG(m_Yaw)) << std::endl;
#endif

}
void CCameraController::AddPitch(float Radians)
{
	static constexpr float maxPitch = DEG2RAD(90);
	m_Pitch -= Radians;
	m_Pitch = std::clamp(m_Pitch, -maxPitch, maxPitch);

#if !NDEBUG
	std::cerr << std::format("Ptich: {}", RAD2DEG(m_Pitch)) << std::endl;
#endif
}
