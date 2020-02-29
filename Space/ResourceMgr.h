#pragma once

class Texture;
class ResourceMgr : public Singleton<ResourceMgr>
{
private:
	std::map<std::wstring, Texture*> m_TextureMap;

public:
	ResourceMgr();
	~ResourceMgr();

	Texture* CreateTextureFromFile(std::wstring fileName);

};

