#include "stdafx.h"
#include "Box.h"

Box::Box()
{
    D3DXCreateTeapot(Renderer::GetInst()->GetDevice(),&m_mesh, NULL);
}

Box::~Box()
{
}

void Box::Render()
{
    m_mesh->DrawSubset(0);
}
