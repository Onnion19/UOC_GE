#ifndef _DEBUGRENDER_H
#define _DEBUGRENDER_H

#include "defines.h"

class CRenderableVertexs;
class CEffect;

class CDebugRender
{
public:
	~CDebugRender();
private:
	CRenderableVertexs				*m_AxisRenderableVertexs;
	CRenderableVertexs				*m_GridRenderableVertexs;
	CRenderableVertexs				*m_CubeRenderableVertexs;
	CRenderableVertexs				*m_SphereRenderableVertexs;
	CEffect							*m_Effect;
public:
	CDebugRender(ID3D11Device *Device);
	void DrawAxis(ID3D11DeviceContext *DeviceContext, float Size);
	void DrawGrid(ID3D11DeviceContext *DeviceContext, float Size, XMFLOAT4 Color);
	void DrawCube(ID3D11DeviceContext *DeviceContext, float Size, XMFLOAT4 Color);
	void DrawSphere(ID3D11DeviceContext *DeviceContext, float Radius, XMFLOAT4 Color);
};

#endif
