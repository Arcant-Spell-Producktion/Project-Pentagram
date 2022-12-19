#pragma once
#include <set>
#include <algorithm>
#include <functional>

template <typename T>
class Action
{
public:
    std::function<void(T)> fn;
    Action(std::function<void(T)> _fn) :fn(_fn) {}
    Action(void(*_fn)(T)) : fn(_fn) {}
    template <typename L>
    Action(L&& lambda)
    {
        fn = lambda;
    }

    void operator()(T arg)
    {
        fn(arg);

    }

    bool operator==(Action<T>& a) const
    {
        return fn.target_type() == a.fn.target_type();
    }
};

template <typename T>
struct ActionCmp
{
    bool operator()(const Action<T>& a, const Action<T>& b) const
    {
        return a.fn.target_type().name() < b.fn.target_type().name();
    }
};

template <typename T>
class Event
{
private:
    std::set<Action<T>, ActionCmp<T>> m_Listeners;

public:
    void AddListenner(Action<T> callfn)
    {
        m_Listeners.insert(callfn);
    }

    void RemoveAllListeners()
    {
        m_Listeners.clear();
    }

    void RemoveListenner(Action<T> callfn)
    {
        auto it = m_Listeners.find(callfn);
        if (it != m_Listeners.end())
            m_Listeners.erase(it);
    }

    void operator=(Action<T> const& callfn)
    {
        RemoveAllListeners();
        AddListenner(callfn);
    }

    void operator+=(Action<T> const& callfn)
    {
        AddListenner(callfn);
    }

    void operator-=(Action<T> const& callfn)
    {
        RemoveListenner(callfn);
    }

    void Invoke(T arg)
    {
        for (auto func : m_Listeners)
        {
            func(arg);
        }
    }

    void operator()(T arg)
    {
        Invoke(arg);
    }
};