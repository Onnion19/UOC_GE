#include <math.h>
#include <stdio.h>
#include "SphericalCameraController.h"
#include "Camera.h"
#include "UOCEngine.h"
#include "InputManager.h"
#include "MouseInput.h"

CSphericalCameraController::CSphericalCameraController() 
//TO DO : Inicializa la variable miembro m_Zoom a 50.0f
//TO DO : Inicializa la variable miembro m_ZoomSpeed a 2.0f
{
}

CSphericalCameraController::~CSphericalCameraController()
{	
}

XMFLOAT3 CSphericalCameraController::GetDirection() const
{
	//TO DO : Calcula la dirección de la cámara utilizando los ángulos Yaw y Pitch
}

void CSphericalCameraController::SetCamera(CCamera *Camera) const
{
	//TO DO : Establecer el FOV de la cámara utilizando el método SetFOV a 50 grados en radianes utilizando la macro DEG2RAD
	//TO DO : Establecer el AspectRatio de la cámara utilizando el método SetAspectRatio a 16.0f/9.0f
	//TO DO : Establecer el LookAt de la cámara utilizando el método SetLookAt a la posición del controlador de cámara
	//TO DO : Establecer la Posición de la cámara utilizando el método SetPosition, la posición de la cámara será la posición del controlador de cámara menos la dirección de nuestro controlador
	//TO DO : Establecer el vector Up de la cámara utilizando el método SetUp, le pasaremos el vector Up de nuestro controlador utilizando nuestro método GetUp
	//TO DO : Llamar al método SetMatrixs de la cámara
}

void CSphericalCameraController::Update(float ElapsedTime)
{
	//TO DO : Añade grados al ángulo yaw del controlador de cámara utilizando el método AddYaw, para ello utilizaremos el método GetMovementX del Input de ratón multiplicado por el elapsedTime y por 30.0f como velocidad
	//TO DO : Añade grados al ángulo pitch del controlador de cámara utilizando el método AddPitch, para ello utilizaremos el método GetMovementY del Input de ratón multiplicado por el elapsedTime y por 30.0f como velocidad
	//TO DO : Añade zoom al controlador de cámara utilizando el método AddZoom, para ello utilizaremos el método GetMovementZ del Input de ratón multiplicado por el elapsedTime y por 2.0f como velocidad
}
