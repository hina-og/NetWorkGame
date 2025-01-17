#include "Item.h"
#include"Stage.h"
#include"Camera.h"

Item::Item(GameObject* parent) : GameObject(parent,"Item")
{

	stage = GetParent()->FindGameObject<Stage>();
	cam = GetParent()->FindGameObject<Camera>();
}

Item::~Item()
{
}

void Item::Initialize()
{
}

void Item::Update()
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

void Item::Draw()
{
	DrawExtendGraph(position_.x,position_.y, position_.x + 32 * cam->camDist, position_.y + 32 * cam->camDist,hIcon_, TRUE);
#if 0 //ボックス
	DrawBoxAA(0, 0, 40, 40, GetColor(255, 255, 0), FALSE);
	DrawBoxAA(40, 40, 80, 80, GetColor(255, 255, 0), FALSE);
#endif
}

void Item::Release()
{
}
