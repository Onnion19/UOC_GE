#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

#define MAXBONES 29

#include <D3D11.h>

#include <map>
#include <memory>
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
	virtual ~CEffect() = default;
	virtual bool Reload(ID3D11Device* Device) = 0;
	virtual bool Load(ID3D11Device* Device, const std::string& Filename, const std::string& PointEntryVS, const std::string& ShaderModelVS, const std::string& PointEntryPS, const std::string& ShaderModelPS) = 0;
	virtual ID3D11VertexShader* GetVertexShader() = 0;
	virtual ID3D11PixelShader* GetPixelShader() = 0;
	virtual ID3D11InputLayout* GetVertexLayout() = 0;
};

template <class T>
class CEffectTemplated : public CEffect
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	std::string m_Filename;
	std::string m_PointEntryVS;
	std::string m_ShaderModelVS;
	std::string m_PointEntryPS;
	std::string m_ShaderModelPS;

	bool LoadShader(const std::string& Filename, const std::string& EntryPoint, const std::string& ShaderModel, ID3DBlob** BlobOut);
public:
	CEffectTemplated() = default;
	virtual ~CEffectTemplated();
	void CleanUp();
	bool Reload(ID3D11Device* Device);
	bool Load(ID3D11Device* Device, const std::string& Filename, const std::string& PointEntryVS, const std::string& ShaderModelVS, const std::string& PointEntryPS, const std::string& ShaderModelPS) override;
	ID3D11VertexShader* GetVertexShader() override
	{
		return m_VertexShader;
	}
	ID3D11PixelShader* GetPixelShader() override
	{
		return m_PixelShader;
	}
	ID3D11InputLayout* GetVertexLayout() override
	{
		return m_VertexLayout;
	}
};

class CEffectManager final
{
private:
	std::map<unsigned int, std::unique_ptr<CEffect>> m_EffectsByVertexType;
	std::map<std::string, std::unique_ptr<CEffect>>	m_Effects;
	ID3D11Buffer* m_SceneConstantBuffer = nullptr;
	ID3D11Buffer* m_ObjectConstantBuffer = nullptr;
	ID3D11Buffer* m_AnimatedModelConstantBuffer = nullptr;

private:
	template<class T>
	void AddEffect(ID3D11Device* Device, const std::string& Name, const std::string& Filename, const std::string& PointEntryVS, const std::string& ShaderModelVS, const std::string& PointEntryPS, const std::string& ShaderModelPS);
	template<class T>
	void AddEffect(ID3D11Device* Device, const std::string& Filename, const std::string& PointEntryVS, const std::string& ShaderModelVS, const std::string& PointEntryPS, const std::string& ShaderModelPS);
	bool CreateConstantBuffer(ID3D11Device* Device, UINT ConstantBufferSize, ID3D11Buffer** ConstantBuffer);
	void SetConstantBuffer(ID3D11DeviceContext* DeviceContext, ID3D11Buffer* ConstantBuffer, void* Data, UINT IdSlot);

public:
	static CSceneConstantBufferParameters			m_SceneConstantBufferParameters;
	static CObjectConstantBufferParameters			m_ObjectConstantBufferParameters;
	static CAnimatedModelConstantBufferParameters	m_AnimatedModelConstantBufferParameters;

	CEffectManager();
	~CEffectManager();
	CEffect* GetEffect(unsigned int VertexType);
	CEffect* GetEffect(const std::string& Name);
	void SetSceneConstantBuffer(ID3D11DeviceContext* DeviceContext);
	void SetObjectConstantBuffer(ID3D11DeviceContext* DeviceContext);
	void SetAnimatedModelConstantBuffer(ID3D11DeviceContext* DeviceContext);
};


template<class T>
inline CEffectTemplated<T>::~CEffectTemplated()
{
	CleanUp();
}

template<class T>
void CEffectTemplated<T>::CleanUp()
{
	CHECKED_DELETE(m_VertexShader);
	CHECKED_DELETE(m_PixelShader);
	CHECKED_DELETE(m_VertexLayout);
}

