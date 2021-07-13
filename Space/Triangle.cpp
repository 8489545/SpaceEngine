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
    CUSTOMVERTEX vertices[] =
    {
        {150.f,50.f,0.5f,1.f,D3DCOLOR_XRGB(255,0,0)},
        {250.f,250.f,0.5f,1.f,D3DCOLOR_XRGB(0,255,0)},
        {50.f,250.f,0.5f,1.f,D3DCOLOR_XRGB(0,0,255)}
    };

    if(FAILED(Renderer::GetInst()->GetDevice()->CreateVertexBuffer(sizeof(vertices),0,FVF,D3DPOOL_DEFAULT,&m_pVB,NULL)))
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

void Triangle::Update()
{
}

void Triangle::Render()
{
    Renderer::GetInst()->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
    Renderer::GetInst()->GetDevice()->SetFVF(FVF);
    Renderer::GetInst()->GetDevice()->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, 1);
}
