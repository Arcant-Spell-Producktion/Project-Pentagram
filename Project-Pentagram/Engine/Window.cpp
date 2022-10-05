#include "Window.h"

// ----------------- Callback Function ----------------- 
void resizeCallback(GLFWwindow* window, int newWidth, int newHeight)
{
	Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);
	currentWindow->SetWindowRatio(glm::vec2((float)newWidth / WINDOW_WIDTH, (float)newHeight / WINDOW_HEIGHT));
	currentWindow->SetWidth(newWidth);
	currentWindow->SetHeight(newHeight);

	if ((float)newWidth / newHeight == WINDOW_RATIO)
	{
		glViewport(0, 0, newWidth, newHeight);
	}
	else if (newWidth * (1.0f / WINDOW_RATIO) <= newHeight)
	{
		int ratioHeight = newWidth * (1.0f / WINDOW_RATIO);
		int offsetHeight = std::abs(newHeight - ratioHeight);
		glViewport(0, offsetHeight / 2, newWidth, ratioHeight);
	}
	else
	{
		int ratioWidth = newHeight * WINDOW_RATIO;
		int offsetWidth = std::abs(newWidth - ratioWidth);
		glViewport(offsetWidth / 2, 0, ratioWidth, newHeight);
	}
}
void windowCloseCallback(GLFWwindow* window)
{
	Window* currentWindow = (Window*)glfwGetWindowUserPointer(window);
	currentWindow->SetClose(true);
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

// Setter Implement
void Window::SetWindowSize(const glm::ivec2 windowSize) 
{
	this->m_Width = windowSize.x;
	this->m_Height = windowSize.y;
	glfwSetWindowSize(m_Window, m_Width, m_Height);
}
void Window::SetWindowSize(const int& windowWidth, const int& windowHeight)
{
	this->m_Width = windowWidth;
	this->m_Height = windowHeight;
	glfwSetWindowSize(m_Window, m_Width, m_Height);
}
void Window::SetWidth(const int& width) 
{ 
	this->m_Width = width;
	glfwSetWindowSize(m_Window, m_Width, m_Height);
}
void Window::SetHeight(const int& height) 
{ 
	this->m_Height = height;
	glfwSetWindowSize(m_Window, m_Width, m_Height);
}
void Window::SetWindowRatio(const glm::vec2& ratio) 
{ 
	this->m_windowRatio = ratio; 
}
void Window::SetClose(const bool& close) 
{ 
	this->m_Close = close; 
}
void Window::SetFullScreen(const bool fullscreen)
{
	// If currentScreen already fullscreen or window
	if (IsFullScreen() == fullscreen)
		return;

	if (fullscreen)
	{
		// backup window position and window size
		glfwGetWindowPos(m_Window, &prevPos[0], &prevPos[1]);
		glfwGetWindowSize(m_Window, &prevScale[0], &prevScale[1]);

		// get resolution of monitor
		const GLFWvidmode* mode = glfwGetVideoMode(m_Monitor);

		// switch to full screen
		glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, mode->width, mode->height, 0);
	}
	else
	{
		// restore last window size and position		
		glfwSetWindowMonitor(m_Window, nullptr, prevPos.x, prevPos.y, prevScale.x, prevScale.y, 0);

	}
	std::cout << m_Width << " " << m_Height << "\n";
}

// Getter Implement
GLFWwindow* Window::getWindow() 
{ 
	return m_Window; 
}
int Window::GetWidth() const 
{ 
	return m_Width; 
}
int Window::GetHeight() const 
{ 
	return m_Height; 
}
glm::vec2 Window::GetWindowRatio() const 
{ 
	return m_windowRatio; 
}
bool Window::IsClose() const 
{ 
	return m_Close; 
}
bool Window::IsNull() const
{
	return (m_Window == nullptr ? true : false);
}
bool Window::IsRunning() const
{
	return !m_Close;
}
bool Window::IsFullScreen() const
{
	return glfwGetWindowMonitor(m_Window) != nullptr;
}

void Window::Init()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

	glfwSetWindowUserPointer((GLFWwindow*)m_Window, (void*)&m_Window);

	glfwSetWindowCloseCallback(m_Window, windowCloseCallback);
	glfwSetFramebufferSizeCallback(m_Window, resizeCallback);
	glfwSetKeyCallback(m_Window, Input::keyCallBack);
	glfwSetCursorPosCallback(m_Window, Input::cursorCallBack);
	glfwSetMouseButtonCallback(m_Window, Input::mouseCallBack);
	
	m_Monitor = glfwGetPrimaryMonitor();

	GLFWimage images[1];
	images[0].pixels = stbi_load("DUCK.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(m_Window, 1, images);
	stbi_image_free(images[0].pixels);

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
void Window::Destroy()
{
	glfwTerminate();
	m_Window = nullptr;
}