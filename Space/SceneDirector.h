#pragma once
class SceneDirector : public Singleton<SceneDirector>
{
	Scene* m_CurrentScene;

public:
	SceneDirector();
	~SceneDirector();

	void ChangeScene(Scene* newScene);

	void Update(float deltaTime, float time);
	void Render();

};

