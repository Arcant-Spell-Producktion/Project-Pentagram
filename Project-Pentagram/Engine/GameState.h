#pragma once

enum class GameState
{
	// List of all Scene
	GS_LOAD_SCENE,
	GS_MENU_SCENE,
	GS_NODE_SCENE,
	GS_BATTLE_SCENE,
	GS_DEMO_SCENE,

	GS_RESTART,
	GS_QUIT,
	GS_NONE
};