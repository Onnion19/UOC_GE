#include "FBXStaticMesh.h"
#include "defines.h"
#include "RenderableVertexs.h"
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"
#include "TextureManager.h"

CFBXStaticMesh::CFBXStaticMesh() : m_Effect(nullptr)
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
	for (int i = 0; i < m_Textures.size(); ++i)
	{
		l_FullVertexs.push_back(std::vector<UOC_POSITION_NORMAL_TEXTURE_VERTEX>());
		l_Indices.push_back(std::vector<unsigned short>());
	}

	for (int i = 0; i < Mesh->GetPolygonCount(); ++i)
	{
		int l_MaterialId = l_MaterialIndices->GetAt(i);
		int l_PolygonVertexsCount = Mesh->GetPolygonSize(i);
		int l_Index0 = Mesh->GetPolygonVertex(i, 0);
		int l_Index1 = Mesh->GetPolygonVertex(i, 1);
		int l_Index2 = Mesh->GetPolygonVertex(i, 2);

		FbxVector4 l_Vertex0 = l_Vertexs[l_Index0].mData;
		FbxVector4 l_Vertex1 = l_Vertexs[l_Index1].mData;
		FbxVector4 l_Vertex2 = l_Vertexs[l_Index2].mData;

		FbxVector4 l_Normal0 = l_Normals->GetAt(i * 3);
		FbxVector4 l_Normal1 = l_Normals->GetAt(i * 3 + 1);
		FbxVector4 l_Normal2 = l_Normals->GetAt(i * 3 + 2);

		int l_TexCoordIndex0 = Mesh->GetTextureUVIndex(i, 0, FbxLayerElement::eTextureDiffuse);
		int l_TexCoordIndex1 = Mesh->GetTextureUVIndex(i, 1, FbxLayerElement::eTextureDiffuse);
		int l_TexCoordIndex2 = Mesh->GetTextureUVIndex(i, 2, FbxLayerElement::eTextureDiffuse);

		FbxVector2 l_TexCoord0 = l_TexCoords->GetAt(l_TexCoordIndex0);
		FbxVector2 l_TexCoord1 = l_TexCoords->GetAt(l_TexCoordIndex1);
		FbxVector2 l_TexCoord2 = l_TexCoords->GetAt(l_TexCoordIndex2);

		UOC_POSITION_NORMAL_TEXTURE_VERTEX l_FullVertex0(XMFLOAT3(-(float)l_Vertex0.mData[0], (float)l_Vertex0.mData[2], (float)l_Vertex0.mData[1]), XMFLOAT3(-(float)l_Normal0.mData[0], (float)l_Normal0.mData[2], (float)l_Normal0.mData[1]), XMFLOAT2((float)l_TexCoord0.mData[0], 1.0f - (float)l_TexCoord0.mData[1]));
		UOC_POSITION_NORMAL_TEXTURE_VERTEX l_FullVertex1(XMFLOAT3(-(float)l_Vertex1.mData[0], (float)l_Vertex1.mData[2], (float)l_Vertex1.mData[1]), XMFLOAT3(-(float)l_Normal1.mData[0], (float)l_Normal1.mData[2], (float)l_Normal1.mData[1]), XMFLOAT2((float)l_TexCoord1.mData[0], 1.0f - (float)l_TexCoord1.mData[1]));
		UOC_POSITION_NORMAL_TEXTURE_VERTEX l_FullVertex2(XMFLOAT3(-(float)l_Vertex2.mData[0], (float)l_Vertex2.mData[2], (float)l_Vertex2.mData[1]), XMFLOAT3(-(float)l_Normal2.mData[0], (float)l_Normal2.mData[2], (float)l_Normal2.mData[1]), XMFLOAT2((float)l_TexCoord2.mData[0], 1.0f - (float)l_TexCoord2.mData[1]));

		l_FullVertexs[l_MaterialId].push_back(l_FullVertex0);
		l_FullVertexs[l_MaterialId].push_back(l_FullVertex1);
		l_FullVertexs[l_MaterialId].push_back(l_FullVertex2);
		l_Indices[l_MaterialId].push_back((unsigned short)l_Indices[l_MaterialId].size());
		l_Indices[l_MaterialId].push_back((unsigned short)l_Indices[l_MaterialId].size());
		l_Indices[l_MaterialId].push_back((unsigned short)l_Indices[l_MaterialId].size());

		if (l_FullVertex0.Position.x < m_BBMin.x || i == 0)
			m_BBMin.x = l_FullVertex0.Position.x;
		if (l_FullVertex0.Position.y < m_BBMin.y || i == 0)
			m_BBMin.y = l_FullVertex0.Position.y;
		if (l_FullVertex0.Position.z < m_BBMin.z || i == 0)
			m_BBMin.z = l_FullVertex0.Position.z;

		if (l_FullVertex1.Position.x < m_BBMin.x)
			m_BBMin.x = l_FullVertex1.Position.x;
		if (l_FullVertex1.Position.y < m_BBMin.y)
			m_BBMin.y = l_FullVertex1.Position.y;
		if (l_FullVertex1.Position.z < m_BBMin.z)
			m_BBMin.z = l_FullVertex1.Position.z;

		if (l_FullVertex2.Position.x < m_BBMin.x)
			m_BBMin.x = l_FullVertex2.Position.x;
		if (l_FullVertex2.Position.y < m_BBMin.y)
			m_BBMin.y = l_FullVertex2.Position.y;
		if (l_FullVertex2.Position.z < m_BBMin.z)
			m_BBMin.z = l_FullVertex2.Position.z;

		if (l_FullVertex0.Position.x > m_BBMax.x || i == 0)
			m_BBMax.x = l_FullVertex0.Position.x;
		if (l_FullVertex0.Position.y > m_BBMax.y || i == 0)
			m_BBMax.y = l_FullVertex0.Position.y;
		if (l_FullVertex0.Position.z > m_BBMax.z || i == 0)
			m_BBMax.z = l_FullVertex0.Position.z;

		if (l_FullVertex1.Position.x > m_BBMax.x)
			m_BBMax.x = l_FullVertex1.Position.x;
		if (l_FullVertex1.Position.y > m_BBMax.y)
			m_BBMax.y = l_FullVertex1.Position.y;
		if (l_FullVertex1.Position.z > m_BBMax.z)
			m_BBMax.z = l_FullVertex1.Position.z;

		if (l_FullVertex2.Position.x > m_BBMax.x)
			m_BBMax.x = l_FullVertex2.Position.x;
		if (l_FullVertex2.Position.y > m_BBMax.y)
			m_BBMax.y = l_FullVertex2.Position.y;
		if (l_FullVertex2.Position.z > m_BBMax.z)
			m_BBMax.z = l_FullVertex2.Position.z;
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
	////TO DO : Recorrer el vector m_RenderableVertexs
	for (auto i = 0u; i < m_RenderableVertexs.size(); i++)
	{
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
