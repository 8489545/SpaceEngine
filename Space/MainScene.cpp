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
    triangle.Init();
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{

}

void MainScene::Render()
{
    triangle.Render();
}
