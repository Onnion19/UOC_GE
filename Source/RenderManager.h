#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include <D3D11.h>
#include "defines.h"

class CRenderManager
{
private:
	ID3D11Device				*m_D3DDevice;
	ID3D11DeviceContext			*m_DeviceContext;
	IDXGISwapChain				*m_SwapChain;
	ID3D11RenderTargetView		*m_RenderTargetView;
	ID3D11Texture2D				*m_DepthStencil;
	ID3D11DepthStencilView		*m_DepthStencilView;
	HWND						m_hWnd;
	XMFLOAT4					m_BackgroundColor;
	bool						m_PaintSolid;
	bool						m_DrawAxisGrid;
	ID3D11RasterizerState		*m_WireframeRenderState;
	ID3D11RasterizerState		*m_SolidRenderState;
public:
	CRenderManager();
	~CRenderManager();
	
	void Init(HWND hWnd, int Width, int Height);
	void Destroy();
	void BeginRenderDX();
	void EndRenderDX();

	ID3D11Device * GetDevice() const { return m_D3DDevice; }
	ID3D11DeviceContext	* GetDeviceContext() const { return m_DeviceContext; }

	XMFLOAT4 * GetBackgroundColorAddress() { return &m_BackgroundColor; }

	bool GetPaintSolid() const { return m_PaintSolid; }
	bool * GetPaintSolidAddress() { return &m_PaintSolid; }
	bool * GetDrawAxisGridAddress() { return &m_DrawAxisGrid; }
	bool DrawAxisGrid() { return m_DrawAxisGrid; }
	void SetSolidRenderState(ID3D11DeviceContext *Device);
	void SetWireframeRenderState(ID3D11DeviceContext *Device);
};

#endif
