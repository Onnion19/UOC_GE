#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <D3D11.h>

#include <unordered_map>
#include <memory>
#include <string>

class CTexture final
{
public:
	ID3D11ShaderResourceView* m_Texture = nullptr;
	ID3D11SamplerState* m_SamplerState = nullptr;
	CTexture() = default;
	~CTexture();
	bool Load(ID3D11Device* Device, const std::string& Filename);
	void Activate(ID3D11DeviceContext* ImmediateContext, unsigned int StageId);
};

class CTextureManager
{
private:
	using TTextureIterator = std::unordered_map<std::string, CTexture*>::iterator;
	using TConstTextureIterator = std::unordered_map<std::string, CTexture*>::const_iterator;

	std::unordered_map<std::string, std::unique_ptr<CTexture>>	m_TextureMap;

	void CleanUp();
public:
	CTextureManager() = default;
	~CTextureManager() = default;
	CTexture* LoadTexture(ID3D11Device* Device, const std::string& Filename);
};

#endif
