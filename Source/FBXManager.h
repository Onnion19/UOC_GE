#ifndef _FBXMANAGER_H
#define _FBXMANAGER_H

#include <fbxsdk.h>
#include "defines.h"
#include <vector>
#include <memory>
#include <string_view>

#define FBXSDK_NEW_API

class CEffect;
class CFBXStaticMesh;

class CFBXManager final
{
private:
	static constexpr auto fbxManagerDtor = [](FbxManager* manager) {manager->Destroy(); };

	std::vector<std::unique_ptr<CFBXStaticMesh>>			m_StaticMeshes;
	std::unique_ptr<FbxManager, decltype(fbxManagerDtor)>	m_Manager;
	void ImportNode(FbxNode* Node);
public:
	CFBXManager();
	~CFBXManager();
	void Load(std::string_view Filename);
};

#endif
