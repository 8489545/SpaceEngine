#pragma once
class Scene;
class SceneDirector : public Singleton<SceneDirector>
{
	Scene* m_CurrentScene;

public:
	SceneDirector();
	~SceneDirector();

	void ChangeScene(Scene* newScene);

	void Update();
	void Render();

};

