#pragma once
class EffectMgr : public Object
{
	Animation* Effect;
public:
	EffectMgr(std::wstring filename, int start, int end, int speed, Vec2 Pos);
	~EffectMgr();

	int Start;
	int End;

	void Update(float deltaTime, float time);
	void Render();
	void OnCollision(Object* other);
};

