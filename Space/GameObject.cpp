
#include "stdafx.h"
#include "GameObject.h"


GameObject::GameObject() :
	 m_Position(0.f, 0.f)
	, m_Rotation(0.f)
	, m_Scale(1.f, 1.f)
	, m_Destroy(0)
	, m_Visible(true)
	, m_Layer(0)
	, m_Tag("UnNamed")
	, m_RotationCenter(0.f, 0.f)
	, m_Parent(nullptr)
	, m_Radius(0.f)
{
	D3DXMatrixIdentity(&m_wMat);
}


GameObject::~GameObject()
{
}

Matrix GameObject::GetMatrix()
{
	D3DXMatrixTransformation2D(&m_wMat, 0, 0, &m_Scale, &m_RotationCenter, m_Rotation, &m_Position);

	if (m_Parent)
		m_wMat *= m_Parent->GetMatrix();

	return m_wMat;
}

void GameObject::Translate(float x, float y)
{
	m_Position.x += x;
	m_Position.y += y;
}

void GameObject::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void GameObject::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void GameObject::Rotate(float r)
{
	m_Rotation += r;
}

void GameObject::SetTag(const std::string tag)
{
	m_Tag = tag;
}

void GameObject::SetParent(GameObject* obj)
{
	m_Parent = obj;
}

void GameObject::Update(float deltaTime, float time)
{
}

void GameObject::Render()
{
}

void GameObject::OnCollision(GameObject* other)
{
}