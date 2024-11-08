#ifndef _RENDERABLE_OBJECT_MANAGER_H_
#define _RENDERABLE_OBJECT_MANAGER_H_

#include <vector>
#include <d3d11.h>
#include <memory>
#include "RenderableObject.h"

class CRenderableObjectManager
{
protected:
	std::vector<std::unique_ptr<CRenderableObject>> m_RenderableObjects;
public:
	CRenderableObjectManager() = default;
	virtual ~CRenderableObjectManager() = default;
	void Update(float ElapsedTime);
	void Render(ID3D11DeviceContext *DeviceContext);
	void AddRenderableObject(std::unique_ptr<CRenderableObject>&& RenderableObject);
};

#endif
