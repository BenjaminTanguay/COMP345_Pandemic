#pragma once

template <class T> class Singleton
{
public:
	template <typename... Args>
	static T* getInstance(Args... args);
	static void destroyInstance();
private:
	static bool instanceFlag;
	static T* instance;
};

