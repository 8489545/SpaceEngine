#include "stdafx.h"
#include "Transform.h"

Transform::Transform() :
    m_Parent(nullptr)
    , m_Position(0,0,0)
    , m_Scale(1,1,1)
    , m_Rotation(0,0,0)
{
    D3DXMatrixIdentity(&matTranslate);
}

Transform::~Transform()
{
}

void Transform::SetTransform(LPDIRECT3DDEVICE9 device)
{
    D3DXMatrixScaling(&matScale, m_Scale.x, m_Scale.y, m_Scale.z);
    D3DXMatrixRotationYawPitchRoll(&matRotation, 
        D3DXToRadian(m_Rotation.y), D3DXToRadian(m_Rotation.x), D3DXToRadian(m_Rotation.z));
    D3DXMatrixTranslation(&matTranslate, m_Position.x, m_Position.y, m_Position.z);

    matWorld = matScale * matRotation * matTranslate;

    device->SetTransform(D3DTS_WORLD, &matWorld);
    //S.R.T scale rotation transform
}
