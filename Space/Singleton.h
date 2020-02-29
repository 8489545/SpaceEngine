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
};

template<class T>
T* Singleton<T>::m_Instance = 0;