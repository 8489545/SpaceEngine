#pragma once
class Scene
{
public:
	Scene();
	~Scene();

	virtual void Init();
	virtual void Release();
	virtual void Update(float delatTime, float Time);
	virtual void Render();
};

