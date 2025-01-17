#include "EyeIcon.h"
#include"Stage.h"
#include"Camera.h"

EyeIcon::EyeIcon(GameObject* parent) : Item(parent)
{
	hIcon_ = -1;
	fileName_ = "Assets//eyeIcon.png";
	position_ = { 0,0 };
	num_ = { 0,0 };
	IsOnLoad_ = false;
	IsAlive_ = false;
}

void EyeIcon::Initialize()
{
	hIcon_ = LoadGraph(fileName_.c_str());
	assert(hIcon_ >= 0);
	stage = GetParent()->FindGameObject<Stage>();
	cam = GetParent()->FindGameObject<Camera>();
	GetGraphSize(hIcon_, &graphSize_.x, &graphSize_.y);
}

EyeIcon::~EyeIcon()
{
}

void EyeIcon::Release()
{
}
