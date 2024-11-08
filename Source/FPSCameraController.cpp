#include "FPSCameraController.h"
#include "Camera.h"
#include <cmath>

#if !NDEBUG
#include <iostream>
#include <format>
#endif

CFPSCameraController::CFPSCameraController()
{
	m_Position = { 0,2,0 };
}



void CFPSCameraController::Move(float Strafe, float Forward, bool Speed, float ElapsedTime)
{

	XMFLOAT3 forwardVec{ cosf(m_Yaw), 0.0f,  sinf(m_Yaw) };
	XMVECTOR forward = XMLoadFloat3(&forwardVec);

	float yawRight = m_Yaw + DEG2RAD(90.0f);
	XMFLOAT3 rightVec{ cosf(yawRight), 0.0f,sinf(yawRight) };
	XMVECTOR right = XMLoadFloat3(&rightVec);

	XMVECTOR movement = DirectX::XMVectorAdd(
		DirectX::XMVectorScale(forward, Forward),
		DirectX::XMVectorScale(right, Strafe)
	);

	movement = DirectX::XMVector3Normalize(movement);

	//TO DO : Calculamos el movimiento multiplicando el vector normalizado por la variable de velocidad m_Speed y por el ElapsedTime
	//TO DO : En caso de que el parámetro Speed sea verdadero multiplicamos el movimiento también por la variable FastSpeed
	float speedMultiplier = Speed ? m_FastSpeed : m_Speed; // Not sure about this
	movement = DirectX::XMVectorScale(movement, speedMultiplier * ElapsedTime);

	XMVECTOR currentPosition = XMLoadFloat3(&m_Position);
	XMVECTOR newPosition = DirectX::XMVectorAdd(currentPosition, movement);
	XMStoreFloat3(&m_Position, newPosition);

}

void CFPSCameraController::AddYaw(float Radians)
{
	CCameraController::AddYaw(Radians * m_YawSpeed);
}

void CFPSCameraController::AddPitch(float Radians)
{
	CCameraController::AddPitch(Radians * m_PitchSpeed);
}

void CFPSCameraController::SetCamera(CCamera* Camera) const
{
	Camera->SetFOV(DEG2RAD(50.f));
	Camera->SetAspectRatio(16.f / 9.f);	

	auto direction = GetDirection();
	XMVECTOR directionVec = XMLoadFloat3(& direction );
	XMVECTOR positionVec = XMLoadFloat3(& m_Position );
	XMFLOAT3 lookAt{};
	auto lookAtVec = DirectX::XMVectorAdd(positionVec, directionVec);
	XMStoreFloat3(&lookAt, lookAtVec);
	Camera->SetLookAt(lookAt);
	Camera->SetPosition(m_Position);
	Camera->SetUp(GetUp());
	Camera->SetMatrixs();
}

XMFLOAT3 CFPSCameraController::GetDirection() const
{
	XMFLOAT3 direction = 	 {
		cos(m_Yaw), sin(m_Pitch),sin(m_Yaw)
	};
	return direction;
}
