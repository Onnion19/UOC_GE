#ifndef _RENDERABLE_OBJECT_H_
#define _RENDERABLE_OBJECT_H_

#include "defines.h"

class CRenderableObject
{
protected:
	XMFLOAT3					m_Position{ 0,0,0 };
	XMFLOAT3					m_Rotation{ 1,1,1 };
	XMFLOAT3					m_Scale{ 0,0,0 };
public:
	CRenderableObject() = default;
	virtual ~CRenderableObject() = default;
	virtual void Update(float ElapsedTime);
	virtual void Render(ID3D11DeviceContext* DeviceContext);
	virtual XMMATRIX GetTransform();

	void SetPosition(const XMFLOAT3& Position) { m_Position = Position; }
	void SetRotation(const XMFLOAT3& Rotation) { m_Rotation = Rotation; }
	void SetScale(const XMFLOAT3& Scale) { m_Scale = Scale; }
};

#endif
