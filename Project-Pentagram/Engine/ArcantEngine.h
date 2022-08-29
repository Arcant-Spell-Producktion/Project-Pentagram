#pragma once

#include <stdlib.h>
#include <time.h>

#include "Window.h"
#include "../Utilities/Singleton.h"

class ArcantEngine : public Singleton<ArcantEngine>
{
	private:
		Window window;

	public:
		ArcantEngine();
		Window* GetWindow();

		void Init();
		void Free();

		bool IsRunning();

};