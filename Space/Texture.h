#pragma once
class Texture
{
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DDEVICE9 m_pDev;
	Vec2 m_Size;

public:
	Texture();
	~Texture();

public:
	bool Init(std::wstring fileName);

public:
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTexture; }
	Vec2 GetSize() { return m_Size; }
};

