#include "RenderableObjectManager.h"
#include "RenderableObject.h"
#include "defines.h"

void CRenderableObjectManager::Update(float ElapsedTime)
{
	for (auto&& object : m_RenderableObjects)
	{
		object->Update(ElapsedTime);

	}
}

void CRenderableObjectManager::Render(ID3D11DeviceContext* DeviceContext)
{
	for (auto&& object : m_RenderableObjects)
	{
		object->Render(DeviceContext);
	}
}

void CRenderableObjectManager::AddRenderableObject(std::unique_ptr<CRenderableObject>&& RenderableObject)
{
	assert(std::find(m_RenderableObjects.begin(), m_RenderableObjects.end(), RenderableObject) == m_RenderableObjects.end());
	m_RenderableObjects.emplace_back(std::move(RenderableObject));
}
