#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject() :
	m_Transform(new Transform())
	, m_Destroy(0)
	, m_Visible(true)
	, m_Layer(0)
	, m_Tag("UnNamed")
	, m_Parent(nullptr)
{
	device = Renderer::GetInst()->GetDevice();
}


GameObject::~GameObject()
{
}

void GameObject::SetTag(const std::string tag)
{
	m_Tag = tag;
}

void GameObject::SetParent(GameObject* obj)
{
	m_Parent = obj;
}

void GameObject::Update()
{
}

void GameObject::Render()
{
	m_Transform->SetTransform(Renderer::GetInst()->GetDevice());
}

void GameObject::OnCollision(GameObject* other)
{
}