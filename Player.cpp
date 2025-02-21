#include "Player.h"
#include"Stage.h"
#include"Runner.h"
#include"Hunter.h"

//#include<ws2tcpip.h> 
//#include <WS2tcpip.h>
//#pragma comment( lib, "ws2_32.lib" )



Player::Player(GameObject* parent)
{
	job_ = RUNNER;
}

Player::~Player()
{
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
