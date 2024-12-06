#include <cmath>
#include <stdio.h>
#include "SphericalCameraController.h"
#include "Camera.h"
#include "UOCEngine.h"
#include "InputManager.h"
#include "MouseInput.h"


void CSphericalCameraController::SetCamera(CCamera* Camera) const
{
	constexpr auto SphericaltoCartesian = [](float thetaRadians, float sigmaRadians, float radius) ->XMFLOAT3 {
		return {
			radius * sin(thetaRadians) * cos(sigmaRadians),
			radius * cos(thetaRadians) + radius * 1.2f, //add radius to offset the sphere to be fully visible.
			radius * sin(thetaRadians) * sin(sigmaRadians)
		};
		};

	Camera->SetFOV(DEG2RAD(50 + m_Zoom));
	Camera->SetAspectRatio(16.f / 9.f);

	Camera->SetLookAt(m_Position);

	auto cameraPos = SphericaltoCartesian(m_Pitch + DEG2RAD(90), m_Yaw, distance);

	Camera->SetPosition({
		cameraPos.x + m_Position.x,
		cameraPos.y + m_Position.y,
		cameraPos.z + m_Position.z
		});

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
