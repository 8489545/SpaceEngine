#pragma once
struct Vertex
{
	Vertex() {};

	Vertex(float _x, float _y, float _z,D3DCOLOR _c)
	{
		x = _x;
		y = _y;
		z = _z;

		color = _c;
	}

	float x = 0.f, y = 0.f, z = 0.f;
	D3DCOLOR color;

	static const DWORD FVF;
};
class Triangle : public Object
{
	IDirect3DVertexBuffer9* m_Triangle = 0;
public:
	Triangle();
	~Triangle();

	bool Init();
	void Release();

	void Render();
};

