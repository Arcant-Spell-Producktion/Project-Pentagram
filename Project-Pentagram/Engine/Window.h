#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glfw/glfw3native.h>
#include <glm/glm.hpp>
#include "Engine/stb/stb_image.h"

#include <iostream>
#include <algorithm>

#include "Input.h"

#define WINDOW_RATIO (16.0f / 9.0f)
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TITLE "Arcant Engine"

class Window
{
	private:
		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;

		// Window Size
		int m_Width;
		int m_Height;
		// Viewport Size
		int m_ViewportWidth;
		int m_ViewportHeight;

		const char* m_Title;
		glm::vec2 m_WindowRatio = glm::vec2(1.0f, 1.0f);
		glm::vec2 m_ViewportRatio = glm::vec2(1.0f, 1.0f);
		glm::vec2 m_ViewportPosition = glm::vec2(0.0f, 0.0f);
		bool m_Close = false;

		glm::ivec2 prevScale;
		glm::ivec2 prevPos;

		void InitMaximizeWidget();
		GLFWmonitor* GetCurrentMonitor();

	public:
		Window(const int &width, const int &height, const char* title);
		
		void MakeContextCurrent();
		void PollEvents();
		void SwapBuffers();
		void Close();

		void UpdateGameViewport();
		void UpdateCursorViewport();

		// Setter
		void SetWindowSize(const glm::ivec2 windowSize);
		void SetWindowSize(const int& windowWidth, const int& windowHeight);
		void SetWindowWidth(const int& width);
		void SetWindowHeight(const int& height);
		void SetViewportWidth(const int& width);
		void SetViewportHeight(const int& height);
		void SetWindowDiffRatio(const glm::vec2& ratio);
		void SetViewportDiffRatio(const glm::vec2& ratio);
		void SetViewportPosition(const glm::vec2& position);
		void SetClose(const bool& close);
		void SetFullScreen(const bool fullscreen);

		// Getter
		GLFWwindow* GetWindowPointer();
		int GetWindowWidth() const;
		int GetWindowHeight() const;
		int GetViewportWidth() const;
		int GetViewportHeight() const;
		glm::vec2 GetWindowDiffRatio() const;
		glm::vec2 GetViewportDiffRatio() const;
		bool IsClose() const;
		bool IsNull() const;
		bool IsRunning() const;
		bool IsFullScreen() const;

		// Core-Loop
		void Init();
		void Destroy();
};