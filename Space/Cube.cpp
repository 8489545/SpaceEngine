#include "stdafx.h"
#include "Cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

bool Cube::Init()
{
	if (!InitVB())
		return false;
	if (!InitIB())
		return false;

	return true;
}

void Cube::Release()
{
}

bool Cube::InitVB()
{
	VERTEX vertices[] =
	{
		{ -1,  1,  1, 0xffff0000 },	/// v0
		{  1,  1,  1, 0xff00ff00 },	/// v1
		{  1,  1, -1, 0xff0000ff },	/// v2
		{ -1,  1, -1, 0xffffff00 },	/// v3

		{ -1, -1,  1, 0xff00ffff },	/// v4
		{  1, -1,  1, 0xffff00ff },	/// v5
		{  1, -1, -1, 0xff000000 },	/// v6
		{ -1, -1, -1, 0xffffffff }	/// v7
	};

	if (FAILED(Renderer::GetInst()->GetDevice()->CreateVertexBuffer(8 * sizeof(VERTEX), 0, FVF, D3DPOOL_DEFAULT, &m_pVB, NULL)))
		return false;

	void* pVertices;
	if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return false;

	memcpy(pVertices, vertices, sizeof(vertices));

	m_pVB->Unlock();

	return true;
}

bool Cube::InitIB()
{
	INDEX indices[] =
	{
		{ 0, 1, 2 }, { 0, 2, 3 },	/// À­¸é
		{ 4, 6, 5 }, { 4, 7, 6 },	/// ¾Æ·§¸é
		{ 0, 3, 7 }, { 0, 7, 4 },	/// ¿ÞÂÊ¸é
		{ 1, 5, 6 }, { 1, 6, 2 },	/// ¿À¸¥ÂÊ ¸é
		{ 3, 2, 6 }, { 3, 6, 7 },	/// ¾Õ¸é
		{ 0, 4, 5 }, { 0, 5, 1 }	/// µÞ¸é
	};

	if (FAILED(Renderer::GetInst()->GetDevice()->CreateIndexBuffer(12 * sizeof(INDEX), 0, D3DFMT_INDEX16, 
		D3DPOOL_DEFAULT, &m_pIB, NULL)))
		return false;

	void* pIndices;

	if (FAILED(m_pIB->Lock(0, sizeof(indices), (void**)&pIndices, 0)))
		return false;

	memcpy(pIndices, indices, sizeof(indices));

	m_pIB->Unlock();

	return true;

}

void Cube::Render()
{
	auto device = Renderer::GetInst()->GetDevice();

	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX));
	device->SetFVF(FVF);
	device->SetIndices(m_pIB);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

}
