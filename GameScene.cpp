#include "GameScene.h"
#include "GameWorld.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Utility.h"
#include <cassert>
#include "Input.h"
#include <cstdlib>
#include <ctime>
#include "ScoreManager.h"
#include "GameoverScene.h"

void GameScene::Init()
{
	Show_game_frame();
	ScoreManager::Instance()->SetScore(0);
	nKey = 0;
	length = 1;
	tmp = false;
	srand(time(NULL));
	headSnake = new Snake(Vector2D(15,15),Direction::LEFT,nullptr);
	taleSnake = new Snake(Vector2D(15,15), Direction::LEFT, nullptr);
	headSnake->SetSnakeNext(taleSnake);
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++) {
			map[i][j] = 0;
		}
	}

	map[5][5] = 2;
}

void GameScene::Update()
{
	if (Input::GetKeyDown(KeyCode::LEFT))
		headSnake->SetDirection(Direction::LEFT);
	if (Input::GetKeyDown(KeyCode::DOWN))
		headSnake->SetDirection(Direction::DOWN);
	if (Input::GetKeyDown(KeyCode::RIGHT))
		headSnake->SetDirection(Direction::RIGHT);
	if (Input::GetKeyDown(KeyCode::UP))
		headSnake->SetDirection(Direction::UP);

	if (tmp)
		MakeTale(headSnake->GetDirection());
	else
		MoveSnake(headSnake->GetDirection());
}

void GameScene::MoveSnake(Direction _direction)
{
	Vector2D pos = headSnake->GetVector();
	Vector2D ptmp;
	Snake *cur;
	cur = headSnake;

	if (_direction == Direction::LEFT)
		pos.posX--;
	else if (_direction == Direction::RIGHT)
		pos.posX++;
	else if (_direction == Direction::UP)
		pos.posY--;
	else if (_direction == Direction::DOWN)
		pos.posY++;	

	for (int i = 0; i < length; i++)
	{	
		ptmp = cur->GetVector();
		map[ptmp.posY][ptmp.posX] = 0;
		cur->SetVector(pos);
		if (map[pos.posY][pos.posX] == 2)
			tmp = true;
		else if (map[pos.posY][pos.posX] == 1)
			GameWorld::Instance()->ChangeScene(new GameoverScene());
		if(cur == headSnake)
			map[pos.posY][pos.posX] = 3;
		else
			map[pos.posY][pos.posX] = 1;
		pos = ptmp;
		cur = cur->GetSnakeNext();
	}

	taleSnake->SetVector(ptmp);

	if (((headSnake->GetVector().posX > MAP_X - 2) || (headSnake->GetVector().posX < 1)) || ((headSnake->GetVector().posY < 1) || (headSnake->GetVector().posY > MAP_Y - 2)))
		GameWorld::Instance()->ChangeScene(new GameoverScene());

	Sleep(100);
}

void GameScene::MakeTale(Direction _direction)
{
	Vector2D taleVector = taleSnake->GetVector();
	int score = ScoreManager::Instance()->GetScore();

	if (_direction == Direction::LEFT)
		taleVector.posX++;
	else if (_direction == Direction::RIGHT)
		taleVector.posX--;
	else if (_direction == Direction::UP)
		taleVector.posY--;
	else if (_direction == Direction::DOWN)
		taleVector.posY++;

	CreateSnake(taleVector, _direction);
	tmp = false;

	map[rand() % (MAP_Y - 1) + 1][rand() % (MAP_X - 1) + 1] = 2;

	ScoreManager::Instance()->SetScore(score += 100);
}

void GameScene::CreateSnake(Vector2D _vector,Direction _direction)
{
	Snake *newNode = new Snake(_vector,_direction,nullptr);

	if (headSnake == nullptr)
	{
		headSnake = newNode;
	}
	else
		taleSnake->SetSnakeNext(newNode);

	taleSnake = newNode;
	length++;
}

void GameScene::Render()
{
	Utility::Gotoxy(2 + taleSnake->GetVector().posX * 2, taleSnake->GetVector().posY + 2);
	cout << "  ";

	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++) {
			Utility::Gotoxy( 2 + 2*j, i + 2 );
			if (map[i][j] == 1)
			{
				Utility::SetColor(GRAY);
				Utility::Gotoxy( 2 + 2 * j, i + 2 );
				cout << "∞";
			}
			else if (map[i][j] == 3)
			{
				Utility::SetColor(GRAY);
				cout << "≒";
			}
			else if ( map[i][j] == 2 )
			{
				Utility::SetColor( RED );
				cout << "～";
			}
		}
		cout << endl;
	}

}

void GameScene::Show_game_frame()
{
	int i;
	Utility::SetColor(GRAY);
	system("cls");
	Utility::Gotoxy(0, 1);
	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	for (i = 2; i<22; i++)
	{
		Utility::Gotoxy(0, i);
		printf("早");
		Utility::Gotoxy(72, i);
		printf("早");
	}
	Utility::Gotoxy(0, 22);
	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

	for (i = 4; i<20; i += 2)
	{
		Utility::Gotoxy(76, i);
		printf("∞");
	}

	for (i = 5; i<20; i += 2)
	{
		Utility::Gotoxy(75, i);
		printf("∞");
	}
	Utility::Gotoxy(75, 2);
	printf("��");
	Utility::Gotoxy(75, 3);
	printf("≒");

	Utility::Gotoxy(4, 0);
	printf("Snake Ver 0.1                                    Made By Hyun_Woo");
}

void GameScene::Release()
{
	Snake* cur = headSnake;
	Snake* tmp;

	do
	{
		tmp = cur->GetSnakeNext();
		free(cur);
	} while (tmp == nullptr);
}