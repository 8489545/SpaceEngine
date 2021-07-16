#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::~Triangle()
{
}

bool Triangle::Init()
{
    VERTEX vertices[] =
    {
        {150.f,50.f,0.f,1.f,D3DCOLOR_ARGB(255,255,0,0)},
        {200.f,100.f,0.f,1.f,D3DCOLOR_ARGB(255,0,255,0)},
        {100.f,50.f,0.f,1.f,D3DCOLOR_ARGB(255,0,0,255)}
    };

    if(FAILED(Renderer::GetInst()->GetDevice()->CreateVertexBuffer(3 * sizeof(VERTEX),0,FVF,D3DPOOL_DEFAULT,&m_pVB,NULL)))
        return false;

    void* pVertices;

    if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
        return false;

    memcpy(pVertices, vertices, sizeof(vertices));
    m_pVB->Unlock();

    return true;
}

void Triangle::Release()
{
}

void Triangle::Render()
{
    Renderer::GetInst()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX));
    Renderer::GetInst()->GetDevice()->SetFVF(FVF);
    Renderer::GetInst()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}
