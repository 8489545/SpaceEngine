#include"stdafx.h"
#include "Camera.h"
Camera::Camera() :
    vEyePt(0.f, 3.f, -5.f)
    , rotation(0.f, 0.f)
    , vLookatPt(0.f, 0.f, 0.f)
    , vRightVec(0.f, 0.f, 0.f)
    , vUpVec(0.f, 1.f, 0.f)
    , cameraFreeView(true)
    , onClick(false)
    , cameraSpeed(30)
{
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.f, 1.f, 1000.f);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
    //Projection(투영) 행렬 가상의 3차원 공간에 있는 좌표를 2차원 좌표로 변환해 출력해준다.

    D3DXMatrixIdentity(&matWorld);
    //단위행렬로 변환
    //단위행렬이란 주 대각선의 원소가 모두 1이고 나머지 원소는 0인 정사각행렬을 뜻함
}

Camera::~Camera()
{
}

void Camera::Rotate()
{
    if (INPUT->GetMousePos().x - 50 > mousePos.x)
    {
        rotation.x += 1 * dt;
    }
    if (INPUT->GetMousePos().x + 50 < mousePos.x)
    {
        rotation.x -= 1 * dt;
    }
    if (INPUT->GetMousePos().y - 50 > mousePos.y)
    {
        rotation.y += 1 * dt;
    }
    if (INPUT->GetMousePos().y + 50 < mousePos.y)
    {
        rotation.y -= 1 * dt;
    }
}
void Camera::Update()
{
    auto device = Renderer::GetInst()->GetDevice();
    
    D3DXMATRIXA16 matRot;
    D3DXMATRIXA16 matRotX;
    D3DXMATRIXA16 matRotY;

    D3DXVECTOR3 vLook;

    D3DXMatrixRotationY(&matRotX, rotation.x);
    D3DXMatrixRotationX(&matRotY, rotation.y);

    matRot = matRotY * matRotX;

    D3DXVECTOR3 fy(0, 0, 1);
    D3DXVec3TransformNormal(&vLook, &fy, &matRot);
    D3DXVec3Cross(&vRightVec, &vUpVec, &vLookatPt);
    D3DXVec3Normalize(&vRightVec, &vRightVec);

    //D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0,0,1), &matRot); //회전한 곳의 방향을 vLook에 넣음
    //D3DXVec3TransformNormal -> 이 함수는 3차원 벡터와 행렬의 곱이고 여러 변환들 (이동 , 크기 , 회전)을 적용할 때 쓰임.
    //vLook 은 방향을 의미하게 된다.
    //D3DXVec3TransformCoord -> 이 함수도 3차원 벡터와 행렬의 곱인데 3차원 벡터를 4차원 벡터로 바꿀 때 마지막을 1 로 해 이동을 적용 시킴
    //vLook 은 좌표 개념이 된다.

    //LookAtPt = EyePt + vLook;//눈에서 바라볼 방향을 더함
    //이 자리에 타겟의 위치를 넣으면 카메라가 그 타겟을 바라봄.

    vLookatPt = vEyePt + vLook;

    vLook *= 0.5f;
    vRightVec *= 0.5f;

    if (INPUT->GetKey('W') == KeyState::PRESS)
    {
        vEyePt += vLook * cameraSpeed * dt;
        vLookatPt += vLook * cameraSpeed * dt;
    }
    if (INPUT->GetKey('S') == KeyState::PRESS)
    {
        vEyePt -= vLook * cameraSpeed * dt;
        vLookatPt -= vLook * cameraSpeed * dt;
    }
    if (INPUT->GetKey('A') == KeyState::PRESS)
    {
        vEyePt += vRightVec * cameraSpeed * dt;
        vLookatPt += vRightVec * cameraSpeed * dt;
    }
    if (INPUT->GetKey('D') == KeyState::PRESS)
    {
        vEyePt -= vRightVec * cameraSpeed * dt;
        vLookatPt -= vRightVec * cameraSpeed * dt;
    }

    if (INPUT->GetButtonDown())
    {
        if (!onClick)
        {
            mousePos = INPUT->GetMousePos();
        }
        onClick = true;
        Rotate();
    }
    else
    {
        onClick = false;
    }

    SetTransform();
}

void Camera::SetTransform()
{
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}
