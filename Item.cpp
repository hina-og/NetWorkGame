#include "Item.h"
#include"Stage.h"
#include"Camera.h"

Item::Item(GameObject* parent) : GameObject(parent,"Item")
{
}

Item::~Item()
{
}

void Item::Initialize()
{
	hIcon_ = -1;
	hIcon_ = LoadGraph(fileName_.c_str());
	assert(hIcon_ >= 0);
	hIcon_ = -1;
	position_ = { 0,0 };
	num_ = { 0,0 };
	IsOnLoad_ = false;
	IsAlive_ = false;
	stage = GetParent()->FindGameObject<Stage>();
	cam = GetParent()->FindGameObject<Camera>();

	GetGraphSize(hIcon_, &graphSize_.x, &graphSize_.y);
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
	DrawExtendGraph(position_.x + cam->camX,position_.y + cam->camY, position_.x + cam->camX + graphSize_.x * cam->camDist, position_.y + cam->camY + graphSize_.y * cam->camDist,hIcon_, TRUE);
#if 1 //ボックス
	DrawBoxAA(position_.x + cam->camX,position_.y + cam->camY,position_.x + STAGE::TILE_SIZE + cam->camX,position_.y+STAGE::TILE_SIZE + cam->camY, GetColor(255, 255, 0), FALSE);
#endif
}

void Item::Release()
{
}

//bool Item::HitSquare(XMINT2 b1,XMINT2 b2,XMINT2 b1dis,XMINT2 b2dis)
//{
//	XMINT2 Box1Center;
//	XMINT2 Box2Center;
//	Box1Center = { b1.x + b1dis.x / 2,b1.y + b1dis.y / 2 };
//	Box2Center = { b2.x + b2dis.x / 2,b2.y + b2dis.y / 2 };
//
//
//	return false;
//}
