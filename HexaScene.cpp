#include "HexaScene.h"

void HexaScene::Init()
{
	ScoreManager::Instance()->SetScore(0);
	show_logo();
	input_data();
	int i, j;
	cur.posX = 4;
	cur.posY = -2;
	blocks = 0;
	stage_data[0].SetSpeed(40);
	stage_data[0].Setblock(60);
	stage_data[0].Setrate(8);
	stage_data[1].SetSpeed(37);
	stage_data[1].Setblock(70);
	stage_data[1].Setrate(7);
	stage_data[2].SetSpeed(33);
	stage_data[2].Setblock(75);
	stage_data[2].Setrate(6);
	stage_data[3].SetSpeed(30);
	stage_data[3].Setblock(80);
	stage_data[3].Setrate(4);
	stage_data[4].SetSpeed(27);
	stage_data[4].Setblock(90);
	stage_data[4].Setrate(2);
	stage_data[5].SetSpeed(22);
	stage_data[5].Setblock(100);
	stage_data[5].Setrate(1);
	stage_data[6].SetSpeed(18);
	stage_data[6].Setblock(110);
	stage_data[6].Setrate(1);
	stage_data[7].SetSpeed(10);
	stage_data[7].Setblock(99999);
	stage_data[7].Setrate(1);
	for (i = 0; i<21; i++)
		for (j = 0; j<10; j++)
			total_block[i][j] = 0;
	for (i = 0; i<21; i++)
	{
		total_block[i][0] = 9;
		total_block[i][9] = 9;
	}
	for (i = 0; i<10; i++)
	{
		total_block[20][i] = 9;
	}
	//랜덤 seed값 넣기
	srand((unsigned)time(NULL));

	make_new_block(cur_block);
	make_new_block(next_block);
	show_total_block();
	show_next_block(next_block);
	show_gamestat();
}

void HexaScene::Update()
{
	Utility::Gotoxy(77, 23);		//화면 잔상을 없애기 위함
	cout << " \b";

	if (Input::GetKeyDown(KeyCode::UP))
	{
		shape_tmp = cur_block[2];
		cur_block[2] = cur_block[1];
		cur_block[1] = cur_block[0];
		cur_block[0] = shape_tmp;
	}
	if (Input::GetKeyDown(KeyCode::LEFT))
	{
		if (cur.posX > 1)
		{
			if (total_block[cur.posY + 2][cur.posX - 1] == 0)
				cur.posX--;
		}
	}
	if (Input::GetKeyDown(KeyCode::RIGHT))
	{
		if (cur.posX < 8)
		{
			if (total_block[cur.posY + 2][cur.posY + 1] == 0)
				cur.posX++;
		}
	}
	if (Input::GetKeyDown(KeyCode::DOWN))
	{
		return_tmp = move_down(&cur.posX, &cur.posY);
		if (return_tmp == 1)		//블럭이 바닥에 닿았을때
		{
			if ((cur.posY < 0) && (total_block[cur.posY + 3][cur.posX] != 0))
			{
				is_gameover = 1;
			}
			else {

				find_fair(0);
				show_total_block();
				show_gamestat();
			}
		}
	}
	if (Input::GetKeyDown(KeyCode::SPACE))
	{
		return_tmp = 0;
		while (return_tmp == 0)
			return_tmp = move_down(&cur.posX, &cur.posY);

		if ((cur.posY < 0) && (total_block[cur.posY + 3][cur.posX] != 0))
		{
			is_gameover = 1;
		}
		else {

			find_fair(0);
			show_total_block();
			show_gamestat();
		}
	}

	if (i%stage_data[LevelManager::Instance()->GetLevel()].GetSpeed() == 0)
	{
		if (blocks > stage_data[LevelManager::Instance()->GetLevel()].Getblock())
			if (LevelManager::Instance()->GetLevel() < 7)
			{
				LevelManager::Instance()->SetLevel(LevelManager::Instance()->GetLevel() + 1);
				blocks = 0;
			}
		return_tmp = move_down(&cur.posX, &cur.posY);		//블럭을 이동한다.

		if (return_tmp == 1)		//블럭이 바닥에 닿았을때	
		{
			if ((cur.posY < 0) && (total_block[cur.posY + 3][cur.posX] != 0))
			{
				is_gameover = 1;
			}
			else {

				find_fair(0);
				show_total_block();
				show_gamestat();
			}
		}
		show_cur_block(cur_block, cur.posX, cur.posY);
	}
	if (is_gameover == 1)
	{
		GameWorld::Instance()->ChangeScene(new GameoverScene);
		Utility::SetColor(GRAY);
	}
	Sleep(100);
}

