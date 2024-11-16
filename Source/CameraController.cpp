#include "CameraController.h"
#include <algorithm>

XMFLOAT3 CCameraController::GetRight() const
{
	auto forward = GetDirection();
	auto up = GetUp();

	auto forwardvec = XMLoadFloat3(&forward);
	auto upvec = XMLoadFloat3(&up);

	auto rightvec = DirectX::XMVector3Cross(forwardvec, upvec);
	XMFLOAT3 right;
	XMStoreFloat3(&right, rightvec);
	return right;
}


XMFLOAT3 CCameraController::GetUp() const
{
	return {
		sinf(m_Pitch) * cosf(m_Yaw),
		cosf(m_Pitch),
		sinf(m_Pitch) * sinf(m_Yaw)
	};
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

}
void CCameraController::AddPitch(float Radians)
{
	static constexpr float maxPitch = DEG2RAD(90);
	m_Pitch -= Radians;
	m_Pitch = std::clamp(m_Pitch, -maxPitch, maxPitch);

}
