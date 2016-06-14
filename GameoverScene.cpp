#include "GameoverScene.h"
#include "Utility.h"
#include "ScoreManager.h"
#include "GameWorld.h"
#include "GameScene.h"
#include <conio.h>

void GameoverScene::Init()
{
}

void GameoverScene::Update()
{
}


void GameoverScene::Render()
{
	Utility::SetColor(RED);
	Utility::Gotoxy(15, 8);
	cout << "旨收收收收收收收收收收收收收旬";
	Utility::Gotoxy(15, 9);
	cout << "早**************************早";
	Utility::Gotoxy(15, 10);
	cout << "早*        GAME OVER       *早";
	Utility::Gotoxy(15, 11);
	cout << "早**************************早";
	Utility::Gotoxy(15, 12);
	cout << "曲收收收收收收收收收收收收收旭";
	Utility::Gotoxy(15, 13);
	cout << "SCORE: " << ScoreManager::Instance()->GetScore() << endl;

	getche();
	GameWorld::Instance()->ChangeScene(new MainScene());
	Utility::SetColor(GRAY);
}

void GameoverScene::Release()
{
}