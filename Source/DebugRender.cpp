#include "DebugRender.h"
#include "UOCEngine.h"
#include "VertexTypes.h"
#include "RenderableVertexs.h"
#include "defines.h"
#include <assert.h>
#include "EffectManager.h"

CDebugRender::CDebugRender(ID3D11Device* Device)
{
	constexpr XMFLOAT4 WHITE{ 1.0f, 1.0f, 1.0f, 1.0f };
	constexpr XMFLOAT4 RED{ 1.0f, 0.0f, 0.0f, 1.0f };
	constexpr XMFLOAT4 GREEN{ 0.0f, 0.0f, 0.0f, 1.0f };
	constexpr XMFLOAT4 BLUE{ 0.0f, 0.0f, 1.0f, 1.0f };

	m_Effect = CUOCEngine::GetEngine()->GetEffectManager()->GetEffect(UOC_POSITION_COLOR_VERTEX::GetVertexType());
	//AXIS
	UOC_POSITION_COLOR_VERTEX l_AxisVtxs[6] =
	{
		{XMFLOAT3(0.0f, 0.0f, 0.0f), RED},
		{XMFLOAT3(1.0f, 0.0f, 0.0f), RED},

		{XMFLOAT3(0.0f, 0.0f, 0.0f), GREEN},
		{XMFLOAT3(0.0f, 1.0f, 0.0f), GREEN},

		{XMFLOAT3(0.0f, 0.0f, 0.0f), BLUE},
		{XMFLOAT3(0.0f, 0.0f, 1.0f), BLUE}
	};

	m_AxisRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_AxisVtxs, 6, 3);

	//CUBE
	const float l_SizeCube = 1.0f;
	UOC_POSITION_COLOR_VERTEX l_CubeVtxs[24] =
	{
		//Base 
		{XMFLOAT3(0.0f, 0.0f, 0.0f), WHITE},
		{XMFLOAT3(l_SizeCube, 0.0f, 0.0f), WHITE},


		{XMFLOAT3(l_SizeCube, 0.0f, 0.0f), WHITE},
		{XMFLOAT3(l_SizeCube, 0.0f, l_SizeCube), WHITE},

		{XMFLOAT3(l_SizeCube, 0.0f, l_SizeCube), WHITE},
		{XMFLOAT3(0.f, 0.0f, l_SizeCube), WHITE},

		{XMFLOAT3(0.f, 0.0f, l_SizeCube), WHITE},
		{XMFLOAT3(0.f, 0.0f, 0.f), WHITE},


		// Base elevada
		{XMFLOAT3(0.0f, l_SizeCube, 0.0f), WHITE},
		{XMFLOAT3(l_SizeCube, l_SizeCube, 0.0f), WHITE},


		{XMFLOAT3(l_SizeCube, l_SizeCube, 0.0f), WHITE},
		{XMFLOAT3(l_SizeCube, l_SizeCube, l_SizeCube), WHITE},

		{XMFLOAT3(l_SizeCube, l_SizeCube, l_SizeCube), WHITE},
		{XMFLOAT3(0.f, l_SizeCube, l_SizeCube), WHITE},

		{XMFLOAT3(0.f, l_SizeCube, l_SizeCube), WHITE},
		{XMFLOAT3(0.f, l_SizeCube, 0.f), WHITE},

		//TO DO : Construye todos los vértices de las lineas laterales del cubo para que el tamaño del cubo sea l_SizeCube, debemos crear dos vértices por linea, por tanto 8 vértices
		{XMFLOAT3(0.0f, 0.0f, 0.0f), WHITE},
		{XMFLOAT3(0.0f, l_SizeCube, 0.0f), WHITE},

		{XMFLOAT3(l_SizeCube, 0.0f, 0.0f), WHITE},
		{XMFLOAT3(l_SizeCube, l_SizeCube, 0.0f), WHITE},

		{XMFLOAT3(l_SizeCube, 0.0f, l_SizeCube), WHITE},
		{XMFLOAT3(l_SizeCube, l_SizeCube, l_SizeCube), WHITE},

		{XMFLOAT3(0.f, 0.0f, l_SizeCube), WHITE},
		{XMFLOAT3(0.f, l_SizeCube, l_SizeCube), WHITE}
	};

	m_CubeRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_CubeVtxs, 24, 12);

	//GRID
	constexpr float l_Size = 10.0f;
	constexpr int l_Grid = 10;
	constexpr float deltaGrid = l_Size / l_Grid;
	constexpr auto gridVert = (l_Grid + 1) * 2 * 2;
	constexpr float height = 0.15f;
	UOC_POSITION_COLOR_VERTEX l_GridVtxs[gridVert];

	for (int i = 0; i <= l_Grid; i++)
	{
		const int positionY = i * 2;
		const int positionZ = gridVert / 2 + positionY;
		l_GridVtxs[positionY] = { XMFLOAT3(deltaGrid * i, height, 0.0f), WHITE };
		l_GridVtxs[positionY + 1] = { XMFLOAT3(deltaGrid * i, height, l_Size), WHITE };

		l_GridVtxs[positionZ] = { XMFLOAT3(0.f, height, deltaGrid * i), WHITE };
		l_GridVtxs[positionZ + 1] = { XMFLOAT3(l_Size, height, deltaGrid * i), WHITE };
	}

	m_GridRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_GridVtxs, gridVert, gridVert / 2);

	//SPHERE
	constexpr int l_VertexCircle = 40;
	constexpr int l_circles = 40;
	constexpr int verticesCount = l_VertexCircle * (l_circles) * 4;
	constexpr float thetaDelta = DEG2RAD(180) / l_circles;
	constexpr float sigmaDelta = DEG2RAD(360) / l_VertexCircle;
	constexpr float radius = 1.f;
	UOC_POSITION_COLOR_VERTEX l_SphereVtxs[verticesCount];

	constexpr auto SphericaltoCartesian = [](float thetaRadians, float sigmaRadians, float radius) ->XMFLOAT3 {
		return {
			radius * sin(thetaRadians) * cos(sigmaRadians),
			radius * cos(thetaRadians) + radius, //add radius to offset the sphere to be fully visible.
			radius * sin(thetaRadians) * sin(sigmaRadians)
		};
	};
	
	for (int circle = 0; circle < l_circles; circle++)
	{
		auto theta = thetaDelta * (circle);
		for(int vertice = 0; vertice < l_VertexCircle; vertice++)
		{
			auto sigma = sigmaDelta * vertice;

			auto originalPos = SphericaltoCartesian(theta, sigma, radius);
			auto nextXZpos = SphericaltoCartesian(theta, sigma + sigmaDelta, radius);
			auto nextXYpos = SphericaltoCartesian(theta + thetaDelta, sigma, radius);
			

			auto arrayIndex = circle * l_VertexCircle * 4 + vertice *4;
			assert(arrayIndex + 3 < verticesCount);

			l_SphereVtxs[arrayIndex] = { originalPos, WHITE };
			l_SphereVtxs[arrayIndex+1] = { nextXZpos, WHITE };

			l_SphereVtxs[arrayIndex +2] = { originalPos, WHITE };
			l_SphereVtxs[arrayIndex +3] = { nextXYpos, WHITE };

		}
	}

	m_SphereRenderableVertexs = new CLinesListRenderableVertexs<UOC_POSITION_COLOR_VERTEX>(Device, l_SphereVtxs, verticesCount, verticesCount / 2);
}

