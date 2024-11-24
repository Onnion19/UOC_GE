#include "EffectManager.h"
#include "VertexTypes.h"
#include "UOCEngine.h"
#include "RenderManager.h"
#include <d3d11shader.h>

CSceneConstantBufferParameters CEffectManager::m_SceneConstantBufferParameters;
CObjectConstantBufferParameters CEffectManager::m_ObjectConstantBufferParameters;
CAnimatedModelConstantBufferParameters CEffectManager::m_AnimatedModelConstantBufferParameters;

CEffectManager::~CEffectManager()
{
	//TO DO : Destruir la variable miembro m_SceneConstantBuffer utilizando la macro CHECKED_RELEASE
	//TO DO : Destruir la variable miembro m_ObjectConstantBuffer utilizando la macro CHECKED_RELEASE
	//TO DO : Destruir la variable miembro m_AnimatedModelConstantBuffer utilizando la macro CHECKED_RELEASE

	//TO DO : Eliminar todos los efectos que se encuentran en el mapa m_EffectsByVertexType utilizando la macro CHECKED_DELETE
	//TO DO : Eliminar todos los efectos que se encuentran en el mapa m_Effects utilizando la macro CHECKED_DELETE
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	//TO DO : Construir un objeto de tipo CEffectTemplated<T>()
	//TO DO : Cargar el efecto llamando al m�todo Load de la clase CEffect que hemos constru�do previamente
	//TO DO : Agregar en el mapa m_EffectsByVertexType seg�n la clave T::GetVertexType() el efecto constru�do previamente
}

template<class T>
void CEffectManager::AddEffect(ID3D11Device *Device, const std::string &Name, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	//TO DO : Construir un objeto de tipo CEffectTemplated<T>()
	//TO DO : Cargar el efecto llamando al m�todo Load de la clase CEffect que hemos constru�do previamente
	//TO DO : Agregar en el mapa m_Effects seg�n la clave Name el efecto constru�do previamente
}

CEffectManager::CEffectManager()
{
	//TO DO : A�adir un efecto utilizando el m�todo templatizado AddEffect<UOC_POSITION_COLOR_VERTEX> que encontramos en el fichero "./Data/Effects/DebugRender.fx" d�nde el punto de entrada del Vertex Shader es "VS", el Shader Model del Vertex Shader es "vs_4_0", el punto de entrada del Pixel Shader es "PS" y el Shader Model del Pixel Shader es "ps_4_0"
	//TO DO : A�adir un efecto utilizando el m�todo templatizado AddEffect<UOC_POSITION_TEXTURE_VERTEX> que encontramos en el fichero "./Data/Effects/UOC_POSITION_TEXTURE_VERTEXShader.fx" d�nde el punto de entrada del Vertex Shader es "VS", el Shader Model del Vertex Shader es "vs_4_0", el punto de entrada del Pixel Shader es "PS" y el Shader Model del Pixel Shader es "ps_4_0"
	//TO DO : A�adir un efecto utilizando el m�todo templatizado AddEffect<UOC_POSITION_NORMAL_TEXTURE_VERTEX> que encontramos en el fichero "./Data/Effects/UOC_POSITION_NORMAL_TEXTURE_VERTEXShader.fx" d�nde el punto de entrada del Vertex Shader es "VS", el Shader Model del Vertex Shader es "vs_4_0", el punto de entrada del Pixel Shader es "PS" y el Shader Model del Pixel Shader es "ps_4_0"
	//TO DO : A�adir un efecto utilizando el m�todo templatizado AddEffect<UOC_POSITION_COLOR_TEXTURE_VERTEX> que encontramos en el fichero "./Data/Effects/UOC_POSITION_COLOR_TEXTURE_VERTEXShader.fx" d�nde el punto de entrada del Vertex Shader es "VS", el Shader Model del Vertex Shader es "vs_4_0", el punto de entrada del Pixel Shader es "PS" y el Shader Model del Pixel Shader es "ps_4_0"
	//TO DO : Llamar al m�todo CreateConstantBuffer para crear el constant buffer que contiene la informaci�n de escena en la variable miembro m_SceneConstantBuffer
	//TO DO : Llamar al m�todo CreateConstantBuffer para crear el constant buffer que contiene la informaci�n de objeto en la variable miembro m_ObjectConstantBuffer
	//TO DO : Llamar al m�todo CreateConstantBuffer para crear el constant buffer que contiene la informaci�n de modelos animados en la variable miembro m_AnimatedModelConstantBuffer
}

