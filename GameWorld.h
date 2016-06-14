#pragma once
#include "Scene.h"
#include "MainScene.h"

class GameWorld
{
private:
	GameWorld() = default;
	~GameWorld() = default;

	bool isQuit;

	Scene* currentScene;
	Scene* changeScene;
public:
	GameWorld(const GameWorld&) = delete;

	static GameWorld* Instance()
	{
		static GameWorld* gameWorld = new GameWorld();
		return gameWorld;
	}

	void Init();

	void Update();

	void Release();

	void ChangeScene(Scene* newScene);

	void IsQuit();
};