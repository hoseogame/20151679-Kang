#include "GameWorld.h"
#include <iostream>

auto main(void) -> int
{
	GameWorld::Instance()->Init();
	GameWorld::Instance()->Update();
	GameWorld::Instance()->Release();
}