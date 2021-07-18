#pragma once
#include <algorithm>

#define ObjMgr ObjectMgr::GetInst()
class ObjectMgr : public Singleton<ObjectMgr>
{
public:
	std::list<GameObject*> m_Objects;

	struct stLISTsort
	{
		bool operator() (const GameObject* pObject1, const GameObject* pObject2) const
		{
			if (pObject1->m_Layer < pObject2->m_Layer)
				return TRUE;

			return FALSE;
		}
	};

public:
	ObjectMgr();
	~ObjectMgr();

	void Release();
	void DeleteCheak();
	void Update();
	void Render();




public:
	void AddObject(GameObject* obj, const std::string tag);
	void RemoveObject(GameObject* obj);
	void CollisionCheak(GameObject* obj, const std::string tag);
	void DeleteObject(std::string tag);

};

