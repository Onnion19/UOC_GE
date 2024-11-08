#include "UOCEngine.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "EffectManager.h"
#include "DebugRender.h"
#include "CameraManager.h"
#include "DebugRender.h"
#include "FBXManager.h"
#include "RenderableObjectManager.h"
#include "TextureManager.h"
#include "VertexTypes.h"

CUOCEngine* CUOCEngine::m_UOCEngine = NULL;

CUOCEngine::~CUOCEngine()
{
	Destroy();
}

CUOCEngine* CUOCEngine::GetEngine()
{
	if (!m_UOCEngine)
	{
		m_UOCEngine = new CUOCEngine();
	}

	return m_UOCEngine;
}

void CUOCEngine::Init(HWND hWnd, int Width, int Height)
{
	m_RenderManager = std::make_unique<CRenderManager>(hWnd, Width, Height);
	m_InputManager = std::make_unique<CInputManager>(hWnd);
	m_EffectManager = std::make_unique<CEffectManager>();

	m_DebugRender = std::make_unique<CDebugRender>(m_RenderManager->GetDevice());
	m_CameraManager = std::make_unique<CCameraManager>();
	m_CameraManager->Load("DATA/XML/cameras.xml");


	m_FBXManager = std::make_unique<CFBXManager>();
	m_RenderableObjectManager = std::make_unique<CRenderableObjectManager>();
	m_TextureManager = std::make_unique<CTextureManager>();
	m_PreviousTime = timeGetTime();
}

void CUOCEngine::Update()
{
	const auto currentTime = timeGetTime();
	auto delta_sec = (currentTime - m_PreviousTime) / 1000;
	m_PreviousTime = currentTime;

	m_InputManager->Update();

	CCameraController* l_CameraController = m_CameraManager->GetCameraController("player");

	CKeyboardInput* l_KeyboardInput = m_InputManager->GetKeyboard();

	if (l_KeyboardInput->KeyBecomesPressed(DIK_TAB))
	{
		m_CameraManager->ChangeVision();
	}

	if (l_KeyboardInput->KeyBecomesPressed(DIK_C))
	{
		m_CameraManager->ChangeControl();
	}

	m_CameraManager->Update(static_cast<float>(delta_sec));
	m_RenderableObjectManager->Update(static_cast<float>(delta_sec));
}

void CUOCEngine::Render()
{
	m_RenderManager->BeginRenderDX();
	ID3D11DeviceContext* l_DeviceContext = m_RenderManager->GetDeviceContext();

	if (m_RenderManager->GetPaintSolid())
	{
		m_RenderManager->SetSolidRenderState(l_DeviceContext);
	}
	else
	{
		m_RenderManager->SetWireframeRenderState(l_DeviceContext);
	}


	auto view = m_CameraManager->GetCamera().GetView();
	auto proj = m_CameraManager->GetCamera().GetProjection();

	CEffectManager::m_SceneConstantBufferParameters.m_View = view;
	CEffectManager::m_SceneConstantBufferParameters.m_Projection = proj;

	m_EffectManager->SetSceneConstantBuffer(l_DeviceContext);
	m_RenderableObjectManager->Render(l_DeviceContext);

	if (m_RenderManager->DrawAxisGrid())
	{
		XMMATRIX world = DirectX::XMMatrixIdentity();
		CEffectManager::m_ObjectConstantBufferParameters.m_World = DirectX::XMMatrixTranspose(world);
		m_EffectManager->SetObjectConstantBuffer(l_DeviceContext);
		m_DebugRender->DrawAxis(l_DeviceContext, 8.f);
		m_DebugRender->DrawGrid(l_DeviceContext, 1.f, { 1.f, 1.f, 1.f, 1.f });
		m_DebugRender->DrawCube(l_DeviceContext, 3.f, { 1.f, 1.f, 1.f, 1.f });
		m_DebugRender->DrawSphere(l_DeviceContext, 3.f, { 1.f, 1.f, 1.f, 1.f });
	}
	m_RenderManager->EndRenderDX();
}

void CUOCEngine::Destroy()
{
	m_RenderManager.reset();
	m_EffectManager.reset();
	m_InputManager.reset();
	m_CameraManager.reset();
	m_DebugRender.reset();
	m_FBXManager.reset();
	m_RenderableObjectManager.reset();
	m_TextureManager.reset();
}

CRenderManager* CUOCEngine::GetRenderManager() { return m_RenderManager.get(); }
CEffectManager* CUOCEngine::GetEffectManager() const { return m_EffectManager.get(); }
CInputManager* CUOCEngine::GetInputManager() const { return m_InputManager.get(); }
CCameraManager* CUOCEngine::GetCameraManager() const { return m_CameraManager.get(); }
CDebugRender* CUOCEngine::GetDebugRender() const { return m_DebugRender.get(); }
CFBXManager* CUOCEngine::GetFBXManager() const { return m_FBXManager.get(); }
CRenderableObjectManager* CUOCEngine::GetRenderableObjectManager() const { return m_RenderableObjectManager.get(); }
CTextureManager* CUOCEngine::GetTextureManager() const { return m_TextureManager.get(); }
