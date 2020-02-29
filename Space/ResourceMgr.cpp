#include "stdafx.h"
#include "ResourceMgr.h"
#include"Texture.h"

ResourceMgr::ResourceMgr()
{
}


ResourceMgr::~ResourceMgr()
{
}

Texture* ResourceMgr::CreateTextureFromFile(std::wstring fileName)
{
	if (!(m_TextureMap.count(fileName)))
	{
		auto texture = new (std::nothrow) Texture();
		if (texture && texture->Init(fileName))
		{
			m_TextureMap[fileName] = texture;
		}
		else
		{
			SafeDelete(texture);
			return 0;
		}
	}

	return m_TextureMap[fileName];
}