template<class T>
bool CEffectTemplated<T>::Reload(ID3D11Device* Device)
{
	CleanUp();
	return Load(Device, m_Filename, m_PointEntryVS, m_ShaderModelVS, m_PointEntryPS, m_ShaderModelPS);
}

template<class T>
bool CEffectTemplated<T>::LoadShader(const std::string& Filename, const std::string& EntryPoint, const std::string& ShaderModel, ID3DBlob** BlobOut)
{
	//NOTA : El siguiente fragmento de código carga un shader de fichero utilizando la función de DirectX D3DX11CompileFromFile
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob = NULL;
	hr = D3DCompileFromFile(str2wstr(Filename).c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryPoint.c_str(), ShaderModel.c_str(), dwShaderFlags, 0, BlobOut, &pErrorBlob);

	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob)
			pErrorBlob->Release();
		return false;
	}
	if (pErrorBlob)
		pErrorBlob->Release();

	return true;
}

template<class T>
bool CEffectTemplated<T>::Load(ID3D11Device* Device, const std::string& Filename, const std::string& PointEntryVS, const std::string& ShaderModelVS, const std::string& PointEntryPS, const std::string& ShaderModelPS)
{
	m_Filename = Filename;
	m_PointEntryVS = PointEntryVS;
	m_ShaderModelVS = ShaderModelVS;
	m_PointEntryPS = PointEntryPS;
	m_ShaderModelPS = ShaderModelPS;

	ID3DBlob* l_VSBlob = NULL;
	//NOTA : El siguiente fragmento de código carga un shader llamando al método LoadShader para cargar el Vertex Shader
	bool l_Loaded = LoadShader(Filename, PointEntryVS, ShaderModelVS, &l_VSBlob);
	if (!l_Loaded)
		return false;
	//NOTA : El siguiente fragmento de código crea el vertex shader a partir de un fichero cargado previamente utilizando el método de DirectX CreateVertexShader
	HRESULT l_HR = Device->CreateVertexShader(l_VSBlob->GetBufferPointer(), l_VSBlob->GetBufferSize(), NULL, &m_VertexShader);
	if (FAILED(l_HR))
	{
		l_VSBlob->Release();
		return false;
	}
	//NOTA : El siguiente fragmento de código crea el layout del tipo de vértice que utiliza el Vertex Shader
	l_Loaded = T::CreateInputLayout(Device, l_VSBlob, &m_VertexLayout);

	l_VSBlob->Release();

	if (!l_Loaded)
		return false;

	ID3DBlob* l_PSBlob = NULL;
	//NOTA : El siguiente fragmento de código carga un  shader llamando el método LoadShader para cargar el Pixel Shader
	l_Loaded = LoadShader(Filename.c_str(), PointEntryPS.c_str(), ShaderModelPS.c_str(), &l_PSBlob);
	if (!l_Loaded)
		return false;

	//NOTA : El siguiente fragmento de código crea el pixel shader a partir de un fichero cargado previamente utilizando el método de DirectX CreatePixelShader
	l_HR = Device->CreatePixelShader(l_PSBlob->GetBufferPointer(), l_PSBlob->GetBufferSize(), NULL, &m_PixelShader);
	l_PSBlob->Release();

	return !FAILED(l_HR);
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device* Device, const std::string& Filename, const std::string& PointEntryVS, const std::string& ShaderModelVS, const std::string& PointEntryPS, const std::string& ShaderModelPS)
{

	auto type = T::GetVertexType();
	std::unique_ptr<CEffect> effect{ new CEffectTemplated<T>() };
	effect->Load(Device, Filename, PointEntryVS, ShaderModelVS, PointEntryPS, ShaderModelPS);
	m_EffectsByVertexType[type] = std::move(effect);
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device* Device, const std::string& Name, const std::string& Filename, const std::string& PointEntryVS, const std::string& ShaderModelVS, const std::string& PointEntryPS, const std::string& ShaderModelPS)
{
	std::unique_ptr<CEffect> effect{ new CEffectTemplated<T>() };
	effect->Load(Device, Filename, PointEntryVS, ShaderModelVS, PointEntryPS, ShaderModelPS);
	m_Effects[Name] = std::move(effect);
}

#endif
