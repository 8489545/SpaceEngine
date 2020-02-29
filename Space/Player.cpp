#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_Obj = Sprite::Create(L"Painting/Player.png");
	m_Obj->SetParent(this);

	SetPosition(100, 100);
}

Player::~Player()
{
}

void Player::Update(float deltaTime, float Time)
{
	if (INPUT->GetKey('W') == KeyState::PRESS)
		m_Position.y -= 300 * dt;
	if (INPUT->GetKey('A') == KeyState::PRESS)
		m_Position.x -= 300 * dt;
	if (INPUT->GetKey('S') == KeyState::PRESS)
		m_Position.y += 300 * dt;
	if (INPUT->GetKey('D') == KeyState::PRESS)
		m_Position.x += 300 * dt;

	if (INPUT->GetKey(VK_SPACE) == KeyState::PRESS)
		Camera::GetInst()->Follow(this);
	else
		Camera::GetInst()->Follow(nullptr);
}

void Player::Render()
{
	m_Obj->Render();
}
