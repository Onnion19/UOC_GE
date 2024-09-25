#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

#define MAXBONES 29

#include <D3D11.h>

#include <map>
#include "defines.h"

class CSceneConstantBufferParameters
{
public:
	XMMATRIX				m_View;
	XMMATRIX				m_Projection;
	XMFLOAT4				m_CameraRightVector;
	XMFLOAT4				m_CameraUpVector;
};

class CObjectConstantBufferParameters
{
public:
	XMMATRIX				m_World;
	XMFLOAT4				m_BaseColor;
	XMFLOAT4				m_DebugRenderScale;
};

class CAnimatedModelConstantBufferParameters
{
public:
	XMMATRIX				m_Bones[MAXBONES];
};

class CEffect
{
public:
	virtual ~CEffect()
	{
	}
	virtual bool Reload(ID3D11Device *Device) = 0;
	virtual bool Load(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS) = 0;
	virtual ID3D11VertexShader * GetVertexShader() = 0;
	virtual ID3D11PixelShader * GetPixelShader() = 0;
	virtual ID3D11InputLayout * GetVertexLayout() = 0;
};

template <class T>
class CEffectTemplated : CEffect
{
private:
	ID3D11VertexShader *m_VertexShader;
	ID3D11PixelShader *m_PixelShader;
	ID3D11InputLayout *m_VertexLayout;
	std::string m_Filename;
	std::string m_PointEntryVS;
	std::string m_ShaderModelVS;
	std::string m_PointEntryPS;
	std::string m_ShaderModelPS;

	bool LoadShader(const std::string &Filename, const std::string &EntryPoint, const std::string &ShaderModel, ID3DBlob **BlobOut);
public:
	CEffectTemplated();
	virtual ~CEffectTemplated();
	void CleanUp();
	bool Reload(ID3D11Device *Device);
	bool Load(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS);
	ID3D11VertexShader * GetVertexShader()
	{
		return m_VertexShader;
	}
	ID3D11PixelShader * GetPixelShader() 
	{
		return m_PixelShader;
	}
	ID3D11InputLayout * GetVertexLayout()
	{
		return m_VertexLayout;
	}
	bool Reload();
};

class CEffectManager 
{
private:
	std::map<unsigned int, CEffect *>				m_EffectsByVertexType;
	std::map<std::string, CEffect *>				m_Effects;
	ID3D11Buffer 									*m_SceneConstantBuffer;
	ID3D11Buffer 									*m_ObjectConstantBuffer;
	ID3D11Buffer 									*m_AnimatedModelConstantBuffer;

	template<class T>
	void AddEffect(ID3D11Device *Device, const std::string &Name, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS);
	template<class T>
	void AddEffect(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS);
	bool CreateConstantBuffer(ID3D11Device *Device, UINT ConstantBufferSize, ID3D11Buffer **ConstantBuffer);
	void SetConstantBuffer(ID3D11DeviceContext *DeviceContext, ID3D11Buffer *ConstantBuffer, void *Data, UINT IdSlot);
public:
	static CSceneConstantBufferParameters			m_SceneConstantBufferParameters;
	static CObjectConstantBufferParameters			m_ObjectConstantBufferParameters;
	static CAnimatedModelConstantBufferParameters	m_AnimatedModelConstantBufferParameters;

	CEffectManager();
	virtual ~CEffectManager();
	CEffect * GetEffect(unsigned int VertexType);
	CEffect * GetEffect(const std::string &Name);
	void SetSceneConstantBuffer(ID3D11DeviceContext *DeviceContext);
	void SetObjectConstantBuffer(ID3D11DeviceContext *DeviceContext);
	void SetAnimatedModelConstantBuffer(ID3D11DeviceContext *DeviceContext);
};

#endif
