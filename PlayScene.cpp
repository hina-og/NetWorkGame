#include "PlayScene.h"
#include "Camera.h"
#include "Stage.h"
#include "Hunter.h"
#include "Runner.h"
//#include"Player.h"
#include"Item.h"
#include"EyeIcon.h"
#include"SpeedUpIcon.h"
#include"AnotherPlayer.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
	job_ = 0;//0:Hunter
}

void PlayScene::Initialize()
{
	Instantiate<Camera>(this);
	Instantiate<Stage>(this);

	if (job_)
	{
		Runner* pRunner = Instantiate<Runner>(this);
		pRunner->SetPlayer(true);
	}
	else
	{
		Hunter* pHunter = Instantiate<Hunter>(this);
		pHunter->SetPlayer(true);
	}

	//for (int i = 0; i < MAX_PLAYERS; i++) {
	//	Runner* pRunner = Instantiate<Runner>(this);
	//	/*pRunner->SetPosition();*/
	//}

	/*AnotherPlayer* pAnotherPlayer = Instantiate<AnotherPlayer>(this);*/

	

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
