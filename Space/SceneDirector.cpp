#include "stdafx.h"
#include"Scene.h"
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

void SceneDirector::Update()
{
	Input::GetInst()->Update();
	ObjMgr->Update();

	if (m_CurrentScene)
		m_CurrentScene->Update();

}

void SceneDirector::Render()
{
	if (m_CurrentScene)
		m_CurrentScene->Render();
	ObjMgr->Render();

}
