#pragma once
class GameObject
{
public:
	LPDIRECT3DDEVICE9 device;
	GameObject* m_Parent;
	Transform* m_Transform;

public:
	bool m_Destroy;
	RECT m_Collision;

	bool m_Visible;

public:
	int m_Layer;
	std::string m_Tag;

public:
	GameObject();
	~GameObject();

public:
	virtual void Update();
	virtual void Render();
	virtual void OnCollision(GameObject* other);

public:
	void SetDestroy(bool destroy) { m_Destroy = destroy; }
	void SetTag(const std::string tag);
	void SetParent(GameObject* obj);
public:
	bool GetDestroy() { return m_Destroy; }
};