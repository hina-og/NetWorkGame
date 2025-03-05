#include "AnotherPlayer.h"
#include"PlayScene.h"

AnotherPlayer::AnotherPlayer(GameObject* parent) : GameObject(parent,"AnotherPlayer")
{
	ImHunter_ = false;
}

void AnotherPlayer::Initialize()
{
	pPScene_ = (PlayScene*)FindObject("PlayScene");
	ImHunter_ = pPScene_->Getjob();

	if (ImHunter_) {
		for (int i = 0; i < MAX_PLAYERS - 1; i++) {
			Runner* pRunner = Instantiate<Runner>(this);
			pRunner->SetPlayer(false);
			pRunners_.push_back(pRunner);
		}
	}
	else {
		pHunter_ = Instantiate<Hunter>(this);
		pHunter_->SetPlayer(false);
		for (int i = 0; i < MAX_PLAYERS - 2; i++) {
			Runner* pRunner = Instantiate<Runner>(this);
			pRunner->SetPlayer(false);
			pRunners_.push_back(pRunner);
		}
	}
}

void AnotherPlayer::Update()
{
	/*size_t index = 1;
	for (auto itr : pRunners_) {
		itr->SetPosition(pData[index].x, pData[index].y, 0));
	    index++;
	}*/
}

void AnotherPlayer::Draw()
{
}

void AnotherPlayer::Release()
{
}
