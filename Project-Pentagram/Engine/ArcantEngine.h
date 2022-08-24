#pragma once

#include <stdlib.h>
#include <time.h>

#include "Window.h"

class ArcantEngine
{
	private:
		static ArcantEngine* instance;
		Window window;

	public:
		ArcantEngine();
		static ArcantEngine* GetInstance();
		Window* GetWindow();

		void Init();
		void Free();

		bool IsRunning();

};