#include "Player.h"
#include"Stage.h"
#include"Runner.h"
#include"Hunter.h"
#include"Conect.h"

Player::Player(GameObject* parent)
{
	job_ = RUNNER;
	startConect = false;
}

void Player::Initialize()
{
	switch (job_) {
	case RUNNER:
	{
		Instantiate<Runner>(GetParent());
		break;
	}
	case HUNTER:
	{
		Instantiate<Hunter>(this);
		break;
	}
	default:
		break;
	}
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		startConect = true;
	}
	if (startConect) {
		Conect* conect = new Conect();
		conect->ConnectToServer();
	}
}

void Player::Draw()
{
}

void Player::Release()
{
}
