#pragma once

#include "Window.h"

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define TITLE "Arcant Engine"

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