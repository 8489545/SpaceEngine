#pragma once
class GameObject;
class Transform
{
public:
    GameObject* m_Parent;

    D3DXVECTOR3 m_Position;
    D3DXVECTOR3 m_Rotation;
    D3DXVECTOR3 m_Scale;

    Matrix matScale;

public:
    Transform();
    ~Transform();

public:
    void SetTransform(LPDIRECT3DDEVICE9 device);
};

