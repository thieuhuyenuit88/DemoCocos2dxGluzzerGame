#pragma once

template<typename T>
class Singleton
{
public:
	static T* GetInstance();
	static void Destroy();
private:
	Singleton(Singleton const&){};
	Singleton& operator=(Singleton const&){};
protected:
	static T* instance;
	Singleton(){ instance = static_cast<T*>(this); };
	~Singleton(){ };
};

template<typename T>
T* Singleton<T>::instance = 0;

template<typename T>
T* Singleton<T>::GetInstance(){
	if (!instance)
	{
		Singleton<T>::instance = new T();
	}

	return instance;
}

template<typename T>
void Singleton<T>::Destroy(){
	if (Singleton<T>::instance != 0)
	{
		delete Singleton<T>::instance;
		Singleton<T>::instance = 0;
	}
}