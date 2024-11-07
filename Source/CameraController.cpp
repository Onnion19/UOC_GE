#include "CameraController.h"
#include <algorithm>

XMFLOAT3 CCameraController::GetRight() const
{
	float yawRight = m_Yaw - DEG2RAD(90.0f);
	return { cosf(yawRight), 0.0f, sinf(yawRight) };
}

XMFLOAT3 CCameraController::GetUp() const
{
	return {
		-sinf(m_Yaw) * sinf(m_Pitch),
		cosf(m_Pitch),
		cosf(m_Yaw) * sinf(m_Pitch)
	};
}

void CCameraController::AddYaw(float Radians)
{
	static constexpr float circle = DEG2RAD(360);
	static constexpr float range = circle * 2;

	auto newYaw = m_Yaw + Radians + circle;
	int loops = newYaw / range;
	newYaw -= loops * range;
	m_Yaw = newYaw - circle;

}
void CCameraController::AddPitch(float Radians)
{
	static constexpr float maxPitch = DEG2RAD(90);
	m_Pitch -= Radians;
	m_Pitch = std::clamp(m_Pitch, -maxPitch, maxPitch);
}
