#include "ArcantEngine.h"

ArcantEngine* ArcantEngine::instance = nullptr;

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
	delete instance;
}

bool ArcantEngine::IsRunning()
{
	return this->window.IsRunning();
}

ArcantEngine* ArcantEngine::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new ArcantEngine();
	}
	return instance;
}

Window* ArcantEngine::GetWindow()
{
	return &(this->window);
}