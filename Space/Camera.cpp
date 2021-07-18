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
    //Projection(����) ��� ������ 3���� ������ �ִ� ��ǥ�� 2���� ��ǥ�� ��ȯ�� ������ش�.

    D3DXMatrixIdentity(&matWorld);
    //������ķ� ��ȯ
    //��������̶� �� �밢���� ���Ұ� ��� 1�̰� ������ ���Ҵ� 0�� ���簢����� ����
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

    //D3DXVec3TransformNormal(&vLook, &D3DXVECTOR3(0,0,1), &matRot); //ȸ���� ���� ������ vLook�� ����
    //D3DXVec3TransformNormal -> �� �Լ��� 3���� ���Ϳ� ����� ���̰� ���� ��ȯ�� (�̵� , ũ�� , ȸ��)�� ������ �� ����.
    //vLook �� ������ �ǹ��ϰ� �ȴ�.
    //D3DXVec3TransformCoord -> �� �Լ��� 3���� ���Ϳ� ����� ���ε� 3���� ���͸� 4���� ���ͷ� �ٲ� �� �������� 1 �� �� �̵��� ���� ��Ŵ
    //vLook �� ��ǥ ������ �ȴ�.

    //LookAtPt = EyePt + vLook;//������ �ٶ� ������ ����
    //�� �ڸ��� Ÿ���� ��ġ�� ������ ī�޶� �� Ÿ���� �ٶ�.

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
