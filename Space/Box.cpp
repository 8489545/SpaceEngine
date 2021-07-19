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
    if (INPUT->GetKey('1') == KeyState::PRESS)
        m_BoxTransform->m_Position.x += 10 * dt;
    if (INPUT->GetKey('2') == KeyState::PRESS)
        m_BoxTransform->m_Position.y += 10 * dt;
    if (INPUT->GetKey('3') == KeyState::PRESS)
        m_BoxTransform->m_Position.z += 10 * dt;
}

void Box::Render()
{
    m_BoxTransform->SetTransform(device);
    m_mesh->DrawSubset(0);
}
