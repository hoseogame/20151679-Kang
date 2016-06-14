#pragma once
#include "Utility.h"
#include <conio.h>
#include <Windows.h>
#include "LevelManager.h"
#include "Scene.h"
#include <iostream>
#include"ScoreManager.h"
#include "Stage.h"
#include "GameWorld.h"
#include "GameoverScene.h"
#include "Input.h"
#include "Vector2D.h"

using namespace std;

class HexaScene : public Scene
{
private:
	const int abs_x = 6;
	const int abs_y = 2;
	int cur_block[3];
	int next_block[3];
	int blocks;
	int max_combo;
	int total_block[21][10];	//����:����:��� 
	STAGE stage_data[8];
	Vector2D cur;
	int i;
	char keytemp;
	int is_gameover;
	int shape_tmp;
	int blank_block[3] = { 0,0,0 };
	int return_tmp;

public:
	void Init() final; 

	void Update() final;

	void Render() final;

	void Release() final;

	void show_logo();

	void input_data();

	int show_cur_block(int* shape, int x, int y);	//���� �������� ��ǥ��
	int show_next_block(int* shape);		//�������� �� ǥ��
	int make_new_block(int* shape);
	int show_total_block();	//�׿����ִ� ���� ȭ�鿡 ǥ���Ѵ�.
	int show_gamestat();
	int move_down(int* x, int* y);
	int find_fair(int combo);		//¦�� �´°��� ã��
	int ani_del_block(int block_arr[21][10]);		//���� ���� ã������ �ִϸ��̼�
	int del_block(int block_arr[21][10], int combo);		//���� ���� ã������ �ִϸ��̼�
};
