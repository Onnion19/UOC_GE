#ifndef _UOC_ENGINE_H_
#define _UOC_ENGINE_H_

#include <D3D11.h>
#include "defines.h"
#include <memory>

class CRenderManager;
class CEffectManager;
class CInputManager;
class CCameraManager;
class CDebugRender;
class CFBXManager;
class CRenderableObjectManager;
class CTextureManager;

class CUOCEngine
{
private:
	static CUOCEngine* m_UOCEngine;
	std::unique_ptr<CRenderManager>m_RenderManager;
	bool						m_DrawAntTweakBar;
	std::unique_ptr<CEffectManager >m_EffectManager;
	std::unique_ptr<CInputManager>m_InputManager;
	std::unique_ptr<CCameraManager>m_CameraManager;
	DWORD 						m_PreviousTime;
	float						m_ElapsedTime;
	std::unique_ptr<CDebugRender>m_DebugRender;
	std::unique_ptr<CFBXManager	>m_FBXManager;
	std::unique_ptr<CRenderableObjectManager> m_RenderableObjectManager;
	std::unique_ptr<CTextureManager>m_TextureManager;

	CUOCEngine() = default;

public:
	~CUOCEngine();

	static CUOCEngine* GetEngine();
	void Init(HWND hWnd, int Width, int Height);
	void Destroy();
	void Update();
	void Render();

	CRenderManager* GetRenderManager();
	CEffectManager* GetEffectManager() const;
	CInputManager* GetInputManager() const;
	CCameraManager* GetCameraManager() const ;
	CDebugRender* GetDebugRender() const;
	CFBXManager* GetFBXManager() const;
	CRenderableObjectManager* GetRenderableObjectManager() const;
	CTextureManager* GetTextureManager() const;
	float GetElapsedTime() const { return m_ElapsedTime; }
};

#endif
