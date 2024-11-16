#include "FBXStaticMesh.h"
#include "defines.h"
#include "RenderableVertexs.h"
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include <algorithm>

CFBXStaticMesh::CFBXStaticMesh() : m_Effect(nullptr)
{
}

CFBXStaticMesh::~CFBXStaticMesh()
{
}

bool CFBXStaticMesh::Generate(FbxNode* Node, FbxMesh* Mesh)
{
	CUOCEngine* l_Engine = CUOCEngine::GetEngine();
	ID3D11Device* l_Device = l_Engine->GetRenderManager()->GetDevice();

	const char* l_Name = Node->GetName();
	int l_MaterialCount = Node->GetMaterialCount();
	for (int i = 0; i < l_MaterialCount; ++i)
	{
		FbxSurfaceMaterial* l_FbxSurfaceMaterial = Node->GetMaterial(i);
		const char* l_MaterialName = l_FbxSurfaceMaterial->GetName();

		FbxProperty l_Property = l_FbxSurfaceMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
		int lLayeredTextureCount = l_Property.GetSrcObjectCount<FbxLayeredTexture>();
		int lNbTextures = l_Property.GetSrcObjectCount<FbxTexture>();
		int l_TexturesCount = l_Property.GetSrcObjectCount<FbxTexture>();
		for (int j = 0; j < l_TexturesCount; j++)
		{
			const FbxFileTexture* l_FbxFileTexture = FbxCast<FbxFileTexture>(l_Property.GetSrcObject<FbxTexture>(j));
			const char* l_FileName = l_FbxFileTexture->GetFileName();
			CTexture* l_Texture = l_Engine->GetTextureManager()->LoadTexture(l_Device, l_FileName);
			m_Textures.push_back(l_Texture);
		}
	}

	FbxVector4* l_Vertexs = Mesh->GetControlPoints();
	FbxLayerElementArrayTemplate<FbxVector4>* l_Normals;
	FbxLayerElementArrayTemplate<FbxVector2>* l_TexCoords;

	bool l_Loaded = Mesh->GetNormals(&l_Normals);
	Mesh->GetTextureUV(&l_TexCoords, FbxLayerElement::eTextureDiffuse);
	FbxLayerElementArrayTemplate<int>* l_MaterialIndices;
	Mesh->GetMaterialIndices(&l_MaterialIndices);
	std::vector<std::vector<UOC_POSITION_NORMAL_TEXTURE_VERTEX>> l_FullVertexs;
	std::vector<std::vector<unsigned short>> l_Indices;

	std::vector < std::unordered_map <int, unsigned short>> l_verticesMap;
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		l_FullVertexs.push_back(std::vector<UOC_POSITION_NORMAL_TEXTURE_VERTEX>());
		l_Indices.push_back(std::vector<unsigned short>());
		l_verticesMap.emplace_back(std::unordered_map <int, unsigned short>{});
	}

	for (int i = 0; i < Mesh->GetPolygonCount(); ++i)
	{
		int l_MaterialId = l_MaterialIndices->GetAt(i);
		int l_PolygonVertexsCount = Mesh->GetPolygonSize(i);
		assert(l_PolygonVertexsCount == 3);
		for (int vertice = 0; vertice < l_PolygonVertexsCount; vertice++)
		{
			int l_Index = Mesh->GetPolygonVertex(i, vertice);

			auto vertice_iter = l_verticesMap[l_MaterialId].find(l_Index);
			if (vertice_iter != l_verticesMap[l_MaterialId].end())
			{
				l_Indices[l_MaterialId].push_back(vertice_iter->second);
				continue;
			}

			FbxVector4 l_Vertex = l_Vertexs[l_Index].mData;
			FbxVector4 l_Normal = l_Normals->GetAt(i * 3 + vertice);
			int l_TexCoordIndex = Mesh->GetTextureUVIndex(i, vertice, FbxLayerElement::eTextureDiffuse);
			FbxVector2 l_TexCoord = l_TexCoords->GetAt(l_TexCoordIndex);			
			UOC_POSITION_NORMAL_TEXTURE_VERTEX l_FullVertex(XMFLOAT3(-(float)l_Vertex.mData[0], (float)l_Vertex.mData[2], (float)l_Vertex.mData[1]), XMFLOAT3(-(float)l_Normal.mData[0], (float)l_Normal.mData[2], (float)l_Normal.mData[1]), XMFLOAT2((float)l_TexCoord.mData[0], 1.0f - (float)l_TexCoord.mData[1]));
			l_FullVertexs[l_MaterialId].emplace_back(l_FullVertex);
			l_verticesMap[l_MaterialId][l_Index] = static_cast<unsigned short>(l_FullVertexs[l_MaterialId].size()-1);
			l_Indices[l_MaterialId].emplace_back((unsigned short)l_FullVertexs[l_MaterialId].size()-1);


			if (l_FullVertex.Position.x < m_BBMin.x || i == 0)
				m_BBMin.x = l_FullVertex.Position.x;
			if (l_FullVertex.Position.y < m_BBMin.y || i == 0)
				m_BBMin.y = l_FullVertex.Position.y;
			if (l_FullVertex.Position.z < m_BBMin.z || i == 0)
				m_BBMin.z = l_FullVertex.Position.z;

			if (l_FullVertex.Position.x > m_BBMax.x || i == 0)
				m_BBMax.x = l_FullVertex.Position.x;
			if (l_FullVertex.Position.y > m_BBMax.y || i == 0)
				m_BBMax.y = l_FullVertex.Position.y;
			if (l_FullVertex.Position.z > m_BBMax.z || i == 0)
				m_BBMax.z = l_FullVertex.Position.z;
		}
	}

	m_Position = XMFLOAT3((m_BBMin.x + m_BBMax.x) / 2.0f, (m_BBMin.y + m_BBMax.y) / 2.0f, (m_BBMin.z + m_BBMax.z) / 2.0f);
	for (size_t i = 0; i < m_Textures.size(); ++i)
	{
		for (int j = 0; j < l_FullVertexs[i].size(); ++j)
		{
			float l_Radius = static_cast<float>(LENGTH(m_Position, l_FullVertexs[i][j].Position));
			if (l_Radius > m_Radius || (i == 0 && j == 0))
				m_Radius = l_Radius;
		}
	}
	for (size_t i = 0; i < m_Textures.size(); ++i)
	{
		CRenderableVertexs* l_RenderableVertexs = new CTriangleListRenderableIndexed16Vertexs<UOC_POSITION_NORMAL_TEXTURE_VERTEX>(l_Device, &l_FullVertexs[i][0].Position.x, (unsigned int)l_FullVertexs[i].size(), &l_Indices[i][0], (unsigned int)l_Indices[i].size());
		m_RenderableVertexs.emplace_back(l_RenderableVertexs);
	}

	m_Effect = l_Engine->GetEffectManager()->GetEffect(UOC_POSITION_NORMAL_TEXTURE_VERTEX::GetVertexType());
	return true;
}

void CFBXStaticMesh::Render(ID3D11DeviceContext* DeviceContext)
{
	for (auto i = 0u; i < m_RenderableVertexs.size(); i++)
	{
		if (!m_Textures[i] || !m_RenderableVertexs[i]) continue;
		m_Textures[i]->Activate(DeviceContext, 0);
		m_RenderableVertexs[i]->DrawIndexed(DeviceContext, m_Effect);
	}
}


bool CFBXStaticMesh::IsInBoundingBox(const XMFLOAT3& Pos)
{
	auto horizontal = Pos.x >= m_BBMin.x && Pos.x <= m_BBMax.x;
	auto vertical = Pos.y >= m_BBMin.y && Pos.y <= m_BBMax.y;
	return horizontal && vertical;
}
