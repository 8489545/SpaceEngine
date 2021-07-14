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
    terrain = Terrain::Create(L"Painting/terrain.png", L"Painting/mountains.bmp");

    mainCamera = new Camera();

    //triangle = new Triangle();
    //triangle->Init();
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
    terrain->Render();
    //triangle->Render();
}
