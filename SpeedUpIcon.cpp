#include "SpeedUpIcon.h"
#include"Stage.h"
#include"Camera.h"

SpeedUpIcon::SpeedUpIcon(GameObject* parent) :Item(parent)
{
	hIcon_ = -1;
	fileName_ = "Assets//speedUpIcon.png";
	position_ = { 0,0 };
	num_ = { 0,0 };
	IsOnLoad_ = false;
	IsAlive_ = false;
}

SpeedUpIcon::~SpeedUpIcon()
{
}

void SpeedUpIcon::Initialize()
{
	hIcon_ = LoadGraph(fileName_.c_str());
	assert(hIcon_ >= 0);
	stage = GetParent()->FindGameObject<Stage>();
	cam = GetParent()->FindGameObject<Camera>();
	GetGraphSize(hIcon_, &graphSize_.x, &graphSize_.y);
}

void SpeedUpIcon::Release()
{
}
