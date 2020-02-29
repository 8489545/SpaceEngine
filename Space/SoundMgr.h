#pragma once
class SoundMgr :public Singleton<SoundMgr>
{
public:
	SoundMgr();
	~SoundMgr();

	void Play(const WCHAR* pFileName, bool loop);
	void Stop();
};

