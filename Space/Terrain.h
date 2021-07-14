#pragma once
class Terrain
{

    LPDIRECT3DTEXTURE9 m_pTexDiffuse;
    LPDIRECT3DTEXTURE9 m_pTexHeightMap;
    LPDIRECT3DDEVICE9 m_pDev;

    LPDIRECT3DVERTEXBUFFER9 m_pVB;
    LPDIRECT3DINDEXBUFFER9 m_pIB;

    D3DXMATRIXA16 matAni;

    DWORD cxHeight;
    DWORD czHegiht;
public:
    Terrain();
    ~Terrain();

    static Terrain* Create(std::wstring diffuse, std::wstring height);

    bool Init(std::wstring diffuse, std::wstring height);

    bool InitVB();
    bool InitIB();

    void SetUpLights();
    void Animate();

    void Release();

    void Update();
    void Render();
};

