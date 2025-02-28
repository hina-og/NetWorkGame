#include "PlayScene.h"
#include "Camera.h"
#include "Stage.h"
#include "Hunter.h"
//#include"Player.h"
#include"Item.h"
#include"EyeIcon.h"
#include"SpeedUpIcon.h"


PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Camera>(this);
	Instantiate<Stage>(this);
	//Instantiate<Player>(this);
	Instantiate<Hunter>(this);
	/*Instantiate<Item>(this);*/
	for (int i = 0; i < 5; i++) {
		//Instantiate<EyeIcon>(this);
		//Instantiate<SpeedUpIcon>(this);
	}
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
