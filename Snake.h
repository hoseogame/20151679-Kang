#pragma once
#include "Vector2D.h"

enum class Direction { LEFT = 0, RIGHT, UP, DOWN };

class Snake
{
private:
	Vector2D vector;
	Direction direction;
	Snake *next = nullptr;

public:
	Snake(Vector2D _vector, Direction _direction, Snake *_next = nullptr)
		: vector(_vector), direction(_direction), next(_next) {}

	void SetDirection(Direction _direction) { direction = _direction; }
	void SetVector(Vector2D _vector) { vector = _vector; }
	void SetSnakeNext(Snake* _next) { next = _next; }

	const Vector2D& GetVector() { return vector; }
	const Direction& GetDirection() { return direction; }
	Snake* GetSnakeNext() { return next; }
};