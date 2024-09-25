#ifndef _FBXMANAGER_H
#define _FBXMANAGER_H

#include <fbxsdk.h>
#include <string>
#include "defines.h"
#include <vector>

#define FBXSDK_NEW_API

class CEffect;
class CFBXStaticMesh;

class CFBXManager
{
private:
	std::vector<CFBXStaticMesh *>				m_StaticMeshes;
	FbxManager				*m_Manager;
	void ImportNode(FbxNode *Node);
public:
	CFBXManager();
	virtual ~CFBXManager();
	void Load(const std::string &Filename);
};

#endif
