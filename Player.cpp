#include "Player.h"
#include"Stage.h"

//#include<ws2tcpip.h> 
//#include <WS2tcpip.h>
//#pragma comment( lib, "ws2_32.lib" )



Player::Player(GameObject* parent)
{
	
	
}

Player::~Player()
{
	
}

void Player::Initialize()
{
}

void Player::Update()
{
	Stage* stage = GetParent()->FindGameObject<Stage>();
	while (!IsOnLoad_) {
		num_ = { GetRand(STAGE::WIDTH),GetRand(STAGE::HEIGHT) };
		if (stage->GetStage(num_.y, num_.x) <= 0) {
			x = num_.x * STAGE::TILE_SIZE;
			y = num_.y* STAGE::TILE_SIZE;
			IsOnLoad_ = true;
		}
	}
	transform_.position_ = { (float)x,(float)y ,0 };




	
}

void Player::Draw()
{
	
	Camera* cam = (Camera*)FindObject("Camera");
	DrawCircle(transform_.position_.x , transform_.position_.y , STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
}

void Player::Release()
{
}
