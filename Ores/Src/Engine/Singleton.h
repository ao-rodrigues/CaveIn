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

	static void deleteInstance()
	{
		delete s_instance;
		s_instance = nullptr;
	}

private:
	static T* s_instance;
};

template<typename T>
T* Singleton<T>::s_instance = nullptr;