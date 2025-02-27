#include "Player.h"
#include"Stage.h"
#include"Runner.h"
#include"Hunter.h"
#include"Conect.h"

//#include<ws2tcpip.h> 
//#include <WS2tcpip.h>
//#pragma comment( lib, "ws2_32.lib" )



Player::Player(GameObject* parent)
{
	job_ = RUNNER;
	startConect = false;
	conect = new Conect("192.168.43.1", 8888);
	conect->InitializeSocket();
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
	//if (CheckHitKey(KEY_INPUT_RETURN)) {
	//	startConect = true;
	//}
	//if (startConect) {
	//	Conect* conect = new Conect("192.168.42.23",8888);
	//	conect->ConnectToServer();
	//}
	
	conect->ConnectToServer();
}

void Player::Draw()
{
}

void Player::Release()
{
}
