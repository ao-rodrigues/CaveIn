#pragma once

template<typename T>
class Singleton
{
public:

	static T& instance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new T();
		}

		return *s_instance;
	}

private:
	static T* s_instance;
};

template<typename T>
T* Singleton<T>::s_instance = nullptr;