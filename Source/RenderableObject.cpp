#include "RenderableObject.h"

CRenderableObject::CRenderableObject()
//TO DO : Inicializar la variable miembro m_Position a 0, 0, 0
//TO DO : Inicializar la variable miembro m_Scale a 1, 1, 1
//TO DO : Inicializar la variable miembro m_Rotation a 0, 0, 0
{
}

CRenderableObject::~CRenderableObject()
{
}

void CRenderableObject::Update(float ElapsedTime)
{
}

void CRenderableObject::Render(ID3D11DeviceContext *DeviceContext)
{
}

XMMATRIX CRenderableObject::GetTransform()
{
	XMMATRIX l_TranslationMatrix, l_RotationMatrix, l_RotationXMatrix, l_RotationYMatrix, l_RotationZMatrix, l_ScaleMatrix;
	//TO DO : Calcular la matriz de traslación l_TranslationMatrix utilizando la función de DirectX::XMMatrixTranslation y la posición que está guardada en la variable m_Position
	//TO DO : Calcular la matriz de rotación en X l_RotationXMatrix utilizando la función de DirectX::XMMatrixRotationX y la rotación que está guardada en la variable m_Rotation.x
	//TO DO : Calcular la matriz de rotación en Y l_RotationYMatrix utilizando la función de DirectX::XMMatrixRotationY y la rotación que está guardada en la variable m_Rotation.y
	//TO DO : Calcular la matriz de rotación en Z l_RotationZMatrix utilizando la función de DirectX::XMMatrixRotationZ y la rotación que está guardada en la variable m_Rotation.z
	//TO DO : Calcular la matriz de escala l_ScaleMatrix utilizando la función de DirectX::XMMatrixScaling y la escala que está guardada en la variable m_Scale
	//TO DO : Calcular la matriz de rotación l_RotationMatrix multiplicando las variables de rotación l_RotationXMatrix por l_RotationYMatrix por l_RotationZMatrix
	//TO DO : Devolver el cálculo de multiplicar la matriz de escala l_ScaleMatrix por l_RotationMatrix por l_TranslationMatrix
}
