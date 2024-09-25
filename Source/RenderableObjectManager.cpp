#include "RenderableObjectManager.h"
#include "RenderableObject.h"
#include "defines.h"

CRenderableObjectManager::CRenderableObjectManager()
{
}

CRenderableObjectManager::~CRenderableObjectManager()
{
	//TO DO : Recorrer el vector m_RenderableObjects y eliminar todos los elementos del vector utilizando la macro CHECKED_DELETE
}

void CRenderableObjectManager::Update(float ElapsedTime)
{
	//TO DO : Recorrer el vector m_RenderableObjects y llamar al método Update de cada uno de los elementos del vector
}

void CRenderableObjectManager::Render(ID3D11DeviceContext *DeviceContext)
{
	//TO DO : Recorrer el vector m_RenderableObjects y llamar al método Render de cada uno de los elementos del vector
}

void CRenderableObjectManager::AddRenderableObject(CRenderableObject *RenderableObject)
{
	//TO DO : Añadir un elemento dentro del vector m_RenderableObjects utilizando el método push_back
}
