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
    subCamera = new Camera();

    Cameras[0] = mainCamera;
    Cameras[1] = subCamera;

    nowCameraIndex = 0;

    triangle = new Triangle();
    triangle->Init();

    cube = new Cube();
    cube->Init();
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{
    if (INPUT->GetKey('1') == KeyState::DOWN)
        nowCameraIndex = 0;
    else if (INPUT->GetKey('2') == KeyState::DOWN)
        nowCameraIndex = 1;

    Cameras[nowCameraIndex]->Update();
}

void MainScene::Render()
{
    //terrain->Render();
    cube->Render();
    triangle->Render();
    //test->Render();
}
