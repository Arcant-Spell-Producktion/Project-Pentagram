#pragma once

#include <mutex>

template <class T>
class Singleton
{
    public:
        Singleton() = default;
        ~Singleton() = default;
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        
        static T* GetInstance()
        {
            std::call_once(initFlag, []() {
                instance = new T();
                });

            return instance;
        }

        void Free()
        {
            std::lock_guard<std::mutex> lock(mutex);
            delete instance;
            instance = nullptr;
        }

    private:

        static T* instance;
        static std::once_flag initFlag;
        static std::mutex mutex;
};

template <class T>
T* Singleton<T>::instance = nullptr;

template <class T>
std::once_flag Singleton<T>::initFlag;

template <class T>
std::mutex Singleton<T>::mutex;
