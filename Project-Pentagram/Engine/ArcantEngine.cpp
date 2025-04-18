#include "ArcantEngine.h"

ArcantEngine::ArcantEngine()
	: m_Window(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE)
{
}

void ArcantEngine::Init()
{
	srand(time(NULL));
	this->m_Window.Init();
}
void ArcantEngine::Free()
{
	this->m_Window.Destroy();
	Singleton::Free();
}

Window* ArcantEngine::GetWindow()
{
	return &(this->m_Window);
}
bool ArcantEngine::IsRunning() const
{
	return this->m_Window.IsRunning();
}