void HexaScene::Render()
{
	show_cur_block(blank_block, cur.posX, cur.posY);
}

void HexaScene::Release()
{
}

void HexaScene::show_logo()
{
	int i, j;
	int cur_color = 0;
	Utility::Gotoxy(13, 3);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━┓";
	Sleep(100);
	Utility::Gotoxy(13, 4);
	cout <<"┃★      ★  ★★★★★  ★      ★     ★★   ┃";
	Sleep(100);
	Utility::Gotoxy(13, 5);
	cout <<"┃★      ★  ★            ★  ★     ★    ★ ┃";
	Sleep(100);
	Utility::Gotoxy(13, 6);
	cout <<"┃★★★★★  ★★★★★      ★      ★★★★★┃";
	Sleep(100);
	Utility::Gotoxy(13, 7);
	cout <<"┃★      ★  ★            ★  ★    ★      ★┃";
	Sleep(100);
	Utility::Gotoxy(13, 8);
	cout <<"┃★      ★  ★★★★★  ★      ★  ★      ★┃";
	Sleep(100);
	Utility::Gotoxy(13, 9);
	cout <<"┗━━━━━━━━━━━━━━━━━━━━━━━┛";
	Utility::Gotoxy(13, 10);
	cout <<" Ver 0.1                         Made By Jae-Dong  ";


	Utility::Gotoxy(28, 20);
	cout << "Please Press Any Key~!";

	for (i = 0; i >= 0; i++)
	{
		if (i % 8 == 0)
		{
			Utility::Gotoxy(20, 19);
			for (j = 0; j<37; j++)
			{
				Utility::SetColor((cur_color + j) % 16 * 16);
				cout << " ";
			}
			if (cur_color >0)
				cur_color--;
			else
				cur_color = 15;
		}
		if (kbhit())
			break;
		Sleep(10);
	}

	getche();
	Utility::SetColor(GRAY);
	system("cls");
}

void HexaScene::input_data()
{
	int i = 0;
	Utility::SetColor(GRAY);
	Utility::Gotoxy(10, 7);
	cout <<"┏━━━━<GAME KEY>━━━━━┓";
	Sleep(10);
	Utility::Gotoxy(10, 8);
	cout <<"┃ UP   : Rotate Block        ┃";
	Sleep(10);
	Utility::Gotoxy(10, 9);
	cout <<"┃ DOWN : Move One-Step Down  ┃";
	Sleep(10);
	Utility::Gotoxy(10, 10);
	cout <<"┃ SPACE: Move Bottom Down    ┃";
	Sleep(10);
	Utility::Gotoxy(10, 11);
	cout <<"┃ LEFT : Move Left           ┃";
	Sleep(10);
	Utility::Gotoxy(10, 12);
	cout <<"┃ RIGHT: Move Right          ┃";
	Sleep(10);
	Utility::Gotoxy(10, 13);
	cout <<"┗━━━━━━━━━━━━━━┛";


	while (i<1 || i>8)
	{
		Utility::Gotoxy(10, 3);
		cout <<"Select Start level[1-8]:       \b\b\b\b\b\b\b";
		cin >> i;
	}


	LevelManager::Instance()->SetLevel(i - 1);
	system("cls");
}

int HexaScene::show_total_block()
{
	int i, j;
	for (i = 0; i<21; i++)
	{
		for (j = 0; j<10; j++)
		{
			Utility::Gotoxy(j * 2 + abs_x, i + abs_y);
			switch (total_block[i][j])
			{
			case 0:
				Utility::SetColor(GRAY | GRAY * 16);
				cout <<"  ";
				break;
			case 1:
				Utility::SetColor(BLUE | DARK_GRAY * 16);
				cout <<"●";
				break;
			case 2:
				Utility::SetColor(SKY_BLUE | DARK_GRAY * 16);
				cout <<"◆";
				break;
			case 3:
				Utility::SetColor(BLACK | DARK_GRAY * 16);
				cout <<"■";
				break;
			case 4:
				Utility::SetColor(GREEN | DARK_GRAY * 16);
				cout <<"♥";
				break;
			case 5:
				Utility::SetColor(RED | DARK_GRAY * 16);
				cout <<"★";
				break;
			case 9:
				Utility::SetColor(((LevelManager::Instance()->GetLevel() % 6) + 1) * 16);
				cout <<"  ";
				break;
			}
		}
	}
	return 0;
}

