#include "Engine/ArcantEngine.h"
#include "Engine/GameStateController.h"
#include "Engine/Collector/EngineDataCollector.h"

#include "Game/GameData/RuntimeGameData.h"
#include "Game/Spells/SpellDatabase.h"

ArcantEngine* engine = nullptr;
GameStateController* gameStateController = nullptr;
EngineDataCollector* engineDataCollector = nullptr;

RuntimeGameData* currentGame = nullptr;
SpellDatabase* spellDatabase = nullptr;

int main()
{
	// Initialize Engine
	engine = ArcantEngine::GetInstance();
	engine->Init();

	// Initialize ShaderCollector(For collecting type of Shader)
	// Initialize FontCollector(For collecting type of Font)
	// Initialize TextureCollector(For collecting all of texture in game)
	engineDataCollector = EngineDataCollector::GetInstance();
	engineDataCollector->LoadResource();

	// Initialize gameStateController
	gameStateController = GameStateController::GetInstance();
	gameStateController->InitGameScene(GameState::GS_MENU_SCENE);

    // Initialize SpellDatabase (For collecting all spell data)
    spellDatabase = SpellDatabase::GetInstance();


    //Initialize GameData (For data management during runtime)
    currentGame = RuntimeGameData::GetInstance();

    //Init player, TODO:: done in character select instead
    //CasterData playerData(Element::Debug, CasterPosition::CasterA, 100, 10);
    currentGame->Player = new PlayerData({ Element::Fire, CasterPosition::CasterA, 100, 10 });

	double currTime = 0;
	double prevTime = 0;
	while (engine->IsRunning())
	{
		// Receive Input from User
		engine->GetWindow()->PollEvents();

		currTime = glfwGetTime();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
