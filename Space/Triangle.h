#pragma once
class Triangle
{
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
public:
    Triangle();
    ~Triangle();

    bool Init();
    void Release();


    void Update();
    void Render();
};

