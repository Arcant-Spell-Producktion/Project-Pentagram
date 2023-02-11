#include <cstdlib>
#include <time.h>

#include "Engine/ArcantEngine.h"
#include "Engine/GameStateController.h"
#include "Engine/Collector/EngineDataCollector.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/GameData/CasterData/CasterStatDatabase.h"
#include "Game/Spells/SpellDatabase.h"

ArcantEngine* engine = nullptr;
GameStateController* gameStateController = nullptr;
EngineDataCollector* engineDataCollector = nullptr;

RuntimeGameData* currentGame = nullptr;
SpellDatabase* spellDatabase = nullptr;
CasterStatDatabase* casterDatabase = nullptr;

int main()
{
	// Initialize Engine
	engine = ArcantEngine::GetInstance();
	engine->Init();

	// Initialize ShaderCollector(For collecting type of Shader)
	// Initialize FontCollector(For collecting type of Font)
	// Initialize TextureCollector(For collecting all of texture in game)
	// engineDataCollector->LoadResource() was already in LoadScene
	engineDataCollector = EngineDataCollector::GetInstance();

	// Initialize gameStateController
	gameStateController = GameStateController::GetInstance();
	gameStateController->InitGameScene(GameState::GS_LOAD_SCENE);

    // Initialize SpellDatabase (For collecting all spell data)
    spellDatabase = SpellDatabase::GetInstance();
    spellDatabase->LoadResource();

    // Initialize CasterDatabase (For collecting all caster data)
    casterDatabase = CasterStatDatabase::GetInstance();
    casterDatabase->LoadResource();

    //Initialize GameData (For data management during runtime)
    currentGame = RuntimeGameData::GetInstance();

    srand(time(0));

	double currTime = 0;
	double prevTime = 0;
	while (engine->IsRunning())
	{
		// Receive Input from User
		engine->GetWindow()->PollEvents();

		currTime = glfwGetTime();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gameStateController->currentScene->GameSceneUpdate(currTime - prevTime);

		if (gameStateController->currentState == GameState::GS_QUIT)
		{
			break;
		}

		gameStateController->currentScene->GameSceneDraw();

		// End Frame
		Input::EndFrame();
		engine->GetWindow()->SwapBuffers();
		gameStateController->UpdateGameState();
		prevTime = currTime;
	}
	gameStateController->currentScene->GameSceneUnload();
	gameStateController->currentScene->GameSceneFree();

	// Deallocate instance
    currentGame->Free();
    spellDatabase->Free();

	engine->Free();
	gameStateController->Free();
	engineDataCollector->Free();
}
