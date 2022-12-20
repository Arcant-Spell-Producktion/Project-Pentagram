#pragma once
#include <iostream>
#include <set>
#include <algorithm>
#include <functional>

/**

@brief Action class template.

Wraps a function or lambda that takes a single argument of type T.

@tparam T The type of the argument that the wrapped function takes.
*/

template <typename T>
class Action
{
public:
    /*

    @brief std::function that holds the wrapped function.
    */
    std::function<void(T)> fn;
    /**

    @brief Default constructor that initializes the std::function with a null function pointer.
    */
    Action() : fn(nullptr) {}
    /**

    @brief Constructor that takes a std::function.
    @param _fn The std::function to be wrapped.
    */
    Action(std::function<void(T)> _fn) : fn(_fn) {}
    /**

    @brief Constructor that takes a function pointer.
    @param _fn The function pointer to be wrapped.
    /
    Action(void (_fn)(T)) : fn(_fn) {}
    /**

    @brief Constructor that takes a lambda.
    @tparam L The type of the lambda.
    @param lambda The lambda to be wrapped.
    */
    template <typename L>
    Action(L&& lambda)
    {
        // Assign the lambda to the std::function
        fn = lambda;
    }
    /**

    @brief Get the value of the wrapped function as a std::string.
    @return The value of the wrapped function as a std::string.
    */
    std::string GetFuncValue() const
    {
        return fn.target_type().name();
    }
    /**

    @brief Call the wrapped function.
    @param arg The argument to pass to the wrapped function.
    */
    void operator()(T arg)
    {
        fn(arg);
    }
    /**

    @brief Compare the function names of the Action objects using std::string comparison.
    @param other The other Action object to compare to.
    @return True if the function names are equal, false otherwise.
    */
    bool operator==(const Action<T>& other) const
    {
        return GetFuncValue() == other.GetFuncValue();
    }
};

/**

@brief Comparator for Action objects.
@tparam T The type of the argument that the Action objects' wrapped functions take.
*/
template <typename T>
struct ActionCmp
{
    /*
    @brief Compare the function names of the Action objects using the '<' operator.
    @param lhs The left-hand side Action object.
    @param rhs The right-hand side Action object.
    @return True if the function name of the left-hand side Action object is less than the function name of the right-hand side Action object, false otherwise.
    */
    bool operator()(const Action<T>& lhs, const Action<T>& rhs) const
    {
        // Compare the function names of the Action objects using the '<' operator
        return lhs.GetFuncValue() < rhs.GetFuncValue();
    }
};

/**

@brief Event class template.

Container for Action objects.

@tparam T The type of the argument that the Action objects' wrapped functions take.
*/
template <typename T>
class Event
{
private:
    /*

    @brief std::set to store the Action objects.
    */
    std::set<Action<T>, ActionCmp<T>> m_Listeners;
    /**

    @brief Log the function pointers of all Action objects in the set.
    */
    void LogListeners() const
    {
        for (const auto& action : m_Listeners)
        {
            std::cout << "Function pointer: " << action.GetFuncValue() << std::endl;
        }
    }
public:
    /**
    * @brief Add an Action to the set.
    *
    * @param callfn The Action object to add to the set.
    */
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
        // LogListeners();
    }

    /**
     * @brief Remove a specific Action from the set.
     *
     * @param callfn The Action object to remove from the set.
     */
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

    /**
     * @brief Remove all Action objects from the set.
     */
    void RemoveAllListeners()
    {
        m_Listeners.clear();
    }

    /**
     * @brief Set the Event to a single Action.
     *
     * @param callfn The Action object to set the Event to.
     */
    void operator=(Action<T> const& callfn)
    {
        RemoveAllListeners();
        AddListener(callfn);
    }

    /**
     * @brief Add an Action to the Event.
     *
     * @param callfn The Action object to add to the Event.
     */
    void operator+=(Action<T> const& callfn)
    {
        AddListener(callfn);
    }

    /**
     * @brief Remove an Action from the Event.
     *
     * @param callfn The Action object to remove from the Event.
     */
    void operator-=(Action<T> const& callfn)
    {
        RemoveListener(callfn);
    }

    /**

    @brief Invoke all stored Actions with the given argument.
    @param arg The argument to pass to the wrapped functions of the stored Action objects.
    */
    void Invoke(T arg)
    {
        for (auto func : m_Listeners)
        {
            func(arg);
        }
    }
    /**

    @brief Invoke all stored Actions with the given argument.
    @param arg The argument to pass to the wrapped functions of the stored Action objects.
    */
    void operator()(T arg)
    {
        Invoke(arg);
    }
};