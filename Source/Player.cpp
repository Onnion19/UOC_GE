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

#if !NDEBUG
#include <iostream>
#include <format>
#endif

CPlayer::CPlayer(void)
{
	m_FPSCameraController = static_cast<CFPSCameraController*>(CUOCEngine::GetEngine()->GetCameraManager()->GetCameraController("player"));
}

void CPlayer::Move(float Strafe, float Forward, bool Fast, float ElapsedTime)
{
	float multiplier = (Fast ? m_FastSpeed : m_Speed) * ElapsedTime;
	XMFLOAT3 movementMultiplier(multiplier, 0, multiplier);
	XMVECTOR movementMultiplierVec = XMLoadFloat3(&movementMultiplier);

	XMFLOAT3 l_VectorMovement{ Forward, 0.f, Strafe };
	XMVECTOR l_Vec = XMLoadFloat3(&l_VectorMovement);
	l_Vec = DirectX::XMVector3Normalize(l_Vec);

	assert(m_FPSCameraController);
	auto direction = m_FPSCameraController->GetDirection();
	XMVECTOR directionVec = XMLoadFloat3(&direction);

	XMVECTOR movementVec = DirectX::XMVectorMultiply(l_Vec, movementMultiplierVec);
	movementVec = DirectX::XMVectorMultiply(movementVec, directionVec);

	XMStoreFloat3(&l_VectorMovement, movementVec);

	m_VerticalSpeed += -9.81f * ElapsedTime;
	l_VectorMovement.y = m_VerticalSpeed * ElapsedTime;


	m_Position.x += l_VectorMovement.x;
	m_Position.y += l_VectorMovement.y;
	m_Position.z += l_VectorMovement.z;


	if (m_Position.y < 2.0f)
	{
		m_Position.y = 2.0f;
		m_VerticalSpeed = 0.0f;
	}
	m_FPSCameraController->SetPosition(m_Position);

}

void CPlayer::Update(float ElapsedTime)
{
	auto inputManager = CUOCEngine::GetEngine()->GetInputManager();
	assert(inputManager);
	CKeyboardInput* l_KeyboardInput = inputManager->GetKeyboard();
	CMouseInput* l_MouseInput = inputManager->GetMouse();

	m_FPSCameraController->AddYaw(l_MouseInput->GetMovementX() * ElapsedTime);
	m_FPSCameraController->AddPitch(l_MouseInput->GetMovementY() * ElapsedTime);

	float l_Forward = 0.0f;
	float l_Strafe = 0.0f;
	bool l_MoveFast = l_KeyboardInput->IsKeyPressed(DIK_LSHIFT);


	if (l_KeyboardInput->IsKeyPressed(DIK_W))
	{
		l_Forward = 1.f;
	}
	else if (l_KeyboardInput->IsKeyPressed(DIK_S))
	{
		l_Forward = -1.f;
	}

	if (l_KeyboardInput->IsKeyPressed(DIK_A))
	{
		l_Strafe = -1.f;
	}
	else if (l_KeyboardInput->IsKeyPressed(DIK_D))
	{
		l_Strafe = 1.f;
	}

	if (l_KeyboardInput->IsKeyPressed(DIK_SPACE) && m_VerticalSpeed <= 0.f)
	{
		Jump();
	}

	Move(l_Strafe, l_Forward, l_MoveFast, ElapsedTime);
}

void CPlayer::Jump()
{
	m_VerticalSpeed = m_VerticalSpeedJump;
}
