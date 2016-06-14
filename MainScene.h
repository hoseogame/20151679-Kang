#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "GameWorld.h"
#include "HexaScene.h"
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class MainScene : public Scene
{
private:
	string message;
public:
	void Init() final;

	void Update() final;

	void Render() final;

	void Release() final;
};