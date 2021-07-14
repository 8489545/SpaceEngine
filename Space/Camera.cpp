#include"stdafx.h"
#include "Camera.h"
Camera::Camera() :
    vEyePt(0.f, 100.f, -256.f)
    , rotation(0.f, 0.f)
    , vLookatPt(0.f, 0.f, 0.f)
    , vRightVec(0.f, 0.f, 0.f)
    , vUpVec(0.f, 1.f, 0.f)
    , cameraFreeView(true)
{
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.f, 1.f, 1000.f);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);

    D3DXMatrixIdentity(&matWorld);
}

Camera::~Camera()
{
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

    vLookatPt = vEyePt + vLook;

    vLook *= 0.5f;
    vRightVec *= 0.5f;

    if (INPUT->GetKey('W') == KeyState::PRESS)
    {
        vEyePt += vLook;
        vLookatPt += vLook;
    }
    if (INPUT->GetKey('S') == KeyState::PRESS)
    {
        vEyePt -= vLook;
        vLookatPt -= vLook;
    }

    SetTransform();
}

void Camera::SetTransform()
{
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);

    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);
}
