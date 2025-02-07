#include "Player.h"
#include"Stage.h"
#include"Runner.h"
#include"Hunter.h"

Player::Player(GameObject* parent)
{
	job_ = RUNNER;
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
}

void Player::Draw()
{
}

void Player::Release()
{
}
