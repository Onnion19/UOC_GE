#include "FPSCameraController.h"
#include "Camera.h"
#include <cmath>

CFPSCameraController::CFPSCameraController()
{
	m_Position = { 0,2,0 };
}



void CFPSCameraController::Move(float Strafe, float Forward, bool Speed, float ElapsedTime)
{
	//TO DO : Calculamos el vector dirección Forward del controlador de cámara utilizando el ángulo m_Yaw
	//TO DO : Calculamos el vector dirección Right del controlador de cámara utilizando el ángulo m_Yaw+DEG2RAD(90.0f)
	//TO DO : Calculamos el vector de movimiento sumando el vector Forward multiplicado por el parámetro Forward y le sumamos el vector Right multiplicado por el parámetro Strafe
	//TO DO : Normalizamos el vector utilizando la función de DirectX XMVector3Normalize
	//TO DO : Calculamos el movimiento multiplicando el vector normalizado por la variable de velocidad m_Speed y por el ElapsedTime
	//TO DO : En caso de que el parámetro Speed sea verdadero multiplicamos el movimiento también por la variable FastSpeed
	//TO DO : Establecemos la posición en m_Position asignándole la posición actual más el movimiento calculado
}

void CFPSCameraController::AddYaw(float Radians)
{
	AddYaw(Radians * m_YawSpeed);
}

void CFPSCameraController::AddPitch(float Radians)
{
	AddPitch(Radians * m_PitchSpeed);
}

void CFPSCameraController::SetCamera(CCamera* Camera) const
{
	Camera->SetFOV(DEG2RAD(50.f));
	Camera->SetAspectRatio(16.f / 9.f);
	{
		const auto x = Camera->GetPosition().x + m_Position.x;
		const auto y = Camera->GetPosition().y + m_Position.y;
		const auto z = Camera->GetPosition().z + m_Position.z;
		Camera->SetLookAt({ x,y,z });
	}
	Camera->SetUp(GetUp());
	Camera->SetMatrixs();
}

XMFLOAT3 CFPSCameraController::GetDirection() const
{
	return {
		std::cos(m_Pitch) * std::sin(m_Yaw),
		std::sin(m_Pitch),
		std::cos(m_Pitch) * std::cos(m_Yaw)
	};
}
