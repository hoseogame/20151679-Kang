#include "MainScene.h"

void MainScene::Init() // 다시 재정의를 못하도록 하는 셀러리드 라는 키워드
{
}

void MainScene::Update()
{
	system("cls");
	cout << "원하는 게임의 이름을 입력해주세요 : ";
	cin >> message;
	if(message == "snake")
		GameWorld::Instance()->ChangeScene(new GameScene());
	else if(message == "hexa")
		GameWorld::Instance()->ChangeScene(new HexaScene());
}

void MainScene::Render()
{
}

void MainScene::Release()
{
}