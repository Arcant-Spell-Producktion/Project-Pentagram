#pragma once
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>

// Action class template
// Wraps a function or lambda that takes a single argument of type T
template <typename T>
class Action
{
public:
    // std::function that holds the wrapped function
    std::function<void(T)> fn;

    // Default constructor that initializes the std::function with a null function pointer
    Action() : fn(nullptr) {}

    // Constructor that takes a std::function
    Action(std::function<void(T)> _fn) :fn(_fn) {}

    // Constructor that takes a function pointer
    Action(void(*_fn)(T)) : fn(_fn) {}

    // Constructor that takes a lambda
    template <typename L>
    Action(L&& lambda)
    {
        // Assign the lambda to the std::function
        fn = lambda;
    }

    std::string GetFuncValue() const
    {
        return fn.target_type().name();
    }

    // Call the wrapped function
    void operator()(T arg)
    {
        fn(arg);
    }

    // Compare the function names of the Action objects using std::string comparison
    bool operator==(const Action<T>& other) const
    {
        return GetFuncValue() == other.GetFuncValue();
    }
};


// Comparator for Action objects
template <typename T>
struct ActionCmp
{
    bool operator()(const Action<T>& lhs, const Action<T>& rhs) const
    {
        // Compare the function names of the Action objects using the '<' operator
        return lhs.GetFuncValue() < rhs.GetFuncValue();
    }
};

// Event class template
// Container for Action objects
template <typename T>
class Event
{
private:
    // std::set to store the Action objects
    std::set<Action<T>, ActionCmp<T>> m_Listeners;

    // Log the function pointers of all Action objects in the set
    void LogListeners() const
    {
        for (const auto& action : m_Listeners)
        {
            std::cout << "Function pointer: " << action.GetFuncValue() << std::endl;
        }
    }
public:

    // Add an Action to the set
    void AddListener(Action<T> callfn)
    {
        // Check if the Action is already present in the set
        if (m_Listeners.count(callfn) > 0)
        {
            // Log a warning message
            std::cerr << "Warning: Action object pointed to " << callfn.GetFuncValue() << " already present in Event" << std::endl;
            return;
        }

        m_Listeners.insert(callfn);
        //LogListeners();
    }

    // Remove a specific Action from the set
    void RemoveListener(Action<T> callfn)
    {
        // Check if the Action is present in the set
        if (m_Listeners.count(callfn) == 0)
        {
            // Log a warning message
            std::cerr << "Warning: Action object not present in Event" << std::endl;
            return;
        }

        m_Listeners.erase(callfn);
    }

    // Remove all Action objects from the set
    void RemoveAllListeners()
    {
        m_Listeners.clear();
    }

    // Set the Event to a single Action
    void operator=(Action<T> const& callfn)
    {
        RemoveAllListeners();
        AddListener(callfn);
    }

    // Add an Action to the Event
    void operator+=(Action<T> const& callfn)
    {
        AddListener(callfn);
    }

    // Remove an Action from the Event
    void operator-=(Action<T> const& callfn)
    {
        RemoveListener(callfn);
    }

    // Invoke all stored Actions with the given argument
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