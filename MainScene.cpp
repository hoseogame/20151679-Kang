#include "MainScene.h"

void MainScene::Init() // �ٽ� �����Ǹ� ���ϵ��� �ϴ� �������� ��� Ű����
{
}

void MainScene::Update()
{
	system("cls");
	cout << "���ϴ� ������ �̸��� �Է����ּ��� : ";
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