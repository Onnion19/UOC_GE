#include "RenderableObject.h"



void CRenderableObject::Update(float)
{
}

void CRenderableObject::Render(ID3D11DeviceContext*)
{
}

XMMATRIX CRenderableObject::GetTransform()
{
	const XMMATRIX l_TranslationMatrix = DirectX::XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	const XMMATRIX l_RotationXMatrix = DirectX::XMMatrixRotationX(m_Rotation.x);
	const XMMATRIX l_RotationYMatrix = DirectX::XMMatrixRotationY(m_Rotation.y);
	const XMMATRIX l_RotationZMatrix = DirectX::XMMatrixRotationZ(m_Rotation.z);
	const XMMATRIX l_ScaleMatrix = DirectX::XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	const XMMATRIX l_RotationMatrix = l_RotationXMatrix * l_RotationYMatrix * l_RotationZMatrix;

	return l_ScaleMatrix * l_RotationMatrix * l_TranslationMatrix;
}
