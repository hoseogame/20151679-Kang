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
	cout << "������������������������������";
	Utility::Gotoxy(15, 9);
	cout << "��**************************��";
	Utility::Gotoxy(15, 10);
	cout << "��*        GAME OVER       *��";
	Utility::Gotoxy(15, 11);
	cout << "��**************************��";
	Utility::Gotoxy(15, 12);
	cout << "������������������������������";
	Utility::Gotoxy(15, 13);
	cout << "SCORE: " << ScoreManager::Instance()->GetScore() << endl;

	getche();
	GameWorld::Instance()->ChangeScene(new MainScene());
	Utility::SetColor(GRAY);
}

void GameoverScene::Release()
{
}