#include "stdafx.h"
#include "MainScene.h"
#include"Player.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	m_BG = Sprite::Create(L"Painting/BG.png");
	m_BG->SetPosition(1920 / 2, 1080 / 2);

	ObjMgr->AddObject(new Player(), "Player");

	m_Text = new TextMgr();
	m_Text->Init(32, true, false, "Arial");
	m_Text->SetColor(255, 255, 255, 255);

	SoundMgr::GetInst()->Play(L"Test.wav", true);
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{
}

void MainScene::Render()
{
	m_BG->Render();

	Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	m_Text->print(std::to_string(INPUT->GetMousePos().x) + " " + std::to_string(INPUT->GetMousePos().y) + " \n" +
		std::to_string(dt) + " " +std::to_string(gt) , 0, 0);
	Renderer::GetInst()->GetSprite()->End();
}
