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
    //Projection(����) ��� ������ 3���� ������ �ִ� ��ǥ�� 2���� ��ǥ�� ��ȯ�� ������ش�.
    
    D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_VIEW, &matView);

    D3DXMatrixIdentity(&matWorld);
    //������ķ� ��ȯ
    //��������̶� �� �밢���� ���Ұ� ��� 1�̰� ������ ���Ҵ� 0�� ���簢����� ����


}

Camera::~Camera()
{
}
void Camera::Update()
{
    auto device = Renderer::GetInst()->GetDevice();

    //LookAtPt = EyePt + vLook;//������ �ٶ� ������ ����
    //�� �ڸ��� Ÿ���� ��ġ�� ������ ī�޶� �� Ÿ���� �ٶ�.

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

    //ī�޶��� ��ġ(eye) ���� ���� ���� ����(lookat)���� �̵��Ҷ�
    //���� ���� �������� ī�޶� ��ġ�� �� ���� �̵� ���Ͱ� �ȴ�.

    D3DXVec3Normalize(&view, &view);

    //view ����ȭ

    vEyePt += view * speed * dt;
    vLookatPt += view * speed * dt;

    //ī�޶� �̵� ����

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

    //�����Ϳ� ���� ������ ������ ���͸� ������ �ӵ��� ���ؼ� Ⱦ�̵��� ����;

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

    //���� ����(view)�� ������ �� �����͸� ���������� �¿�� ȸ���� ����� �����
    //�ٽ� ���ͷ� �ٲ��� �� ���͸� �ٽ� ���� eye�� �ٲ��ش�.

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

    //Crossȸ���� ������ �����Ϳ� �交���� ������ �Ǵ� ���� ���ؾ��ϹǷ� ������ ���� ���� ���Ѵ�.

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
