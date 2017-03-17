#include "Singleton.h"


template <class T> T* Singleton<T>::instance = nullptr;
//template <class T> bool Singleton<T>::instanceFlag = false;

template<class T>
template<typename ...Args>
inline T * Singleton<T>::getInstance(Args ...args)
{
	if (instance == nullptr)
	{
		instanceFlag = true;
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