bool CEffectManager::CreateConstantBuffer(ID3D11Device *Device, UINT ConstantBufferSize, ID3D11Buffer **ConstantBuffer)
{
	//NOTA : El siguiente fragmento de c�digo crea una descripci�n de buffer de DirectX para crearlo posteriormente utilizando el m�todo CreateBuffer
	D3D11_BUFFER_DESC l_BufferDescription;
	ZeroMemory(&l_BufferDescription, sizeof(l_BufferDescription));

	l_BufferDescription.Usage=D3D11_USAGE_DEFAULT;
	l_BufferDescription.ByteWidth=ConstantBufferSize;
	l_BufferDescription.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
	l_BufferDescription.CPUAccessFlags=0;
	if(FAILED(Device->CreateBuffer(&l_BufferDescription, NULL, ConstantBuffer)))
		return false;

	return true;
}

void CEffectManager::SetConstantBuffer(ID3D11DeviceContext *DeviceContext, ID3D11Buffer *ConstantBuffer, void *Data, UINT IdSlot)
{
	//TO DO : Establecemos la informaci�n del constant buffer de Data utilizando el m�todo de DirectX UpdateSubresource de DeviceContext 
	//TO DO : Establecer el constant buffer para que pueda ser utilizado por el Vertex Shader utilizando el m�todo de DirectX VSSetConstantBuffers de DeviceContext  en el slot IdSlot
	//TO DO : Establecer el constant buffer para que pueda ser utilizado por el Pixel Shader utilizando el m�todo de DirectX PSSetConstantBuffers de DeviceContext  en el slot IdSlot
}

void CEffectManager::SetSceneConstantBuffer(ID3D11DeviceContext *DeviceContext)
{
	//TO DO : Llamar al m�todo SetConstantBuffer para establecer las constantes de escena m_SceneConstantBufferParameters en el buffer m_SceneConstantBuffer en el slot 0
}

void CEffectManager::SetObjectConstantBuffer(ID3D11DeviceContext *DeviceContext)
{
	//TO DO : Llamar al m�todo SetConstantBuffer para establecer las constantes de objeto m_ObjectConstantBufferParameters en el buffer m_ObjectConstantBuffer en el slot 1
}

void CEffectManager::SetAnimatedModelConstantBuffer(ID3D11DeviceContext *DeviceContext)
{
	//TO DO : Llamar al m�todo SetConstantBuffer para establecer las constantes de modelos animados m_AnimatedModelConstantBufferParameters en el buffer m_AnimatedModelConstantBuffer en el slot 2
}

CEffect * CEffectManager::GetEffect(const std::string &Name)
{
	//TO DO : Buscar el efecto seg�n el Name en el mapa m_Effects, en caso de encontrarlo lo devolvemos, si no se encuentra devolvemos NULL
}

CEffect * CEffectManager::GetEffect(unsigned int VertexType)
{
	//TO DO : Buscar el efecto seg�n el VertexType en el mapa m_EffectsByVertexType, en caso de encontrarlo lo devolvemos, si no se encuentra devolvemos NULL
}

template<class T>
CEffectTemplated<T>::CEffectTemplated()
//TO DO : Inicializar la variable miembro m_VertexShader a NULL
//TO DO : Inicializar la variable miembro m_PixelShader a NULL
//TO DO : Inicializar la variable miembro m_VertexLayout a NULL
{
}

