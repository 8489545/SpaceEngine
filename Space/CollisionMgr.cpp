#include "stdafx.h"
#include "CollisionMgr.h"


CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}

bool CollisionMgr::MouseWithBoxSize(Object* obj)
{
	Vec2 Mouse = INPUT->GetMousePos();
	if (Mouse.x > obj->m_Position.x - obj->m_Size.x
		&& Mouse.x < obj->m_Position.x + obj->m_Size.x / 2
		&& Mouse.y > obj->m_Position.y - obj->m_Size.y
		&& Mouse.y < obj->m_Position.y + obj->m_Size.y / 2)
	{
		return true;
	}

	return false;
}