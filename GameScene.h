#pragma once
#include "Scene.h"
#include "Snake.h"
#include <array>

using namespace std;

const int MAP_X = 35;
const int MAP_Y = 20;

class GameScene : public Scene
{
private:
	int nKey;
	/*int map[30][30];*/
	array<array<int, MAP_X>, MAP_Y> map;
	Snake *headSnake;
	Snake *taleSnake;
	int length;
	bool tmp;

public:
	void Init() final; // 다시 재정의를 못하도록 하는 셀러리드 라는 키워드

	void Update() final;

	void Render() final;

	void Release() final;

	void MakeTale(Direction _direction);

	void Show_game_frame();

	void CreateSnake(Vector2D _vector,Direction _direction);

	void MoveSnake(Direction _direction);
};