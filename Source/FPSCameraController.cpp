#include "FPSCameraController.h"
#include "Camera.h"
#include <cmath>

CFPSCameraController::CFPSCameraController()
{
	m_Position = { 0,2,0 };
}



void CFPSCameraController::Move(float Strafe, float Forward, bool Speed, float ElapsedTime)
{
	//TO DO : Calculamos el vector direcci�n Forward del controlador de c�mara utilizando el �ngulo m_Yaw
	//TO DO : Calculamos el vector direcci�n Right del controlador de c�mara utilizando el �ngulo m_Yaw+DEG2RAD(90.0f)
	//TO DO : Calculamos el vector de movimiento sumando el vector Forward multiplicado por el par�metro Forward y le sumamos el vector Right multiplicado por el par�metro Strafe
	//TO DO : Normalizamos el vector utilizando la funci�n de DirectX XMVector3Normalize
	//TO DO : Calculamos el movimiento multiplicando el vector normalizado por la variable de velocidad m_Speed y por el ElapsedTime
	//TO DO : En caso de que el par�metro Speed sea verdadero multiplicamos el movimiento tambi�n por la variable FastSpeed
	//TO DO : Establecemos la posici�n en m_Position asign�ndole la posici�n actual m�s el movimiento calculado
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
