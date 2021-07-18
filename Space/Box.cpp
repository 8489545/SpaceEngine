#include "stdafx.h"
#include "Box.h"

Box::Box()
{
    D3DXCreateTeapot(Renderer::GetInst()->GetDevice(),&m_mesh, NULL);

    m_BoxTransform = new Transform();
}

Box::~Box()
{
}

void Box::Update()
{
}

void Box::Render()
{
    m_BoxTransform->SetTransform(device);
    m_mesh->DrawSubset(0);
}
