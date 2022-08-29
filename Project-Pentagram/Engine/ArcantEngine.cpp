#include "ArcantEngine.h"

ArcantEngine::ArcantEngine()
	: window(WINDOW_WIDTH, WINDOW_HEIGHT, TITLE)
{
}

void ArcantEngine::Init()
{
	srand(time(NULL));
	this->window.Init();
}

void ArcantEngine::Free()
{
	this->window.Destroy();
	Singleton::Free();
}

bool ArcantEngine::IsRunning()
{
	return this->window.IsRunning();
}

Window* ArcantEngine::GetWindow()
{
	return &(this->window);
}