#include "CameraController.h"

CCameraController::CCameraController()
//TO DO : Inicializar la variable m_Yaw a 0.0f
//TO DO : Inicializar la variable m_Pitch a 0.0f
{
}
CCameraController::~CCameraController()
{
}

XMFLOAT3 CCameraController::GetRight() const
{
	//TO DO : Calcular el vector Right de la cámara, para ello utilizaremos el ángulo Yaw-DEG2RAD(90.0f) de la cámara
}

XMFLOAT3 CCameraController::GetUp() const
{
	//TO DO : Calcular el vector Up de la cámara, para ello utilizaremos los ángulos Yaw y Pitch de la cámara
}

void CCameraController::AddYaw(float Radians)
{
	//TO DO : Incrementar el ángulo Yaw de la cámara según el parámetro Radians
	//TO DO : Si el ángulo Yaw es superior a 360 grados decrementarlo en 360 grados para que siempre entre -360 y 360 grados
	//TO DO : Si el ángulo Yaw es inferior a -360 grados incrementarlo en 360 grados para que siempre entre -360 y 360 grados
}
void CCameraController::AddPitch(float Radians)
{
	//TO DO : Decremenetar el ángulo Pitch de la cámara según el parámetro Radians
	//NOTA : Hacer un clamp consiste en limitar un valor en que no supere un cierto valor
	//TO DO : Hacer un clamp del ángulo entre 90 y -90 grados
}
