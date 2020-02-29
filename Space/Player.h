#pragma once
class Player : public Object
{
	Sprite* m_Obj;
public:

	Player();
	~Player();

	void Update(float deltaTime,float Time);
	void Render();
};

