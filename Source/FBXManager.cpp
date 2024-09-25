#include "FBXManager.h"
#include "defines.h"
#include <vector>
#include "RenderManager.h"
#include "FBXStaticMesh.h"
#include "RenderableObjectManager.h"
#include "RenderableObject.h"
#include "MeshInstance.h"
#include "UOCEngine.h"

CFBXManager::CFBXManager()
{
	//NOTA : Inicializamos el Manager del SDK de la librería FBXSDK
	m_Manager=FbxManager::Create();
	FbxIOSettings *l_IOSettings=FbxIOSettings::Create(m_Manager, IOSROOT);
	m_Manager->SetIOSettings(l_IOSettings);
}

CFBXManager::~CFBXManager()
{
	//TO DO : Destruir el m_Manager llamando al método Destroy si es diferente de NULL
	//TO DO : Destruir todos los elementos del vector m_StaticMeshes utilizando la macro CHECKED_DELETE
}

void CFBXManager::Load(const std::string &Filename)
{
	//NOTA : Creamos un importador para poder caragar un fichero FBX según el fichero Filename
	FbxImporter *l_FbxImporter;
	l_FbxImporter=FbxImporter::Create(m_Manager, Filename.c_str());
	l_FbxImporter->Initialize(Filename.c_str(), -1, m_Manager->GetIOSettings());
	//NOTA : Creamos una escena de tipo FbxScene y la importamos
	FbxScene *l_FbxScene=FbxScene::Create(m_Manager, "tempName");
	l_FbxImporter->Import(l_FbxScene);
	//NOTA : Una vez importada la escena FBX importamos el nodo Root utilizando el método ImportNode
	FbxNode *l_RootNode=l_FbxScene->GetRootNode();
	ImportNode(l_RootNode);
	//NOTA : Destruímos el importador de Fbx
	l_FbxImporter->Destroy();
}

void CFBXManager::ImportNode(FbxNode *Node)
{
	CRenderableObjectManager *l_RenderableObjectManager=CUOCEngine::GetEngine()->GetRenderableObjectManager();
	if(Node!=NULL)
	{
		//NOTA : Recorremos todos los hijos del nodo de tipo FbxNode
		for(int i=0; i<Node->GetChildCount(); ++i)
		{
			FbxNode *l_FbxNode=Node->GetChild(i);
			FbxMesh *l_FbxMesh=l_FbxNode->GetMesh();
			if(l_FbxMesh!=NULL)
			{
				CFBXStaticMesh *l_FBXStaticMesh=new CFBXStaticMesh();
				//NOTA : En caso de que tengamos malla FbxMesh en este FbxNode leemos creamos una malla de tipo CFBXStaticMesh a partir del FbxNode y de la FbxMesh
				l_FBXStaticMesh->Generate(l_FbxNode, l_FbxMesh);
				//NOTA : Añadimos la malla en el vector de mallas estáticas
				m_StaticMeshes.push_back(l_FBXStaticMesh);
				
				const char *l_Name=l_FbxMesh->GetName();
				
				//NOTA : Creamos un objecto renderizable de tipo CMeshInstance a partir de la CFBXStaticMesh				
				FbxDouble3 l_Position=l_FbxNode->LclTranslation.Get();
				FbxDouble3 l_Rotation=l_FbxNode->LclRotation.Get();
				FbxDouble3 l_Scale=l_FbxNode->LclScaling.Get();
				CRenderableObject *l_RenderableObject=new CMeshInstance(l_FBXStaticMesh);
				//NOTA : Leemos la posición, rotación y escala del FbxNode y la asignamos en el CMeshInstance
				l_RenderableObject->SetPosition(XMFLOAT3(-(float)l_Position[0], (float)l_Position[1], -(float)l_Position[2]));
				l_RenderableObject->SetRotation(XMFLOAT3(DEG2RAD((float)-l_Rotation[0]), DEG2RAD((float)l_Rotation[2]), DEG2RAD((float)l_Rotation[1])));
				l_RenderableObject->SetScale(XMFLOAT3((float)l_Scale[0], (float)l_Scale[1], (float)l_Scale[2]));
				//NOTA : Añadir el objeto renderizable CMeshInstance
				l_RenderableObjectManager->AddRenderableObject(l_RenderableObject);
			}
			//NOTA : Llamamos al método ImportNode de forma recursiva para importar los hijos de nuestros hijos
			ImportNode(l_FbxNode);
		}
	}
}
