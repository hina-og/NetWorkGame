#include "Player.h"
#include"Stage.h"

Player::Player(GameObject* parent)
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
}

void Player::Draw()
{
	Camera* cam = (Camera*)FindObject("Camera");
	DrawCircle(x , y , STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
}

void Player::Release()
{
}
