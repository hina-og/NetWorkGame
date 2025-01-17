#include "SpeedUpIcon.h"
#include"Stage.h"
#include"Camera.h"

SpeedUpIcon::SpeedUpIcon(GameObject* parent) :Item(parent)
{
	hIcon_ = -1;
}

SpeedUpIcon::~SpeedUpIcon()
{
}

void SpeedUpIcon::Initialize()
{
	hIcon_ = LoadGraph("Assets//speedUpIcon.png");
	assert(hIcon_ >= 0);
	position_ = { 0,0 };
	num_ = { 0,0 };
	IsOnLoad_ = false;
	IsAlive_ = false;
	stage = GetParent()->FindGameObject<Stage>();

	GetGraphSize(hIcon_, &graphSize_.x, &graphSize_.y);
}

void SpeedUpIcon::Release()
{
}