int HexaScene::find_fair(int combo)
{
	int fair_num = 0;
	int i = 0, j = 1, k = 0, l = 1;
	int tmp_shape;
	int tmp_x, tmp_y;
	int fair_arr[21][10];
	int is_del_block = 0;

	for (i = 0; i<21; i++)		//fair_arr 초기화
		for (j = 0; j<10; j++)
			fair_arr[i][j] = 0;

	for (i = 0; i<20; i++)			//세로
	{
		for (j = 1; j<9; j++)		//가로
		{
			tmp_shape = total_block[i][j];

			if (tmp_shape == 0)	//빈칸일경우 기준점을 다음칸으로 옮김
				continue;

			for (k = 0; k<4; k++)	//방향
			{
				tmp_y = i;
				tmp_x = j;
				fair_num = 0;
				for (l = 1; l<5; l++)	//깊이
				{
					switch (k)
					{
					case 0:		//기준점에서 왼쪽 아래 대각선 방향을
						tmp_y++;
						tmp_x--;
						break;
					case 1:		//기준점에서 아래 방향
						tmp_y++;
						break;
					case 2:		//기준점에서 오른쪽 아래 대각선 방향
						tmp_y++;
						tmp_x++;
						break;
					case 3:		//기준점에서 오른쪽 방향
						tmp_x++;
						break;
					}
					if (tmp_x <1 || tmp_x >12 || tmp_y > 20)
						break;
					if (total_block[tmp_y][tmp_x] == tmp_shape)
						fair_num++;
					else
						break;
				}
				if (fair_num >= 2)
				{
					is_del_block = 1;
					tmp_y = i;
					tmp_x = j;
					for (l = 0; l <= fair_num; l++)
					{
						fair_arr[tmp_y][tmp_x] = 1;
						switch (k)
						{
						case 0:		//기준점에서 왼쪽 아래 대각선 방향을
							tmp_y++;
							tmp_x--;
							break;
						case 1:		//기준점에서 아래 방향
							tmp_y++;
							break;
						case 2:		//기준점에서 오른쪽 아래 대각선 방향
							tmp_y++;
							tmp_x++;
							break;
						case 3:		//기준점에서 오른쪽 방향
							tmp_x++;
							break;
						}
					}
				}

			}
		}
	}
	if (is_del_block == 1)	//3개이상이 연달아 있을때
	{
		combo++;
		ani_del_block(fair_arr);
		del_block(fair_arr, combo);
		show_total_block();

		if (combo > max_combo)
			max_combo = combo;

		find_fair(combo);
		return 1;
	}
	return 0;
}

int HexaScene::ani_del_block(int block_arr[21][10])
{
	int i, j, k;

	for (k = 0; k<6; k++)
	{
		for (i = 0; i<21; i++)
		{
			for (j = 1; j<9; j++)
			{
				if (block_arr[i][j] == 0)
					continue;

				Utility::Gotoxy(j * 2 + abs_x, i + abs_y);
				switch (total_block[i][j])
				{
				case 1:
					Utility::SetColor(BLUE | (DARK_GRAY + (k % 2)) * 16);
					cout <<"●";
					break;
				case 2:
					Utility::SetColor(SKY_BLUE | (DARK_GRAY + (k % 2)) * 16);
					cout <<"◆";
					break;
				case 3:
					Utility::SetColor(BLACK | (DARK_GRAY + (k % 2)) * 16);
					cout <<"■";
					break;
				case 4:
					Utility::SetColor(GREEN | (DARK_GRAY + (k % 2)) * 16);
					cout <<"♥";
					break;
				case 5:
					Utility::SetColor(RED | (DARK_GRAY + (k % 2)) * 16);
					cout <<"★";
					break;
				}


				Sleep(24);
			}

		}

	}
	return 0;
}

int HexaScene::move_down(int* x, int* y)
{
	int j;
	if (total_block[*y + 3][*x] != 0)		//블럭이 바닥에 닿았을때
	{
		for (j = 0; j<3; j++)
			total_block[*y + j][*x] = cur_block[j];
		cur_block[0] = next_block[0];
		cur_block[1] = next_block[1];
		cur_block[2] = next_block[2];
		make_new_block(next_block);
		show_total_block();
		show_next_block(next_block);
		*x = 4;
		*y = -2;
		return 1;
	}
	else {
		(*y)++;
		return 0;
	}

}

