#pragma once

#include <thread>
#include <glfw/glfw3.h>

#include "Engine/ArcantEngine.h"

class Thread
{
	private:
		std::thread m_Thread;
		bool m_IsThreadJoin = false;
		bool m_IsWindowReady = false;
		GLFWwindow* m_ThreadWindow = nullptr;

	public:
		template<class Function, class ...Args>
		Thread(Function&& f, Args&&... args)
			: m_Thread(f, args...)
		{
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
			m_ThreadWindow = glfwCreateWindow(640, 480, "", NULL, ArcantEngine::GetInstance().GetWindow()->GetWindowPointer());
		}
		Thread() 
		{
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
			m_ThreadWindow = glfwCreateWindow(640, 480, "", NULL, ArcantEngine::GetInstance().GetWindow()->GetWindowPointer());
		}
		~Thread()
		{
			if (m_IsThreadJoin == false)
			{
				m_Thread.detach();
			}
			glfwDestroyWindow(m_ThreadWindow);
		}

		void Join()
		{
			m_IsThreadJoin = true;
			m_Thread.join();
		}
		void MakeContext()
		{
			glfwMakeContextCurrent(m_ThreadWindow);
		}

		// Setter
		template<class Function, class ...Args>
		void SetFunction(Function&& f, Args&&... args)
		{
			m_Thread = std::thread(std::forward<Function>(f), std::forward<Args>(args)...);
		}
		// Getter
		GLFWwindow* GetThreadWindow() { return m_ThreadWindow; }
};