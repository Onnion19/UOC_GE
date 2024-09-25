#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <D3D11.h>

#include <map>
#include <string>

class CTexture 
{
public:
	ID3D11ShaderResourceView		*m_Texture;
	ID3D11SamplerState				*m_SamplerState;
	CTexture();
	virtual ~CTexture();
	bool Load(ID3D11Device *Device, const std::string &Filename);
	void Activate(ID3D11DeviceContext *ImmediateContext, unsigned int StageId);
};

class CTextureManager
{
private:
	typedef std::map<std::string, CTexture*>::iterator		TTextureIterator;
	std::map<std::string, CTexture*>						m_TextureMap;
	
	void CleanUp();
public:
	CTextureManager();
	virtual ~CTextureManager();
	CTexture * LoadTexture(ID3D11Device *Device, const std::string &Filename);
};

#endif
