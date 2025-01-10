#include "TitleScene.h"
#include "Hunter.h"

TitleScene::TitleScene(GameObject* parent)
{
	
}

void TitleScene::Initialize()
{
	Instantiate<Hunter>(this);
}

void TitleScene::Update()
{
}

void TitleScene::Draw()
{
	//DrawCircle(100, 100, 20, GetColor(255, 0, 0), TRUE);
}

void TitleScene::Release()
{
}
