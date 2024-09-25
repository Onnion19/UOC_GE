#include "UOCEngine.h"
#include "RenderManager.h"
#include "DebugRender.h"
#include "Player.h"
#include <assert.h>
#include <math.h>
#include "defines.h"
#include "Camera.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "FPSCameraController.h"
#include "EffectManager.h"

CPlayer::CPlayer(void)
//TO DO : Inicializar la variable miembro m_Speed a 10.0f
//TO DO : Inicializar la variable miembro m_FastSpeed a 20.0f
//TO DO : Inicializar la variable miembro m_Position a (0.0f, 1.75f, 0.0f)
//TO DO : Inicializar la variable miembro m_VerticalSpeed a 0.0f
//TO DO : Inicializar la variable miembro m_VerticalSpeedJump a 8.0f
{
	//TO DO : Asignar el controlador de cámara en la variable m_FPSCameraController, para ello debemos pedirle al CameraManager de la clase CUOCEngine el controlador de cámara que tiene por nombre "player"
}

CPlayer::~CPlayer()
{
}

void CPlayer::Move(float Strafe, float Forward, bool Fast, float ElapsedTime)
{
	XMFLOAT3 l_VectorMovement;
	//TO DO : Crear una variable que contenga el ángulo Yaw del controlador de cámara m_FPSCameraController
	//TO DO : Inicializar la variable l_VectorMovement con la dirección de movimiento sobre el plano XZ del personaje según los valores de Strafe y Forward. Strafe moverá al personaje lateralmente y Forward hacia delante
	//TO DO : Incrementar la variable miembro m_VerticalSpeed según la gravedad -9.81 multiplicado por el ElapsedTime
	//TO DO : Normalizar el vector l_VectorMovement utilizando la función de DirectX XMVector3Normalize, para ello deberemos convertir l_VectorMovement de tipo XMFLOAT3 a XMVECTOR
	//TO DO : Multiplicar el vector normalizado por la velocidad m_FastSpeed o m_Speed (dependiendo si está activo el parámetro Fast) por el ElapsedTime y asignarlo a l_VectorMovement 
	//TO DO : Asignar en la componente Y de l_VectorMovement el movimiento en Y multiplicando m_VerticalSpeed por el ElapsedTime
	//TO DO : Incrementar m_Position según el vector l_VectorMovement
	//TO DO : Para evitar que el personaje no caiga infinitamente debemos bloquearlo, para ello si la componente Y de m_Position es menor que 2 asignamos la componente Y de m_Position a 2 y le asignamos la velocidad vertical m_VerticalSpeed el valor de 0
	//TO DO : Establecer la nueva posición en el controlador de cámara m_FPSCameraController con el método SetPosition
}

void CPlayer::Update(float ElapsedTime)
{
	CKeyboardInput *l_KeyboardInput;
	CMouseInput *l_MouseInput;
	//TO DO : Asignar en l_KeyboardInput el device del Keyboard del InputManager que se encuentra en la clase CUOCEngine
	//TO DO : Asignar en l_MouseInput el device del Mouse del InputManager que se encuentra en la clase CUOCEngine
	//TO DO : Incrementar el ángulo Yaw del controlador de cámara m_FPSCameraController utilizando el método AddYaw según el movimiento en -X del ratón que recogemos utilizando el método GetMovementX de la instancia l_MouseInput multiplicado por el ElapsedTime
	//TO DO : Incrementar el ángulo Pitch del controlador de cámara m_FPSCameraController utilizando el método AddPitch según el movimiento en Y del ratón que recogemos utilizando el método GetMovementY de la instancia l_MouseInput multiplicado por el ElapsedTime
	
	float l_Forward=0.0f;
	float l_Strafe=0.0f;
	bool l_MoveFast;

	//TO DO : Asignar en la variable l_MoveFast verdadero si está pulsada la tecla DIK_LSHIFT utilizando el método IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	//TO DO : Si se pulda la tecla DIK_W en el teclado asignamos el valor de 1 a l_Forward. Para saber si se pulsa la tecla utilizamos el método IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	//TO DO : Si se pulda la tecla DIK_S en el teclado asignamos el valor de -1 a l_Forward. Para saber si se pulsa la tecla utilizamos el método IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	//TO DO : Si se pulda la tecla DIK_A en el teclado asignamos el valor de -1 a l_Strafe. Para saber si se pulsa la tecla utilizamos el método IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	//TO DO : Si se pulda la tecla DIK_D en el teclado asignamos el valor de 1 a l_Strafe. Para saber si se pulsa la tecla utilizamos el método IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	//TO DO : Si se pulda la tecla DIK_SPACE en el teclado y m_VerticalSpeed tiene un valor de 0.0f llamamos al método Jump. Para saber si se pulsa la tecla utilizamos el método IsKeyPressed de la instancia del dispositivo de teclado l_KeyboardInput
	//TO DO : Llamar al método Move para mover el personaje
}

void CPlayer::Jump()
{
	//TO DO : Asignar el valor de m_VerticalSpeedJump a la variable miembro m_VerticalSpeed
}
