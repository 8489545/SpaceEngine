#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain() : m_pDev(Renderer::GetInst()->GetDevice())
{
}

Terrain::~Terrain()
{
}

Terrain* Terrain::Create(std::wstring diffuse, std::wstring height)
{
    auto terrain = new (std::nothrow) Terrain();

    if (terrain && terrain->Init(diffuse,height))
    {
        return terrain;
    }
    else
    {
        SafeDelete(terrain);
        return nullptr;
    }
}

bool Terrain::Init(std::wstring diffuse, std::wstring height)
{
    if (FAILED(D3DXCreateTextureFromFile(m_pDev, diffuse.c_str(), &m_pTexDiffuse)))
    {
        MessageBox(NULL, L"Can't open the texture file.", L"Error", MB_OK);
        return false;
    }

    if (FAILED(D3DXCreateTextureFromFileEx(m_pDev, height.c_str(), D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0,
        D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &m_pTexHeightMap)))
    {
        MessageBox(NULL, L"Can't open the texture file.", L"Error", MB_OK);
        return false;
    }

    if (InitVB() && InitIB())
        return true;

    return false;
}

bool Terrain::InitVB()
{
    D3DSURFACE_DESC desc;
    D3DLOCKED_RECT d3drc;

    m_pTexHeightMap->GetLevelDesc(0, &desc);

    cxHeight = desc.Width;
    czHegiht = desc.Height;

    if (FAILED(m_pDev->CreateVertexBuffer(cxHeight * czHegiht * sizeof(TEXVERTEX), 0,
        TexVertexFVF, D3DPOOL_DEFAULT, &m_pVB, NULL)))
        return false;

    m_pTexHeightMap->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);

    void* pVertexBuffer = nullptr;
    if (FAILED(m_pVB->Lock(0, cxHeight * czHegiht * sizeof(TEXVERTEX), &pVertexBuffer, 0)))
        return false;

    TEXVERTEX v;
    TEXVERTEX* pV = (TEXVERTEX*)pVertexBuffer;

    for (DWORD z = 0; z < cxHeight; ++z)
    {
        for (DWORD x = 0; x < czHegiht; ++x)
        {
            v.p.x = (float)x - cxHeight / 2.f;
            v.p.y = ((float)(*((LPDWORD)d3drc.pBits + x + z * (d3drc.Pitch / 4)) & 0x000000ff)) / 10.f;
            v.p.z = -((float)z - czHegiht / 2.f);

            v.n.x = v.p.x;
            v.n.y = v.p.y;
            v.n.z = v.p.z;
            D3DXVec3Normalize(&v.n, &v.n);

            v.t.x = (float)x / (cxHeight - 1);
            v.t.y = (float)z / (czHegiht - 1);


            *pV++ = v;
        }
    } 

    m_pVB->Unlock();
    m_pTexHeightMap->UnlockRect(0);

    return true;
}

bool Terrain::InitIB()
{
    if(FAILED(m_pDev->CreateIndexBuffer((cxHeight - 1) * (czHegiht - 1) * 2 * sizeof(INDEX)
        ,0,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&m_pIB,NULL)))
        return false;

    INDEX i;
    INDEX* pI;

    if (FAILED(m_pIB->Lock(0, (cxHeight - 1) * (czHegiht - 1) * 2 * sizeof(INDEX), (void**)&pI, 0)))
        return false;

    for (DWORD z = 0; z < czHegiht - 1; z++)
    {
        for (DWORD x = 0; x < cxHeight - 1; x++)
        {
            i._0 = (z * cxHeight + x);
            i._1 = (z * cxHeight + x + 1);
            i._2 = ((z + 1) * cxHeight + x);

            *pI++ = i;

            i._0 = ((z + 1) * cxHeight + x);
            i._1 = (z * cxHeight + x + 1);
            i._2 = ((z + 1) * cxHeight + x + 1);

            *pI++ = i;
        }
    }
    m_pIB->Unlock();

    return true;
}

void Terrain::SetUpLights()
{
    D3DMATERIAL9 mtrl;
    ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
    mtrl.Diffuse.a = mtrl.Ambient.a = 1.f;
    mtrl.Diffuse.r = mtrl.Ambient.r = 1.f;
    mtrl.Diffuse.g = mtrl.Ambient.g = 1.f;
    mtrl.Diffuse.b = mtrl.Ambient.b = 1.f;
    m_pDev->SetMaterial(&mtrl);

    D3DXVECTOR3 vecDir;
    D3DLIGHT9 light;

    ZeroMemory(&light, sizeof(D3DLIGHT9));
    light.Type = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r = 1.f;
    light.Diffuse.g = 1.f;
    light.Diffuse.b = 0.f;
    vecDir = D3DXVECTOR3(1, 1, 1);

    D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);
    light.Range = 1000.f;
    m_pDev->SetLight(0, &light);
    m_pDev->LightEnable(0, true);
    m_pDev->SetRenderState(D3DRS_LIGHTING, true);

    m_pDev->SetRenderState(D3DRS_AMBIENT, 0x00909090);
}

void Terrain::Animate()
{
    static DWORD t = 0;
    static bool flag = false;

    DWORD d = GetTickCount64() % ((int)((D3DX_PI * 2) * 1000.f));

    //D3DXMatrixRotationY(&matAni, d / 1000.f);

    D3DXMatrixIdentity(&matAni);
    SetUpLights();
}

void Terrain::Release()
{
}

void Terrain::Update()
{
}

void Terrain::Render()
{
    Animate();

    m_pDev->SetTexture(0, m_pTexDiffuse);
    m_pDev->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    m_pDev->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);

    m_pDev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    m_pDev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    m_pDev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

    m_pDev->SetTransform(D3DTS_WORLD, &matAni);
    m_pDev->SetStreamSource(0, m_pVB, 0, sizeof(TEXVERTEX));
    m_pDev->SetFVF(TexVertexFVF);
    m_pDev->SetIndices(m_pIB);
    m_pDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, cxHeight * czHegiht, 0, (cxHeight - 1) * (czHegiht - 1) * 2);
}
