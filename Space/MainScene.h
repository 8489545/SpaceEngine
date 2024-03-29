#pragma once
class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	Triangle* triangle;
	Terrain* terrain;
	Cube* cube;

	Box* box;
	
	Camera* mainCamera;
	Camera* subCamera;

	Camera* Cameras[2];

	int nowCameraIndex;
	

	void Init();
	void Release();

	void Update();
	void Render();
};

