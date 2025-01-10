#include "Item.h"

Item::Item(GameObject* parent) : GameObject(parent,"Item"),hEyeIcon_(-1),hSpeedUpIcon_(-1)
{
	hEyeIcon_ = LoadGraph("Assets//eyeIcon.png");
	assert(hEyeIcon_ >= 0);
	hSpeedUpIcon_ = LoadGraph("Assets//speedUpIcon.png");
	assert(hSpeedUpIcon_ >= 0);
}

Item::~Item()
{
	if (hEyeIcon_ >= 0) {
		DeleteGraph(hEyeIcon_);
		hEyeIcon_ = -1;
	}
	if (hSpeedUpIcon_ >= 0) {
		DeleteGraph(hSpeedUpIcon_);
		hSpeedUpIcon_ = -1;
	}
}

void Item::Initialize()
{
}

void Item::Update()
{
}

void Item::Draw()
{
	DrawGraph(0, 0, hEyeIcon_, TRUE);
	DrawGraph(0, 0, hSpeedUpIcon_, TRUE);
}

void Item::Release()
{
}
