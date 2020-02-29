#pragma once
enum class KeyState
{
	DOWN,
	UP,
	PRESS,
	NONE
};
#define INPUT Input::GetInst()
class Input : public Singleton<Input>
{
	int m_CurrentState[256];
	int m_PrevState[256];
	bool m_bCurrentState;
	bool m_bPrevState;

	Vec2 m_MousePosition;

	bool m_ButtonDown;
	bool m_RightButtonDown;

public:
	Input();
	~Input();

	void Update();
	void ButtonDown(bool down);
	void RightButtonDown(bool down);

	KeyState GetKey(int key);
	Vec2 GetMousePos() { return m_MousePosition; }

	bool GetButtonDown() { return m_ButtonDown; }
	bool GetRightButtonDown() { return m_RightButtonDown; }

private:
	void KeyBoardUpdate();
	void MouseUpdate();
};

