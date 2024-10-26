#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <D3D11.h>
#include "defines.h"
#include <array>

class CRenderManager
{
private:
	ID3D11Device* m_D3DDevice = nullptr;
	ID3D11DeviceContext* m_DeviceContext = nullptr;
	IDXGISwapChain* m_SwapChain = nullptr;
	ID3D11RenderTargetView* m_RenderTargetView = nullptr;
	ID3D11Texture2D* m_DepthStencil = nullptr;
	ID3D11DepthStencilView* m_DepthStencilView = nullptr;
	HWND						m_hWnd = nullptr;
	std::array<float, 4>			m_BackgroundColor;
	bool						m_PaintSolid;
	bool						m_DrawAxisGrid;
	ID3D11RasterizerState* m_WireframeRenderState;
	ID3D11RasterizerState* m_SolidRenderState;
	void Init(HWND hWnd, int Width, int Height);
public:
	CRenderManager(HWND hWnd, int Width, int Height);
	~CRenderManager();

	void BeginRenderDX();
	void EndRenderDX();

	ID3D11Device* GetDevice() const { return m_D3DDevice; }
	ID3D11DeviceContext* GetDeviceContext() const { return m_DeviceContext; }

	std::array<float, 4>& GetBackgroundColorAddress() { return m_BackgroundColor; }

	bool GetPaintSolid() const { return m_PaintSolid; }
	bool* GetPaintSolidAddress() { return &m_PaintSolid; }
	bool* GetDrawAxisGridAddress() { return &m_DrawAxisGrid; }
	bool DrawAxisGrid() { return m_DrawAxisGrid; }
	void SetSolidRenderState(ID3D11DeviceContext* Device);
	void SetWireframeRenderState(ID3D11DeviceContext* Device);
};

#endif
