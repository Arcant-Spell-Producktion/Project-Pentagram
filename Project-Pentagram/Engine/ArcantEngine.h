#pragma once

#include <stdlib.h>
#include <time.h>

#include "Window.h"
#include "Utilities/Singleton.h"

class ArcantEngine : public Singleton<ArcantEngine>
{
	private:
		Window m_Window;

	public:
		ArcantEngine();

		void Init();
		void Free();

		Window* GetWindow();
		bool IsRunning() const;

};