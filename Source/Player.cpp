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

	XMFLOAT3 l_VectorMovement{ 0.f, 0.f, 0.f };
	if (std::abs(Strafe) + std::abs(Forward) > 0.01f)
	{
		float multiplier = (Fast ? m_FastSpeed : m_Speed) * ElapsedTime;
		assert(m_FPSCameraController);
		auto forward = m_FPSCameraController->GetDirection();
		auto right = m_FPSCameraController->GetRight();
		XMVECTOR forwardVec = XMLoadFloat3(&forward);
		forwardVec = DirectX::XMVectorScale(forwardVec, Forward);
		XMVECTOR rightVec = XMLoadFloat3(&right);
		rightVec = DirectX::XMVectorScale(rightVec, Strafe);

		auto directionVec = DirectX::XMVectorAdd(forwardVec, rightVec);
		directionVec = DirectX::XMVector3Normalize(directionVec);

		XMVECTOR movementVec = DirectX::XMVectorScale(directionVec, multiplier);
		XMStoreFloat3(&l_VectorMovement, movementVec);


	}
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
