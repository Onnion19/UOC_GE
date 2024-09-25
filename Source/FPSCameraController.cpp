#include "FPSCameraController.h"
#include "Camera.h"

CFPSCameraController::CFPSCameraController()
//TO DO : Inicializa la variable miembro m_YawSpeed a 100.0f
//TO DO : Inicializa la variable miembro m_PitchSpeed a 60.0f
//TO DO : Inicializa la variable miembro m_Speed a 5.0f
//TO DO : Inicializa la variable miembro m_FastSpeed a 10.0f
//TO DO : Inicializa la variable miembro m_Position a 0, 2, 0
{
}

CFPSCameraController::~CFPSCameraController()
{	
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
	//TO DO : Llama al método AddYaw de la clase base CCameraController pasándole el ángulo -Radians multiplicado por la variable m_YawSpeed
}

void CFPSCameraController::AddPitch(float Radians)
{
	//TO DO : Llama al método AddPitch de la clase base CCameraController pasándole el ángulo Radians multiplicado por la variable m_PitchSpeed
}

void CFPSCameraController::SetCamera(CCamera *Camera) const
{
	//TO DO : Establecer el FOV de la cámara utilizando el método SetFOV a 50 grados en radianes utilizando la macro DEG2RAD
	//TO DO : Establecer el AspectRatio de la cámara utilizando el método SetAspectRatio a 16.0f/9.0f
	//TO DO : Establecer la posición de la cámara utilizando el método SetPosition
	//TO DO : Establecer el LookAt de la cámara utilizando el método SetLookAt, el lookat será la posición más la dirección de nuestro controlador
	//TO DO : Establecer el vector Up de la cámara utilizando el método SetUp, le pasaremos el vector Up de nuestro controlador utilizando nuestro método GetUp
	//TO DO : Llamar al método SetMatrixs de la cámara
}

XMFLOAT3 CFPSCameraController::GetDirection() const
{
	//TO DO : Devuelve la dirección del controlador de cámara utilizando lós ángulos m_Yaw y m_Pitch
}
