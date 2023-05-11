#pragma once

#include <mutex>

template <class T>
class Singleton
{
    protected:
        static T* instance;
        static std::mutex mutex;
    public:

        static T* GetInstance()
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (instance == nullptr)
            {
                instance = new T();
            }
            return instance;
        }

        void Free()
        {
            std::lock_guard<std::mutex> lock(mutex);
            delete instance;
            instance = nullptr;
        }
};

template <class T>
T* Singleton<T>::instance = nullptr;

template <class T>
std::mutex Singleton<T>::mutex;
