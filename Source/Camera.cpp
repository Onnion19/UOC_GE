#include "Camera.h"

void CCamera::SetMatrixs()
{
	//NOTA : Para construir una variable de tipo XMVECTOR utilizar la función de DirectX::XMVectorSet
	auto eye = DirectX::XMVectorSet(m_Position.x, m_Position.y, m_Position.z, 0);
	auto lookAt = DirectX::XMVectorSet(m_LookAt.x, m_LookAt.y, m_LookAt.z, 0);
	// Not sure about this up vector. 4d should be 1 representing a vector or 0?
	auto up = DirectX::XMVectorSet(m_Up.x, m_Up.y, m_Up.z, 1);

	m_View = DirectX::XMMatrixLookAtRH(eye, lookAt, up);

	m_Projection = DirectX::XMMatrixPerspectiveFovRH(m_FOV, m_AspectRatio, m_ZNear, m_ZFar);
}
