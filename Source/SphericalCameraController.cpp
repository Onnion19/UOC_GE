#include <cmath>
#include <stdio.h>
#include "SphericalCameraController.h"
#include "Camera.h"
#include "UOCEngine.h"
#include "InputManager.h"
#include "MouseInput.h"




XMFLOAT3 CSphericalCameraController::GetDirection() const
{
	return {
		std::cos(m_Pitch) * std::sin(m_Yaw),
		std::sin(m_Pitch),
		std::cos(m_Pitch) * std::cos(m_Yaw)
	};
}

void CSphericalCameraController::SetCamera(CCamera* Camera) const
{
	Camera->SetFOV(DEG2RAD(50));
	Camera->SetAspectRatio(16.f / 9.f);
	Camera->SetLookAt(m_Position);
	{
		const auto x = Camera->GetPosition().x - m_Position.x;
		const auto y = Camera->GetPosition().y - m_Position.y;
		const auto z = Camera->GetPosition().z - m_Position.z;
		Camera->SetPosition({ x,y,z });
	}
	Camera->SetUp(GetUp());
	Camera->SetMatrixs();
}

void CSphericalCameraController::Update(float ElapsedTime)
{
	auto mouseInput = CUOCEngine::GetEngine()->GetInputManager()->GetMouse();
	AddYaw(mouseInput->GetMovementX() * ElapsedTime * m_RotationSpeed);
	AddPitch(mouseInput->GetMovementY() * ElapsedTime * m_RotationSpeed);
	AddZoom(mouseInput->GetMovementZ() * ElapsedTime * m_ZoomSpeed);
}
