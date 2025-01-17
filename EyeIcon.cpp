#include "EyeIcon.h"
#include"Stage.h"
#include"Camera.h"

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
	cam = GetParent()->FindGameObject<Camera>();

	GetGraphSize(hIcon_, &graphSize_.x, &graphSize_.y);
}

void EyeIcon::Release()
{
}
