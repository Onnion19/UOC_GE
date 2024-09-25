#include "TextureManager.h"
#include <assert.h>
#include "defines.h"
#include "DDSTextureLoader11.h"

CTexture::CTexture()
//TO DO : Inicializar la variable miembro m_Texture a NULL
//TO DO : Inicializar la variable miembro m_SamplerState a NULL
{
}

CTexture::~CTexture()
{
	//TO DO : Destruir la variable miembro m_SamplerState utilizando la macro CHECKED_RELEASE
	//TO DO : Destruir la variable miembro m_Texture utilizando la macro CHECKED_RELEASE
}

bool CTexture::Load(ID3D11Device *Device, const std::string &Filename)
{
	//INFO : Este método carga una textura de fichero Filename en la variable m_Texture 
	HRESULT l_HR = DirectX::CreateDDSTextureFromFile(Device, str2wstr(Filename.substr(0, Filename.length() - 4) + ".dds").c_str(), NULL, &m_Texture);
	
	//INFO : El siguiente fragmento de código construye una descripción del Sampler State 
	D3D11_SAMPLER_DESC l_SampDesc;
	ZeroMemory(&l_SampDesc, sizeof(l_SampDesc));
	l_SampDesc.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	l_SampDesc.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.ComparisonFunc=D3D11_COMPARISON_NEVER;
	l_SampDesc.MinLOD=0;
	l_SampDesc.MaxLOD=D3D11_FLOAT32_MAX;
	//INFO : La siguiente llamada crea el sampler state que utilizaremos después para poder pintar una malla de triángulos con texturas
	l_HR=Device->CreateSamplerState(&l_SampDesc, &m_SamplerState);
	return !FAILED(l_HR);
}

void CTexture::Activate(ID3D11DeviceContext *ImmediateContext, unsigned int StageId)
{
	//TO DO : Establecer el sampler state m_SamplerState en StageId utilizando el método PSSetSamplers de la instancia ImmediateContext
	//TO DO : Establecer el resource de textura m_Texture en StageId utilizando el método PSSetShaderResources de la instancia ImmediateContext
}

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
	//TO DO : Llamar al métoco CleanUp
}

void CTextureManager::CleanUp()
{
	//TO DO : Recorrer el mapa m_TextureMap y eliminar todos los objetos second del mapa utilizando la macro CHECKED_DELETE
	//TO DO : Realizar un clear de la variable miembro m_TextureMap
}

CTexture *  CTextureManager::LoadTexture(ID3D11Device *Device, const std::string &Filename)
{
	CTexture * l_Texture=NULL;
	//TO DO : Si la textura por nombre Filename existe en el mapa m_TextureMap, asignamos el valor del mapa según Filename en l_Texture
	//TO DO : En caso contrario (TODO LOS TO DO DENTRO DEL ELSE)
		//TO DO: Extraemos el nombre del fichero sin path de Filename utilizando la función GetFilename
		//TO DO: Creamos un string con PATH_TEXTURES más el nombre del fichero sin path que hemos extraído en el TO DO anterior
		//TO DO: Construye una textura y asignarla a la variable l_Texture
		//TO DO: Llamar al método Load pasándole el nombre del fichero con path completo construído previamente
		//TO DO: Insertar en el mapa m_TextureMap según el nombre Filename la textura creada l_Texture
	return l_Texture;
}
