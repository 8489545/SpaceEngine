#pragma once
class Box : public GameObject
{
    LPD3DXMESH m_mesh;

    Transform* m_BoxTransform;
public:
    Box();
    ~Box();

    void Update();
    void Render();
};

