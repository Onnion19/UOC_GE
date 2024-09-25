#ifndef _UOC_ENGINE_H_
#define _UOC_ENGINE_H_

#include <D3D11.h>
#include "defines.h"

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
	static CUOCEngine			*m_UOCEngine;
	CRenderManager				*m_RenderManager;
	bool						m_DrawAntTweakBar;
	CEffectManager 				*m_EffectManager;
	CInputManager				*m_InputManager;
	CCameraManager				*m_CameraManager;
	DWORD 						m_PreviousTime;
	float						m_ElapsedTime;
	CDebugRender				*m_DebugRender;
	CFBXManager					*m_FBXManager;
	CRenderableObjectManager	*m_RenderableObjectManager;
	CTextureManager				*m_TextureManager;

	CUOCEngine();

public:
	~CUOCEngine();

	static CUOCEngine * GetEngine();
	void Init(HWND hWnd, int Width, int Height);
	void Destroy();
	void Update();
	void Render();

	CRenderManager * GetRenderManager() { return m_RenderManager; }
	CEffectManager * GetEffectManager() const { return m_EffectManager; }
	CInputManager * GetInputManager() const { return m_InputManager; }
	CCameraManager * GetCameraManager() const { return m_CameraManager; }
	CDebugRender * GetDebugRender() const { return m_DebugRender; }
	CFBXManager	* GetFBXManager() const { return m_FBXManager; }
	CRenderableObjectManager * GetRenderableObjectManager() const { return m_RenderableObjectManager; }
	CTextureManager * GetTextureManager() const { return m_TextureManager; }
	float GetElapsedTime() const { return m_ElapsedTime; }
};

#endif
