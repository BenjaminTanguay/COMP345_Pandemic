#pragma once

template <class T> class Singleton
{
public:
	template <typename... Args>
	static T* getInstance(Args... args);
	static void destroyInstance();
private:
	static T* instance;
};

template <class T> T* Singleton<T>::instance = nullptr;

template<class T>
template<typename ...Args>
inline T * Singleton<T>::getInstance(Args ...args)
{
	if (!instance)
	{
		instance = new T(std:forward<Args>(args)...);
	}
	return instance;
}

template<class T>
inline void Singleton<T>::destroyInstance()
{
	delete instance;
	instance = nullptr;
}
