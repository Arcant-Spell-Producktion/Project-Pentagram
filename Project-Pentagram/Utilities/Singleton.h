#pragma once

#include <mutex>

template <class T>
class Singleton
{
    public:
        Singleton() = default;
        virtual ~Singleton() = default;

        static T& GetInstance()
        {
            static T instance;
            return instance;
        }

        virtual void Free()
        {
            ReinitializeInstance();
        }

    private:

        static void ReinitializeInstance()
        {
            static std::mutex mutex;
            std::lock_guard<std::mutex> lock(mutex);
            static T& instance = GetInstance();
            instance.~T(); // Call the destructor
            new (&instance) T(); // Reinitialize the instance
        }
};
