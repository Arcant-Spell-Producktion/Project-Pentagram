#include "Input.h"

namespace Input
{
	float mouseX;
	float mouseY;
	bool keyPressed[GLFW_KEY_LAST];
	bool keyBeginPressed[GLFW_KEY_LAST];

	bool IsKeyPressed(const int& key)
	{
		return keyPressed[key];
	}

	bool IsKeyBeginPressed(const int& key)
	{
		return keyBeginPressed[key];
	}

	void EndFrame()
	{
		for (int idx = 0; idx < GLFW_KEY_LAST; idx++)
		{
			keyBeginPressed[idx] = false;
		}
	}

	void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keyPressed[key] = true;
			keyBeginPressed[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keyPressed[key] = false;
			keyBeginPressed[key] = false;
		}

		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}

	void cursorCallBack(GLFWwindow* window, double xPos, double yPos)
	{
		mouseX = (float)xPos;
		mouseY = (float)yPos;
	}

	void mouseCallBack(GLFWwindow* window, int key, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			keyPressed[key] = true;
			keyBeginPressed[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keyPressed[key] = false;
			keyBeginPressed[key] = false;
		}
	}
}
