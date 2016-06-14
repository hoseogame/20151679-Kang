#include "GameWorld.h"
#include "Input.h"
#include "GameoverScene.h"

void GameWorld::Init()
{
	Input::Init();
	currentScene = new MainScene();

	isQuit      = false;
	changeScene = nullptr;
}

void GameWorld::Update()
{
	while (!isQuit) {
		if (changeScene)
		{
			currentScene->Release();
			delete currentScene;

			currentScene = changeScene;
			currentScene->Init();

			changeScene = nullptr;
		}
		else
		{
			Input::Update();
			currentScene->Update();
			currentScene->Render();
			Input::KeyRelease();
		}
	}
}

void GameWorld::Release()
{
	currentScene->Release();
	delete currentScene;
}

void GameWorld::ChangeScene(Scene* newScene)
{
	changeScene = newScene;
}

void GameWorld::IsQuit()
{
	isQuit = true;
}