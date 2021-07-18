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

    mainCamera = new Camera();
    subCamera = new Camera();

    Cameras[0] = mainCamera;
    Cameras[1] = subCamera;

    nowCameraIndex = 0;

    triangle = new Triangle();
    triangle->Init();

    cube = new Cube();
    cube->Init();

    box = new Box();
}

void MainScene::Release()
{
}

void MainScene::Update()
{
    if (INPUT->GetKey('1') == KeyState::DOWN)
        nowCameraIndex = 0;
    else if (INPUT->GetKey('2') == KeyState::DOWN)
        nowCameraIndex = 1;

    Cameras[nowCameraIndex]->Update();
}

void MainScene::Render()
{
    box->Render();
}
