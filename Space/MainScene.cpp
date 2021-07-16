#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
    terrain = Terrain::Create(L"Painting/terrain.png", L"Painting/height.bmp");

    test = Sprite::Create(L"Painting/Test.png");
    test->SetPosition(100, 100);

    mainCamera = new Camera();

    triangle = new Triangle();
    triangle->Init();
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{
    mainCamera->Update();
}

void MainScene::Render()
{
    Renderer::GetInst()->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
    terrain->Render();
    triangle->Render();
    //test->Render();
}
