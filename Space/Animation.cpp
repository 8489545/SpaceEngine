#include "stdafx.h"
#include"Sprite.h"
#include"GameObject.h"
#include "Animation.h"
#include"App.h"

Animation::Animation()
	: m_AutoPlay(0)
	, m_CurrentFrame(0)
	, m_Delay(0.f)
	, m_FrameCount(0.f)
	, A(255)
	, R(255)
	, G(255)
	, B(255)
{
}

Animation::~Animation()
{
}

void Animation::AddContinueFrame(std::wstring fileName, int firstFrame, int lastFrame)
{
	if (firstFrame < lastFrame)
	{
		for (int i = firstFrame; i <= lastFrame; i++)
		{
			auto sprite = Sprite::Create(fileName.c_str() + std::to_wstring(i) + L".png");

			sprite->SetParent(this);
			if (sprite)
				m_Anim.push_back(sprite);
		}
	}
}
void Animation::Init(float delay, bool play)
{
	m_Delay = delay;
	m_AutoPlay = play;
}

void Animation::Update(float deltaTime, float time)
{
	m_FrameCount += dt;

	if (m_Destroy)
	{
		m_Anim.at(m_CurrentFrame)->SetDestroy(true);
	}

	if (m_AutoPlay == true)
	{
		if (m_FrameCount > m_Delay)
		{
			m_CurrentFrame++;
			m_FrameCount = 0.f;
		}
	}

	if (m_CurrentFrame > m_Anim.size() - 1)
	{
		m_CurrentFrame = 0;
	}
	m_Anim.at(m_CurrentFrame)->A = A;
	m_Anim.at(m_CurrentFrame)->R = R;
	m_Anim.at(m_CurrentFrame)->G = G;
	m_Anim.at(m_CurrentFrame)->B = B;

	m_Anim.at(m_CurrentFrame)->Update();

}

void Animation::Render()
{

	m_Anim.at(m_CurrentFrame)->Render();
}