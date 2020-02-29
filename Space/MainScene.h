#pragma once
class MainScene : public Scene
{
	Sprite* m_BG;

	TextMgr* m_Text;
public:
	MainScene();
	~MainScene();

	void Init();
	void Release();

	void Update(float deltaTime,float time);
	void Render();
};

