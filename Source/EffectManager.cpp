#include "EffectManager.h"
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"
#include <d3d11shader.h>

CSceneConstantBufferParameters CEffectManager::m_SceneConstantBufferParameters;
CObjectConstantBufferParameters CEffectManager::m_ObjectConstantBufferParameters;
CAnimatedModelConstantBufferParameters CEffectManager::m_AnimatedModelConstantBufferParameters;




CEffectManager::CEffectManager()
{
	auto device = CUOCEngine::GetEngine()->GetRenderManager()->GetDevice();
	assert(device);

	AddEffect<UOC_POSITION_COLOR_VERTEX>(device, "./Data/Effects/DebugRender.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<UOC_POSITION_TEXTURE_VERTEX>(device, "/Data/Effects/UOC_POSITION_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<UOC_POSITION_NORMAL_TEXTURE_VERTEX>(device, "./Data/Effects/UOC_POSITION_NORMAL_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");
	AddEffect<UOC_POSITION_COLOR_TEXTURE_VERTEX>(device, "./Data/Effects/UOC_POSITION_COLOR_TEXTURE_VERTEXShader.fx", "VS", "vs_4_0", "PS", "ps_4_0");

	//Not sure about that constat buffer size
	CreateConstantBuffer(device, sizeof(CSceneConstantBufferParameters), &m_SceneConstantBuffer);
	CreateConstantBuffer(device, sizeof(CObjectConstantBufferParameters), &m_ObjectConstantBuffer);
	CreateConstantBuffer(device, sizeof(CAnimatedModelConstantBufferParameters), &m_AnimatedModelConstantBuffer);
}

CEffectManager::~CEffectManager()
{
	CHECKED_RELEASE(m_SceneConstantBuffer);
	CHECKED_RELEASE(m_ObjectConstantBuffer);
	CHECKED_RELEASE(m_AnimatedModelConstantBuffer);
}

bool CEffectManager::CreateConstantBuffer(ID3D11Device* Device, UINT ConstantBufferSize, ID3D11Buffer** ConstantBuffer)
{
	//NOTA : El siguiente fragmento de código crea una descripción de buffer de DirectX para crearlo posteriormente utilizando el método CreateBuffer
	D3D11_BUFFER_DESC l_BufferDescription;
	ZeroMemory(&l_BufferDescription, sizeof(l_BufferDescription));

	l_BufferDescription.Usage = D3D11_USAGE_DEFAULT;
	l_BufferDescription.ByteWidth = ConstantBufferSize;
	l_BufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	l_BufferDescription.CPUAccessFlags = 0;
	if (FAILED(Device->CreateBuffer(&l_BufferDescription, NULL, ConstantBuffer)))
		return false;

	return true;
}

void CEffectManager::SetConstantBuffer(ID3D11DeviceContext* DeviceContext, ID3D11Buffer* ConstantBuffer, void* Data, UINT IdSlot)
{
	DeviceContext->UpdateSubresource(ConstantBuffer, 0, nullptr, Data, 0, 0);
	DeviceContext->VSSetConstantBuffers(IdSlot, 1, &ConstantBuffer);
	DeviceContext->PSSetConstantBuffers(IdSlot, 1, &ConstantBuffer);
}

void CEffectManager::SetSceneConstantBuffer(ID3D11DeviceContext* DeviceContext)
{
	SetConstantBuffer(DeviceContext, m_SceneConstantBuffer, &m_SceneConstantBufferParameters, 0);
}

void CEffectManager::SetObjectConstantBuffer(ID3D11DeviceContext* DeviceContext)
{
	SetConstantBuffer(DeviceContext, m_ObjectConstantBuffer, &m_ObjectConstantBufferParameters, 1);
}

void CEffectManager::SetAnimatedModelConstantBuffer(ID3D11DeviceContext* DeviceContext)
{
	SetConstantBuffer(DeviceContext, m_AnimatedModelConstantBuffer, &m_AnimatedModelConstantBufferParameters, 2);
}

CEffect* CEffectManager::GetEffect(const std::string& Name)
{
	auto iter = m_Effects.find(Name);
	return (iter != m_Effects.end()) ? iter->second.get() : nullptr;
}

CEffect* CEffectManager::GetEffect(unsigned int VertexType)
{
	auto iter = m_EffectsByVertexType.find(VertexType);
	return (iter != m_EffectsByVertexType.end()) ? iter->second.get() : nullptr;
}


