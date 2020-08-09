#include "stdafx.h"
#include "SoundMgr.h"


SoundMgr::SoundMgr()
{
}


SoundMgr::~SoundMgr()
{
}

void SoundMgr::Play(const WCHAR* pFileName, bool loop)
{
	WCHAR szFullPath[256] = L"../Sound/";
	lstrcatW(szFullPath, pFileName);

	if (!loop)
	{
		PlaySound(szFullPath, NULL, SND_ASYNC | SND_NOSTOP | SND_FILENAME);
	}
	else if (loop)
	{
		PlaySound(szFullPath, NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP | SND_FILENAME);
	}
}

void SoundMgr::Stop()
{
	PlaySound(nullptr, NULL, SND_ASYNC);
}