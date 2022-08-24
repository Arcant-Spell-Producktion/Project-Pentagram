#include "Window.h"

void resizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);
	currentWindow->SetWindowRatio(glm::vec2((float)newWidth / WINDOW_WIDTH, (float)newHeight / WINDOW_HEIGHT));
	currentWindow->SetWidth(newWidth);
	currentWindow->SetHeight(newHeight);
	glViewport(0, 0, newWidth, newHeight);
}

Window::Window(const int& width, const int& height, const char* title)
	: m_Width(width), m_Height(height), m_Title(title), m_Window(nullptr)
{

}

void Window::MakeContextCurrent()
{
	glfwMakeContextCurrent(m_Window);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_Window);
}

void Window::Close()
{
	glfwSetWindowShouldClose(m_Window, true);
}

void Window::Destroy()
{
	glfwTerminate();
	m_Window = nullptr;
}

bool Window::IsNull()
{
	return (m_Window == nullptr ? true : false);
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(m_Window);
}

// Setter Implement
void Window::SetWidth(const int& width) { this->m_Width = width; }
void Window::SetHeight(const int& height) { this->m_Height = height; }
void Window::SetWindowRatio(const glm::vec2& ratio) { this->m_windowRatio = ratio; }

// Getter Implement
GLFWwindow* Window::getWindow() { return m_Window; }
int Window::GetWidth() { return m_Width; }
int Window::GetHeight() { return m_Height; }
glm::vec2 Window::GetWindowRatio() { return m_windowRatio; };

void Window::Init()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

	glfwSetWindowUserPointer((GLFWwindow*)m_Window, (void*)&m_Window);
	glfwSetFramebufferSizeCallback(m_Window, resizeCallback);
	glfwSetKeyCallback(m_Window, Input::keyCallBack);
	glfwSetCursorPosCallback(m_Window, Input::cursorCallBack);
	glfwSetMouseButtonCallback(m_Window, Input::mouseCallBack);

	this->MakeContextCurrent();

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Error : Initialize GLAD failed\n";
		exit(EXIT_FAILURE);
	}

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, m_Width, m_Height);
}
