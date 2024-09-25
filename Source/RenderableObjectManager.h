#ifndef _RENDERABLE_OBJECT_MANAGER_H_
#define _RENDERABLE_OBJECT_MANAGER_H_

#include <vector>
#include <d3d11.h>

class CRenderableObject;

class CRenderableObjectManager
{
protected:
	std::vector<CRenderableObject *>				m_RenderableObjects;
public:
	CRenderableObjectManager();
	virtual ~CRenderableObjectManager();
	void Update(float ElapsedTime);
	void Render(ID3D11DeviceContext *DeviceContext);
	void AddRenderableObject(CRenderableObject *RenderableObject);
};

#endif
