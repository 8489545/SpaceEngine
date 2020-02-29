#pragma once
class Animation : public Object
{
private:
	std::vector<Sprite*> m_Anim;

	int m_Delay;
	bool m_AutoPlay;
	int m_FrameCount;

public:
	int m_CurrentFrame;
	Vec2 m_AniSize;
	int A, R, G, B;

public:
	Animation();
	~Animation();

	void SetFrame(int frame) { m_CurrentFrame = frame; }
	void AddFrame(std::wstring fileName);
	void AddContinueFrame(std::wstring fileName, int firstFrame, int lastFrame);

	void Init(int delay, bool play);
	void Update(float deltaTime, float time);
	void Render();
};

