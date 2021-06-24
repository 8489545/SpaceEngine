#include "stdafx.h"
#include "Triangle.h"

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

bool Triangle::Init()
{
    Renderer::GetInst()->GetDevice()->CreateVertexBuffer(3 * sizeof(Vertex), D3DUSAGE_WRITEONLY, Vertex::FVF, D3DPOOL_MANAGED, &m_Triangle,0);


    Vertex* vertices;

    m_Triangle->Lock(0, 0, (void**)&vertices, 0);

    vertices[0] = Vertex(-1.f, 0.f, 2.f,D3DCOLOR_XRGB(255,0,0));
    vertices[1] = Vertex(0.f, 1.f, 2.f,D3DCOLOR_XRGB(0,255,0));
    vertices[2] = Vertex(1.f, 0.f, 2.f, D3DCOLOR_XRGB(0, 0, 255));
    
    m_Triangle->Unlock();

    Matrix proj;
    D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5, (float)App::GetInst()->m_Width / (float)App::GetInst()->m_Height, 1.f, 1000.f);
    Renderer::GetInst()->GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);
    Renderer::GetInst()->GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

    return true;
}

void Triangle::Release()
{
}

void Triangle::Render()
{

    Renderer::GetInst()->GetDevice()->SetStreamSource(0, m_Triangle, 0, sizeof(Vertex));
    Renderer::GetInst()->GetDevice()->SetFVF(Vertex::FVF);
    Renderer::GetInst()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
