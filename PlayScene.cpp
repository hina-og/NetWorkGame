#include "PlayScene.h"
#include "Camera.h"
#include "Stage.h"
#include "Hunter.h"
#include "Runner.h"
//#include"Player.h"
#include"Item.h"
#include"EyeIcon.h"
#include"SpeedUpIcon.h"

const int MAX_PLAYERS = 1;

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	job_ = 1;//0:Hunter
}

void PlayScene::Initialize()
{
	Instantiate<Camera>(this);
	Instantiate<Stage>(this);

	if (job_)
	{
		Instantiate<Runner>(this);
	}
	else
	{
		Instantiate<Hunter>(this);
	}

	for (int i = 0; i < MAX_PLAYERS; i++) {
		Runner* pRunner = Instantiate<Runner>(this);
		/*pRunner->SetPosition();*/
	}

	/*Instantiate<Item>(this);*/
	for (int i = 0; i < 5; i++) {
		Instantiate<EyeIcon>(this);
		Instantiate<SpeedUpIcon>(this);
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
