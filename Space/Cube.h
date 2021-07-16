#pragma once
class Cube
{
    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    LPDIRECT3DINDEXBUFFER9 m_pIB;
public:
    Cube();
    ~Cube();

    bool Init();
    void Release();

private:
    bool InitVB();
    bool InitIB();

public:
    void Render();
};

