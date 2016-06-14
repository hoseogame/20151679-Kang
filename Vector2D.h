#pragma once
struct Vector2D
{
	int posX;
	int posY;

	Vector2D(int _posX = 0, int _posY = 0)
		: posX(_posX), posY(_posY) {}

	Vector2D(const Vector2D& rhs)
	{
		posX = rhs.posX;
		posY = rhs.posY;
	}

	Vector2D& operator=(const Vector2D& rhs)
	{
		posX = rhs.posX;
		posY = rhs.posY;

		return *this;
	}
};