#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Input.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define TITLE "Arcant Engine"

class Window
{
	private:
		GLFWwindow* m_Window;
		int m_Width;
		int m_Height;
		const char* m_Title;
		glm::vec2 m_windowRatio = glm::vec2(1.0f, 1.0f);

	public:
		Window(const int &width, const int &height, const char* title);
		
		void MakeContextCurrent();
		void PollEvents();
		void SwapBuffers();

		void Close();
		bool IsNull();
		bool IsRunning();

		// Setter
		void SetWidth(const int& width);
		void SetHeight(const int& height);
		void SetWindowRatio(const glm::vec2& ratio);

		// Getter
		GLFWwindow* getWindow();
		int GetWidth();
		int GetHeight();
		glm::vec2 GetWindowRatio();

		// Core-Loop
		void Init();
		void Destroy();
};