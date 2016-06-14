#pragma once
#include <conio.h>
#include <iostream>
using namespace std;

enum KeyCode { LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80 ,SPACE = 32};

class Input
{
private:
	Input() = default;
	~Input() = default;

	static int key;

public:
	Input(const Input&) = delete;

	static void Init()
	{
		key = 0;
	}

	static void Update()
	{
		if (_kbhit())
		{
			_getch();
			key = _getch();
		}
	}

	static void KeyRelease()
	{
		key = 0;
	}

	static bool GetKeyDown(KeyCode keyCode)
	{
		if (key == (int)keyCode)
			return true;
		else
			return false;
	};
};