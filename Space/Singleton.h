#pragma once

template <class T>
class Singleton
{
	static T* m_Instance;

public:
	Singleton() {};
	~Singleton() {};

	static T* GetInst()
	{
		if (m_Instance == nullptr)
			m_Instance = new T();

		return m_Instance;
	}

	static void ReleaseInst()
	{
		delete m_Instance;
		m_Instance = NULL;
	}
};

template<class T>
T* Singleton<T>::m_Instance = 0;