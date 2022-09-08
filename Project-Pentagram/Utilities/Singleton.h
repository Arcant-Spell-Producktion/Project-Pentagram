#pragma once
template <class T>
class Singleton
{
protected:
    static T* instance;
public:

    static T* GetInstance()
    {
        if (instance == nullptr)
        {
            instance = new T();
        }
        return instance;
    }

    void Free() { delete instance; instance = nullptr; }
};

template <class T>
T* Singleton<T>::instance = nullptr;
