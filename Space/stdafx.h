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
#include<map>
#include<list>
#include<ctime>
#include<vector>
#include<string>
#include<sstream>
#include<cmath>
#include<mmsystem.h>
//

#include"Singleton.h"
#include"Input.h"
#include"Renderer.h"
#include"App.h"
#include"Object.h"
#include"Scene.h"
#include"ObjectMgr.h"
#include"CollisionMgr.h"
#include"SceneDirector.h"
#include"TextMgr.h"
#include"SoundMgr.h"
#include"Camera.h"
#include"Sprite.h"
#include"Animation.h"
#include"EffectMgr.h"
//

template<class T>
inline void SafeDelete(T*& x)
{
	delete x;
	x = static_cast<T*>(0);
};