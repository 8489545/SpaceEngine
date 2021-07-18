#include "stdafx.h"
#include "Transform.h"

Transform::Transform() :
    m_Parent(nullptr)
    , m_Position(0,0,0)
    , m_Scale(1,1,1)
    , m_Rotation(0,0,0)
{
}

Transform::~Transform()
{
}

void Transform::SetTransform(LPDIRECT3DDEVICE9 device)
{
    D3DXMatrixScaling(&matScale, m_Scale.x, m_Scale.y, m_Scale.z);

    device->SetTransform(D3DTS_WORLD, &matScale);
}
