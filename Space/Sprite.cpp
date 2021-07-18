#include"stdafx.h"
#include"Sprite.h"
#include"Texture.h"
#include"ResourceMgr.h"
#include"Camera.h"

Sprite::Sprite()
	: m_pSp(Renderer::GetInst()->GetSprite())
{
	m_pSp->AddRef();
	SetRect(&m_Rect, 0, 0, 0, 0);
	A = 255;
	R = 255;
	G = 255;
	B = 255;
}

Sprite::~Sprite()
{
}

bool Sprite::Init(std::wstring fileName)
{
	m_Texture = ResourceMgr::GetInst()->CreateTextureFromFile(fileName);
	if (m_Texture)
	{
		return true;
	}
	else
		return false;
}

Sprite* Sprite::Create(std::wstring fileName)
{
	auto sprite = new (std::nothrow) Sprite();
	if (sprite && sprite->Init(fileName))
	{
		return sprite;
	}
	else
	{
		SafeDelete(sprite);
		return nullptr;
	}
}



void Sprite::Render()
{
	m_pSp->Begin(D3DXSPRITE_ALPHABLEND);


	if (m_Visible == false)
		m_pSp->Draw(m_Texture->GetTexture(), &m_Rect, 0, 0, D3DCOLOR_ARGB(0, R, G, B));
	else
		m_pSp->Draw(m_Texture->GetTexture(), &m_Rect, 0, 0, D3DCOLOR_ARGB(A, R, G, B));

	m_pSp->End();
}