template<class T>
CEffectTemplated<T>::~CEffectTemplated()
{
	//TO DO : Llamar al m�todo CleanUp
}

template<class T>
void CEffectTemplated<T>::CleanUp()
{
	//TO DO : Destruir la variable miembro m_VertexShader utilizando la macro CHECKED_RELEASE
	//TO DO : Destruir la variable miembro m_PixelShader utilizando la macro CHECKED_RELEASE
	//TO DO : Destruir la variable miembro m_VertexLayout utilizando la macro CHECKED_RELEASE
}

template<class T>
bool CEffectTemplated<T>::Reload(ID3D11Device *Device)
{
	//TO DO : Llamar al m�todo CleanUp
	//TO DO : Devolver el resultado de la llamada al m�todo Load
}

template<class T>
bool CEffectTemplated<T>::LoadShader(const std::string &Filename, const std::string &EntryPoint, const std::string &ShaderModel, ID3DBlob **BlobOut)
{
	//NOTA : El siguiente fragmento de c�digo carga un shader de fichero utilizando la funci�n de DirectX D3DX11CompileFromFile
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob= NULL;
	hr = D3DCompileFromFile(str2wstr(Filename).c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryPoint.c_str(), ShaderModel.c_str(), 	dwShaderFlags, 0, BlobOut, &pErrorBlob);
	
	if(FAILED(hr))
	{
		if(pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if(pErrorBlob)
			pErrorBlob->Release();
		return false;
	}
	if(pErrorBlob)
		pErrorBlob->Release();

	return true;
}

template<class T>
bool CEffectTemplated<T>::Load(ID3D11Device *Device, const std::string &Filename, const std::string &PointEntryVS, const std::string &ShaderModelVS, const std::string &PointEntryPS, const std::string &ShaderModelPS)
{
	m_Filename=Filename;
	m_PointEntryVS=PointEntryVS;
	m_ShaderModelVS=ShaderModelVS;
	m_PointEntryPS=PointEntryPS;
	m_ShaderModelPS=ShaderModelPS;

	ID3DBlob *l_VSBlob=NULL;
	//NOTA : El siguiente fragmento de c�digo carga un shader llamando al m�todo LoadShader para cargar el Vertex Shader
	bool l_Loaded=LoadShader(Filename, PointEntryVS, ShaderModelVS, &l_VSBlob);
	if(!l_Loaded)
		return false;
	//NOTA : El siguiente fragmento de c�digo crea el vertex shader a partir de un fichero cargado previamente utilizando el m�todo de DirectX CreateVertexShader
	HRESULT l_HR=Device->CreateVertexShader(l_VSBlob->GetBufferPointer(), l_VSBlob->GetBufferSize(), NULL, &m_VertexShader);
	if(FAILED(l_HR))
	{
		l_VSBlob->Release();
		return false;
	}
	//NOTA : El siguiente fragmento de c�digo crea el layout del tipo de v�rtice que utiliza el Vertex Shader
	l_Loaded=T::CreateInputLayout(Device, l_VSBlob, &m_VertexLayout);

	l_VSBlob->Release();

	if(!l_Loaded)
		return false;

	ID3DBlob *l_PSBlob=NULL;
	//NOTA : El siguiente fragmento de c�digo carga un  shader llamando el m�todo LoadShader para cargar el Pixel Shader
	l_Loaded=LoadShader(Filename.c_str(), PointEntryPS.c_str(), ShaderModelPS.c_str(), &l_PSBlob);
	if(!l_Loaded)
		return false;

	//NOTA : El siguiente fragmento de c�digo crea el pixel shader a partir de un fichero cargado previamente utilizando el m�todo de DirectX CreatePixelShader
	l_HR=Device->CreatePixelShader(l_PSBlob->GetBufferPointer(), l_PSBlob->GetBufferSize(), NULL, &m_PixelShader);
	l_PSBlob->Release();

	return !FAILED(l_HR);
}