int HexaScene::show_cur_block(int* shape, int x, int y)
{
	int i;
	for (i = 0; i<3; i++)
	{
		if (y + i <0)		//화면 위쪽의 블럭은 보여주지 않음
			continue;

		Utility::Utility::Gotoxy((x * 2) + abs_x, y + i + abs_y);
		cout <<"  \b\b";
		switch (shape[i])
		{
		case 0:
			Utility::SetColor(GRAY * 16);
			cout <<"  ";
			break;
		case 1:
			Utility::SetColor(BLUE | WHITE * 16);
			cout <<"●";
			break;
		case 2:
			Utility::SetColor(SKY_BLUE | WHITE * 16);
			cout <<"◆";
			break;
		case 3:
			Utility::SetColor(BLACK | WHITE * 16);
			cout <<"■";
			break;
		case 4:
			Utility::SetColor(GREEN | WHITE * 16);
			cout <<"♥";
			break;
		case 5:
			Utility::SetColor(RED | WHITE * 16);
			cout <<"★";
			break;
		}
	}
	return 0;
}

int HexaScene::show_next_block(int* shape)
{
	int i, j;
	//SetColor(((level+1)%6+1)|GRAY*16);
	for (i = 2; i<7; i++)
	{
		Utility::Utility::Gotoxy(28, i);
		for (j = 0; j<5; j++)
		{
			if (i == 2 || i == 6 || j == 0 || j == 4)
			{
				Utility::SetColor(((LevelManager::Instance()->GetLevel() + 1) % 6 + 1));
				cout <<"■";
			}
			else {
				Utility::SetColor(GRAY * 16);
				cout <<"  ";
			}

		}
	}
	show_cur_block(shape, 13, 1);
	return 0;
}

int HexaScene::show_gamestat()
{
	static int printed_text = 0;
	Utility::SetColor(GRAY);
	if (printed_text == 0)
	{
		Utility::Gotoxy(29, 7);
		cout << "STAGE";

		Utility::Gotoxy(29, 9);
		cout << "SCORE";

		Utility::Gotoxy(29, 12);
		cout << "BLOCKS";

		Utility::Gotoxy(29, 15);
		cout << "MAX COMBO";
	}
	Utility::Gotoxy(35, 7);
	cout << LevelManager::Instance()->GetLevel() + 1;
	Utility::Gotoxy(29, 10);
	cout << ScoreManager::Instance()->GetScore();
	Utility::Gotoxy(29, 13);
	cout << stage_data[LevelManager::Instance()->GetLevel()].Getblock() - blocks;
	Utility::Gotoxy(29, 16);
	cout << max_combo;
	return 0;
}

int HexaScene::make_new_block(int* shape)
{
	int i;
	int rtn_tmp;
	rtn_tmp = rand() % 100;
	if (stage_data[LevelManager::Instance()->GetLevel()].Getrate() > rtn_tmp)	//트리플 확률로 트리플이 나올때
	{
		rtn_tmp = rand() % 5 + 1;
		shape[0] = rtn_tmp;
		shape[1] = rtn_tmp;
		shape[2] = rtn_tmp;
		return 0;
	}
	for (i = 0; i<3; i++)
	{
		shape[i] = rand() % 5 + 1;
	}
	return 0;
}

int HexaScene::del_block(int block_arr[21][10], int combo)
{
	int i, j, k;
	int block_num = 0;		//없애는 블럭의 개수
	for (i = 19; i >= 0; i--)
	{
		for (j = 1; j<9; j++)
		{

			if (block_arr[i][j] == 1)
			{
				total_block[i][j] = 0;
				block_num++;
				blocks++;

			}

		}
	}
	for (i = 0; i<20; i++)
	{
		for (j = 1; j<9; j++)
		{
			if (total_block[i][j] != 0)
				continue;

			for (k = i; k >= 0; k--)	//블럭을비운 빈공간을 위에 있는 블럭으로 채운다.
			{
				if (k == 0)
				{
					total_block[k][j] = 0;

				}
				else {
					total_block[k][j] = total_block[k - 1][j];

				}
			}

		}
	}

	//점수 계산
	ScoreManager::Instance()->SetScore(ScoreManager::Instance()->GetScore() + combo*1.3*(block_num * 12));
	return 0;
}