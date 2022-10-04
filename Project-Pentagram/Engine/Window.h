#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "Input.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TITLE "Arcant Engine"

class Window
{
	private:
		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
		int m_Width;
		int m_Height;
		const char* m_Title;
		glm::vec2 m_windowRatio = glm::vec2(1.0f, 1.0f);
		bool m_Close = false;

		glm::ivec2 prevScale;
		glm::ivec2 prevPos;

	public:
		Window(const int &width, const int &height, const char* title);
		
		void MakeContextCurrent();
		void PollEvents();
		void SwapBuffers();
		void Close();

		// Setter
		void SetWidth(const int& width);
		void SetHeight(const int& height);
		void SetWindowRatio(const glm::vec2& ratio);
		void SetClose(const bool& close);
		void SetFullScreen(const bool fullscreen);

		// Getter
		GLFWwindow* getWindow();
		int GetWidth() const;
		int GetHeight() const;
		glm::vec2 GetWindowRatio() const;
		bool IsClose() const;
		bool IsNull() const;
		bool IsRunning() const;
		bool IsFullScreen() const;

		// Core-Loop
		void Init();
		void Destroy();
};