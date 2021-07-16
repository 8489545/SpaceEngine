#pragma once
class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	Triangle* triangle;
	Terrain* terrain;

	Sprite* test;
	
	Camera* mainCamera;
	

	void Init();
	void Release();

	void Update(float deltaTime,float time);
	void Render();
};

