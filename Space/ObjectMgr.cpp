#include "stdafx.h"
#include "ObjectMgr.h"



ObjectMgr::ObjectMgr()
{
}

ObjectMgr::~ObjectMgr()
{
}

void ObjectMgr::Release()
{
	for (auto iter = m_Objects.begin(); iter != m_Objects.end(); iter++)
	{
		(*iter)->SetDestroy(true);
	}
}

void ObjectMgr::DeleteCheak()
{
	for (auto iter = m_Objects.begin(); iter != m_Objects.end();)
	{
		if ((*iter)->GetDestroy())
		{
			GameObject* temp = (*iter);
			iter = m_Objects.erase(iter);
			SafeDelete(temp);
		}
		else
		{
			++iter;
		}
	}
}
void ObjectMgr::CollisionCheak(GameObject* obj, const std::string tag)
{
	for (auto& iter : m_Objects)
	{
		if (iter->m_Tag == tag)
		{
			RECT rc;
			if (IntersectRect(&rc, &obj->m_Collision, &iter->m_Collision))
			{
				obj->OnCollision(iter);
				iter->OnCollision(obj);
			}
		}
	}
}

void ObjectMgr::DeleteObject(std::string tag)
{
	for (auto& iter : m_Objects)
	{
		if (iter->m_Tag == tag)
		{
			iter->SetDestroy(true);
		}
	}
}

void ObjectMgr::Update()
{
	DeleteCheak();
	for (const auto& iter : m_Objects)
	{
		(iter)->Update();
	}
}

void ObjectMgr::Render()
{
	m_Objects.sort(stLISTsort());

	for (const auto& iter : m_Objects)
	{
		(iter)->Render();
	}
}

void ObjectMgr::AddObject(GameObject* obj, const std::string tag)
{
	m_Objects.push_back(obj);
	obj->SetTag(tag);
}

void ObjectMgr::RemoveObject(GameObject* obj)
{
	if (obj)
		obj->SetDestroy(true);
}