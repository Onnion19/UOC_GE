#include "MeshInstance.h"
#include "FBXStaticMesh.h"
#include "EffectManager.h"
#include "UOCEngine.h"

CMeshInstance::CMeshInstance(CFBXStaticMesh* StaticMesh)
	: CRenderableObject()
	, m_StaticMesh(StaticMesh)

{
}

void CMeshInstance::Render(ID3D11DeviceContext* DeviceContext)
{
	auto effectManager = CUOCEngine::GetEngine()->GetEffectManager();
	assert(effectManager);

	effectManager->m_ObjectConstantBufferParameters.m_World = DirectX::XMMatrixTranspose(GetTransform());
	effectManager->SetObjectConstantBuffer(DeviceContext);

	assert(m_StaticMesh);
	m_StaticMesh->Render(DeviceContext);
}
