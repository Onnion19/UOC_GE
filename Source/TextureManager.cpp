#include "TextureManager.h"
#include <assert.h>
#include "defines.h"
#include "DDSTextureLoader11.h"


CTexture::~CTexture()
{
	CHECKED_DELETE(m_Texture);
	CHECKED_DELETE(m_SamplerState);
}

bool CTexture::Load(ID3D11Device* Device, const std::string& Filename)
{
	//INFO : Este método carga una textura de fichero Filename en la variable m_Texture 
	HRESULT l_HR = DirectX::CreateDDSTextureFromFile(Device, str2wstr(Filename.substr(0, Filename.length() - 4) + ".dds").c_str(), NULL, &m_Texture);
	//INFO : El siguiente fragmento de código construye una descripción del Sampler State 
	D3D11_SAMPLER_DESC l_SampDesc;
	ZeroMemory(&l_SampDesc, sizeof(l_SampDesc));
	l_SampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	l_SampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	l_SampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	l_SampDesc.MinLOD = 0;
	l_SampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	//INFO : La siguiente llamada crea el sampler state que utilizaremos después para poder pintar una malla de triángulos con texturas
	l_HR = Device->CreateSamplerState(&l_SampDesc, &m_SamplerState);
	return !FAILED(l_HR);
}

void CTexture::Activate(ID3D11DeviceContext* ImmediateContext, unsigned int StageId)
{
	assert(ImmediateContext);
	ImmediateContext->PSSetSamplers(StageId, 1, &m_SamplerState); //Not sure about this
	ImmediateContext->PSSetShaderResources(StageId, 1, &m_Texture); //Not sure about this neither

	//TO DO : Establecer el sampler state m_SamplerState en StageId utilizando el método PSSetSamplers de la instancia ImmediateContext
	//TO DO : Establecer el resource de textura m_Texture en StageId utilizando el método PSSetShaderResources de la instancia ImmediateContext
}


void CTextureManager::CleanUp()
{
	m_TextureMap.clear();
}

CTexture* CTextureManager::LoadTexture(ID3D11Device* Device, const std::string& Filename)
{
	auto iter = m_TextureMap.find(Filename);
	if (iter != m_TextureMap.end()) return iter->second.get();


	std::string name;
	GetFilename(Filename.c_str(), name);
	std::string texturePath{ PATH_TEXTURES };
	texturePath.append(name);


	auto tuple = m_TextureMap.emplace(texturePath, new CTexture());
	
	if (!tuple.second) return nullptr;

	CTexture* texture = tuple.first->second.get();
	texture->Load(Device, texturePath);
	return texture;
}
