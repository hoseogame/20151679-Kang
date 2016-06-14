#pragma once

struct STAGE {
private:
	int speed;
	int triple_rate;
	int clear_block;
public:
	void SetSpeed(int _speed) { speed = _speed; }
	const int GetSpeed() { return speed; }

	void Setrate(int _rate) { triple_rate = _rate; }
	const int Getrate() { return triple_rate; }

	void Setblock(int _block) { clear_block = _block; }
	const int Getblock() { return clear_block; }
};