#include "DebugRender.h"
#include "UOCEngine.h"
#include "VertexTypes.h"
#include "RenderableVertexs.h"
#include "defines.h"
#include <assert.h>
#include "EffectManager.h"

CDebugRender::CDebugRender(ID3D11Device *Device)
{
	//TO DO : Establecer la variable m_Effect pidiéndole el Effect a la clase CEffectManager que se encuentra en el motor, pediremos el Efecto que tiene por tipo de vértice UOC_POSITION_COLOR_VERTEX::GetVertexType()
	//AXIS
	UOC_POSITION_COLOR_VERTEX l_AxisVtxs[6]=
	{
		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 1.0f, 0.0f, 0.0f ), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
			
		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		{XMFLOAT3( 0.0f, 1.0f, 0.0f ), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},

		{XMFLOAT3( 0.0f, 0.0f, 0.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		{XMFLOAT3( 0.0f, 0.0f, 1.0f ), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}
	};
	
	m_AxisRenderableVertexs=new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_AxisVtxs, 6, 3);
	
	//CUBE
	const float l_SizeCube=1.0f;
	UOC_POSITION_COLOR_VERTEX l_CubeVtxs[] =
	{
		//TO DO : Construye todos los vértices de la base del cubo para que el tamaño del cubo sea l_SizeCube, debemos crear dos vértices por linea, por tanto 8 vértices
		//TO DO : Construye todos los vértices de la tapa del cubo para que el tamaño del cubo sea l_SizeCube, debemos crear dos vértices por linea, por tanto 8 vértices
		//TO DO : Construye todos los vértices de las lineas laterales del cubo para que el tamaño del cubo sea l_SizeCube, debemos crear dos vértices por linea, por tanto 8 vértices
	};

	//TO DO : Construye la instancia m_CubeRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pasándole los vértices del cubo l_CubeVtxs, el número de vértices y el número de primitivas (número de lineas)

	//GRID
	float l_Size=10.0f;
	const int l_Grid=10;
	UOC_POSITION_COLOR_VERTEX l_GridVtxs[(l_Grid+1)*2*2];
	//TO DO : Construye todos los vértices de la grid en el eje X, cada linea estará formada por dos vértices y el tamaño de la grid será l_Size y el número de secciones de la grid será l_Grid
	//TO DO : Construye todos los vértices de la grid en el eje Z, cada linea estará formada por dos vértices y el tamaño de la grid será l_Size y el número de secciones de la grid será l_Grid
	//TO DO : Construye la instancia m_GridRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pasándole los vértices del cubo l_GridVtxs, el número de vértices y el número de primitivas (número de lineas)
	
	//SPHERE
	const int l_Aristas=10;
	UOC_POSITION_COLOR_VERTEX l_SphereVtxs[4*l_Aristas*l_Aristas];
	//TO DO : Construye todos los vértices de la esfera, para ello crearemos círculos sobre el plano XZ desplazados en el eje Y según el número de Aristas, recordar que al pintarse con lineas esos círculos debemos crear dos vértices por línea
	//TO DO : Construye todos los vértices de la esfera, para ello crearemos círculos sobre el plano XY desplazados en el eje Z según el número de Aristas, recordar que al pintarse con lineas esos círculos debemos crear dos vértices por línea
	//TO DO : Construye la instancia m_SphereRenderableVertexs de tipo CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX> pasándole los vértices de la esfera l_SphereVtxs, el número de vértices y el número de primitivas (número de lineas)
}

CDebugRender::~CDebugRender()
{
	//TO DO : Destruir la variable miembro m_AxisRenderableVertexs utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_GridRenderableVertexs utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_CubeRenderableVertexs utilizando la macro CHECKED_DELETE
	//TO DO : Destruir la variable miembro m_SphereRenderableVertexs utilizando la macro CHECKED_DELETE
}


void CDebugRender::DrawAxis(ID3D11DeviceContext *DeviceContext, float Size)
{
	//TO DO : Establecer el color blanco (XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)) en la variable miembro m_BaseColor que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tamaño según el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al método SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar los ejes utilizando el método Draw de la instancia m_AxisRenderableVertexs utilizando el CEffect m_Effect
}

void CDebugRender::DrawGrid(ID3D11DeviceContext *DeviceContext, float Size, XMFLOAT4 Color)
{
	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tamaño según el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al método SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar la grid utilizando el método Draw de la instancia m_GridRenderableVertexs utilizando el CEffect m_Effect
}

void CDebugRender::DrawCube(ID3D11DeviceContext *DeviceContext, float Size, XMFLOAT4 Color)
{
	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tamaño según el Size en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al método SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar el cubo utilizando el método Draw de la instancia m_CubeRenderableVertexs utilizando el CEffect m_Effect
}

void CDebugRender::DrawSphere(ID3D11DeviceContext *DeviceContext, float Radius, XMFLOAT4 Color)
{
	//TO DO : Establecer el color en la variable miembro m_BaseColor que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Establecer el tamaño según el Radius en la variable miembro m_DebugRenderScale que se encuentra en la variable miembro estática m_ObjectConstantBufferParameters de la clase CEffectManager
	//TO DO : Llamar al método SetObjectConstantBuffer para establecer las constantes del objeto en el shader que se encuentra en el EffectManager del motor
	//TO DO : Pintar la esfera utilizando el método Draw de la instancia m_SphereRenderableVertexs utilizando el CEffect m_Effect
}
