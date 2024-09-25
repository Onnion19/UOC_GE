#ifndef _MESH_INSTANCE_H_
#define _MESH_INSTANCE_H_

#include "RenderableObject.h"

class CFBXStaticMesh;

class CMeshInstance : public CRenderableObject
{
private:
	CFBXStaticMesh					*m_StaticMesh;
public:
	CMeshInstance(CFBXStaticMesh *StaticMesh);
	virtual ~CMeshInstance();
	void Render(ID3D11DeviceContext *DeviceContext);

};

#endif
