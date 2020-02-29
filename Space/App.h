#pragma once
class App : public Singleton<App>
{
private:
	HWND m_Hwnd;

public:
	App();
	~App();

public:
	int m_Width;
	int m_Height;
	bool m_WindowMode;

private:
	bool _CreateWindow();
	bool _CreateRenderer();

public:
	bool Init(int width, int height, bool windowMode);
	void Run();
	void Release();

public:
	float
		DeltaTime,
		Time;

public:
	HWND GetHwnd() {
		return m_Hwnd;
	}

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

};

