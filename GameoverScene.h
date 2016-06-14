#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "GameWorld.h"
#include <string>
#include <iostream>

using namespace std;

class GameoverScene final : public Scene
{
public:
	void Init() final;

	void Update() final;

	void Render() final;

	void Release() final;
};