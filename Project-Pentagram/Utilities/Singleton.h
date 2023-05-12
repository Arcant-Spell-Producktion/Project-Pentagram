#pragma once

#include <mutex>

template <class T>
class Singleton
{
    public:
        Singleton() = default;
        ~Singleton() = default;

        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

        void Free()
        {
        }

    private:
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
};
