#pragma once

typedef struct D3DXVECTOR2 Vec2;
typedef struct D3DXMATRIX Matrix;

#define dt App::GetInst()->DeltaTime
#define gt App::GetInst()->Time
#define _USE_MATH_DEFINES

template<class T>
inline void SafeDelete(T*& x);

#include<Windows.h>
#include<stdio.h>
#include<iostream>
#include<d3d9.h>
#include<d3dx9.h>
#include<d3dx9math.h>
#include<d3dx9shape.h>
#include<map>
#include<list>
#include<ctime>
#include<vector>
#include<string>
#include<cmath>
//

#include"Types.h"
#include"Singleton.h"
#include"Input.h"
#include"Renderer.h"
#include"App.h"
#include"GameObject.h"
#include"ObjectMgr.h"
#include"Camera.h"
#include"Sprite.h"
#include"Scene.h"
#include"SceneDirector.h"
#include"Terrain.h"
#include"Shapes.h"
//

template<class T>
inline void SafeDelete(T*& x)
{
	delete x;
	x = static_cast<T*>(0);
};