CDebugRender::~CDebugRender()
{
	CHECKED_DELETE(m_AxisRenderableVertexs);
	CHECKED_DELETE(m_GridRenderableVertexs);
	CHECKED_DELETE(m_CubeRenderableVertexs);
	CHECKED_DELETE(m_SphereRenderableVertexs);
}


void CDebugRender::DrawAxis(ID3D11DeviceContext* DeviceContext, float Size)
{
	auto effectManager = CUOCEngine::GetEngine()->GetEffectManager();
	assert(effectManager);
	auto& bufferParameters = CUOCEngine::GetEngine()->GetEffectManager()->m_ObjectConstantBufferParameters;
	bufferParameters.m_BaseColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	bufferParameters.m_DebugRenderScale = XMFLOAT4(Size, Size, Size, Size);
	effectManager->SetObjectConstantBuffer(DeviceContext);
	m_AxisRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawGrid(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color)
{
	auto effectManager = CUOCEngine::GetEngine()->GetEffectManager();
	assert(effectManager);
	auto& bufferParameters = CUOCEngine::GetEngine()->GetEffectManager()->m_ObjectConstantBufferParameters;
	bufferParameters.m_BaseColor = Color;
	bufferParameters.m_DebugRenderScale = XMFLOAT4(Size, Size, Size, Size);
	effectManager->SetObjectConstantBuffer(DeviceContext);
	m_GridRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawCube(ID3D11DeviceContext* DeviceContext, float Size, XMFLOAT4 Color)
{
	auto effectManager = CUOCEngine::GetEngine()->GetEffectManager();
	assert(effectManager);
	auto& bufferParameters = CUOCEngine::GetEngine()->GetEffectManager()->m_ObjectConstantBufferParameters;
	bufferParameters.m_BaseColor = Color;
	bufferParameters.m_DebugRenderScale = XMFLOAT4(Size, Size, Size, Size);
	effectManager->SetObjectConstantBuffer(DeviceContext);
	m_CubeRenderableVertexs->Draw(DeviceContext, m_Effect);
}

void CDebugRender::DrawSphere(ID3D11DeviceContext* DeviceContext, float Radius, XMFLOAT4 Color)
{
	auto effectManager = CUOCEngine::GetEngine()->GetEffectManager();
	assert(effectManager);
	auto& bufferParameters = CUOCEngine::GetEngine()->GetEffectManager()->m_ObjectConstantBufferParameters;
	bufferParameters.m_BaseColor = Color;
	bufferParameters.m_DebugRenderScale = XMFLOAT4(Radius, Radius, Radius, Radius);
	effectManager->SetObjectConstantBuffer(DeviceContext);
	m_SphereRenderableVertexs->Draw(DeviceContext, m_Effect);
}
