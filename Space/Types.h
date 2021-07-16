#pragma once
#include"stdafx.h"

struct CUSTOMVERTEX
{
    float x, y, z, rhw;
    DWORD color;

}typedef VERTEX;

struct MYINDEX
{
    WORD _0, _1, _2;
}typedef INDEX;

struct TEXTUREVERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    D3DXVECTOR3 t;

}typedef TEXVERTEX;

extern DWORD FVF;
extern DWORD TexVertexFVF;