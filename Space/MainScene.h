#pragma once
class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	Triangle triangle;

	void Init();
	void Release();

	void Update(float deltaTime,float time);
	void Render();
};

