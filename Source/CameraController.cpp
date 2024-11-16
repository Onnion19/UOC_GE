#include "CameraController.h"
#include <algorithm>

XMFLOAT3 CCameraController::GetRight() const
{
	return {
	   -sinf(m_Yaw),
	   0.0f,
	   cosf(m_Yaw)
	};
}

XMFLOAT3 CCameraController::GetDirection() const
{
	XMFLOAT3 direction = {
	cosf(m_Pitch) * cosf(m_Yaw),
	sinf(m_Pitch),
	cosf(m_Pitch) * sinf(m_Yaw)
	};
	return direction;
}


XMFLOAT3 CCameraController::GetUp() const
{
	auto forward = GetDirection();
	auto forward_vec = XMLoadFloat3(&forward);

	auto right = GetRight();
	auto right_vec = XMLoadFloat3(&right);


	auto up_vec = DirectX::XMVector3Cross(right_vec, forward_vec);
	
	XMFLOAT3 up{};
	XMStoreFloat3(&up, up_vec);

	return up;
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
