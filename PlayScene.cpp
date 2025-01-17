#include "PlayScene.h"
#include "Camera.h"
#include "Stage.h"
#include "Hunter.h"
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
	Instantiate<Hunter>(this);
	/*Instantiate<Item>(this);*/
	//Instantiate<EyeIcon>(this);
	//Instantiate<SpeedUpIcon>(this);
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
