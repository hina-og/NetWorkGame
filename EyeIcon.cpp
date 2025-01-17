#include "EyeIcon.h"
#include"Stage.h"

EyeIcon::EyeIcon(GameObject* parent) : Item(parent)
{
	hIcon_ = -1;
}

EyeIcon::~EyeIcon()
{
}

void EyeIcon::Initialize()
{
	hIcon_ = LoadGraph("Assets//eyeIcon.png");
	assert(hIcon_ >= 0);
	position_ = { 0,0 };
	num_ = { 0,0 };
	IsOnLoad_ = false;
	IsAlive_ = false;
	stage = GetParent()->FindGameObject<Stage>();
}

void EyeIcon::Update()
{
	if (!IsAlive_) {
		while (!IsOnLoad_) {
			num_ = { GetRand(STAGE::WIDTH),GetRand(STAGE::HEIGHT) };
			if (stage->GetStage(num_.y, num_.x) <= 0) {
				position_ = { num_.x * STAGE::TILE_SIZE,num_.y * STAGE::TILE_SIZE };
				IsOnLoad_ = true;
			}
		}
	}
}

void EyeIcon::Release()
{
}
