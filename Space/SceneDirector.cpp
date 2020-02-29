#include "stdafx.h"
#include "SceneDirector.h"


SceneDirector::SceneDirector()
{
}


SceneDirector::~SceneDirector()
{
}

void SceneDirector::ChangeScene(Scene* newScene)
{
	if (m_CurrentScene)
	{
		m_CurrentScene->Release();
		SafeDelete(m_CurrentScene);
	}

	m_CurrentScene = newScene;
	m_CurrentScene->Init();
}

void SceneDirector::Update(float deltaTime, float time)
{
	Camera::GetInst()->Update(deltaTime, time);
	Input::GetInst()->Update();
	ObjMgr->Update(deltaTime, time);

	if (m_CurrentScene)
		m_CurrentScene->Update(deltaTime, time);

}

void SceneDirector::Render()
{
	if (m_CurrentScene)
		m_CurrentScene->Render();
	ObjMgr->Render();

}
