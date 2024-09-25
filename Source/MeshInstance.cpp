#include "MeshInstance.h"
#include "FBXStaticMesh.h"
#include "EffectManager.h"
#include "UOCEngine.h"

CMeshInstance::CMeshInstance(CFBXStaticMesh *StaticMesh)
//TO DO : Llamar al constructor vacío de la clase base CRenderableObject
//TO DO : Inicializar la variable miembro m_StaticMesh al valor de StaticMesh que recibimos por parámetro
{
}

CMeshInstance::~CMeshInstance()
{
}

void CMeshInstance::Render(ID3D11DeviceContext *DeviceContext)
{
	//TO DO : Establecer la variable de matriz de mundo m_World que se encuentra en la variable estática m_ObjectConstantBufferParameters de la clase CEffectManager, debemos asignarle el valor que devuelve la matriz transpuesta utilizando la función de DirectX XMMatrixTranspose del GetTransform de la CRenderableObject de la que derivamos
	//TO DO : Llamar al método SetObjectConstantBuffer del EffectManager que se encuentra en el motor
	//TO DO : Llamar al método Render de la variable miembro m_StatiMesh
}
