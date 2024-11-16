#include "ApplicationDX.h"
#include <assert.h>
#include "defines.h"
#include "DebugRender.h"
#include "Camera.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "EffectManager.h"
#include "VertexTypes.h"
#include "Player.h"
#include "FBXManager.h"
#include "EffectManager.h"
#include "UOCEngine.h"
#include "RenderManager.h"

CApplicationDX::~CApplicationDX()
{
	auto engine = CUOCEngine::GetEngine();
	engine->Destroy();
	CHECKED_DELETE(engine);
}

void CApplicationDX::Init(HWND hWnd, int Width, int Height)
{
	CUOCEngine::GetEngine()->Init(hWnd, Width, Height);
	m_Player = std::make_unique<CPlayer>();
	CUOCEngine::GetEngine()->GetFBXManager()->Load("data/models/world/World.fbx");
}

void CApplicationDX::Render()
{
	CUOCEngine::GetEngine()->Render();
}

CPlayer* CApplicationDX::GetPlayer() const
{
	return m_Player.get();
}

void CApplicationDX::Update()
{
	CUOCEngine::GetEngine()->Update();
	auto delta = CUOCEngine::GetEngine()->GetElapsedTime();
	m_Player->Update(delta);
}

LRESULT WINAPI CApplicationDX::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;
			break;
		}
	}
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}