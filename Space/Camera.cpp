#include"stdafx.h"
#include "Camera.h"
Camera::Camera() :
    vEyePt(0.f, 0.f, 5.f)
    , vLookatPt(0.f, 0.f, 0.f)
    , vUpVec(0.f, 1.f, 0.f)
    , cameraSpeed(5)
    , cameraFreeView(true)
{
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, WINSIZEX / WINSIZEY, 1.f, 1000.f);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
    //Projection(투영) 행렬 가상의 3차원 공간에 있는 좌표를 2차원 좌표로 변환해 출력해준다.
    
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);

    D3DXMatrixIdentity(&matWorld);
    //단위행렬로 변환
    //단위행렬이란 주 대각선의 원소가 모두 1이고 나머지 원소는 0인 정사각행렬을 뜻함


}

Camera::~Camera()
{
}
void Camera::Update()
{
    auto device = Renderer::GetInst()->GetDevice();

    //LookAtPt = EyePt + vLook;//눈에서 바라볼 방향을 더함
    //이 자리에 타겟의 위치를 넣으면 카메라가 그 타겟을 바라봄.

    if (cameraFreeView)
    {
        Translate();

        if (INPUT->GetKey(VK_UP) == KeyState::PRESS)
        {
            RotationUp(D3DXToRadian(-30) * dt);
        }
        if (INPUT->GetKey(VK_DOWN) == KeyState::PRESS)
        {
            RotationUp(D3DXToRadian(30) * dt);
        }

        if (INPUT->GetKey(VK_LEFT) == KeyState::PRESS)
        {
            RotationCross(D3DXToRadian(30) * dt);
        }
        if (INPUT->GetKey(VK_RIGHT) == KeyState::PRESS)
        {
            RotationCross(D3DXToRadian(-30) * dt);
        }

        ShowCursor(false);
    }

    SetTransform();
}

void Camera::SetTransform()
{
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
}

void Camera::FrontTranslate(float speed)
{
    D3DXVECTOR3 view;
    view = vLookatPt - vEyePt;

    //카메라의 위치(eye) 에서 현재 보는 시점(lookat)으로 이동할때
    //현재 보는 시점에서 카메라 위치를 뺀 값이 이동 벡터가 된다.

    D3DXVec3Normalize(&view, &view);

    //view 정규화

    vEyePt += view * speed * dt;
    vLookatPt += view * speed * dt;

    //카메라 이동 적용

    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::SideTranslate(float speed)
{
    D3DXVECTOR3 view;
    D3DXVECTOR3 cross;
    view = vLookatPt - vEyePt;
    D3DXVec3Cross(&cross, &vUpVec, &view);
    D3DXVec3Normalize(&cross, &cross);
    D3DXVec3Normalize(&view, &view);

    //업벡터와 보는 방향의 직각인 벡터를 구한후 속도를 곱해서 횡이동을 수행;

    vEyePt += cross * speed * dt;
    vLookatPt += cross * speed * dt;

    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::RotationCross(float angle)
{
    D3DXVECTOR3 view;
    D3DXMATRIXA16 matRot;

    view = vLookatPt - vEyePt;

    D3DXMatrixRotationAxis(&matRot, &vUpVec, angle);
    D3DXVec3TransformCoord(&view, &view, &matRot);

    //보는 방향(view)을 구해준 후 업벡터를 기준축으로 좌우로 회전한 행렬을 만들고
    //다시 벡터로 바꿔준 후 벡터를 다시 기존 eye로 바꿔준다.

    vLookatPt = (vEyePt + view);

    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::RotationUp(float angle)
{
    D3DXVECTOR3 view;
    D3DXVECTOR3 cross;
    D3DXMATRIXA16 matRot;

    view = vLookatPt - vEyePt;

    D3DXVec3Cross(&cross, &vUpVec, &view);
    D3DXMatrixRotationAxis(&matRot, &cross, angle);
    D3DXVec3TransformCoord(&view, &view, &matRot);

    //Cross회전과 같지만 업벡터와 뷰벡터의 직각이 되는 축을 구해야하므로 외적을 통해 축을 구한다.

    vLookatPt = (vEyePt + view);

    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}

void Camera::Translate()
{
    if (INPUT->GetKey('W') == KeyState::PRESS)
    {
        FrontTranslate(cameraSpeed);
    }
    if (INPUT->GetKey('S') == KeyState::PRESS)
    {
        FrontTranslate(-cameraSpeed);
    }

    if (INPUT->GetKey('A') == KeyState::PRESS)
    {
        SideTranslate(-cameraSpeed);
    }
    if (INPUT->GetKey('D') == KeyState::PRESS)
    {
        SideTranslate(cameraSpeed);
    }
}
