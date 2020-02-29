#pragma once
class CollisionMgr : public Singleton<CollisionMgr>
{
public:
	CollisionMgr();
	~CollisionMgr();

	bool MouseWithBoxSize(Object* obj);
};

