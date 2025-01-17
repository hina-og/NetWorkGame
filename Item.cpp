#include "Item.h"
#include"Stage.h"
#include "Camera.h"

Item::Item(GameObject* parent) : GameObject(parent,"Item"),hEyeIcon_(-1),hSpeedUpIcon_(-1)
{
	hEyeIcon_ = LoadGraph("Assets//eyeIcon.png");
	assert(hEyeIcon_ >= 0);
	hSpeedUpIcon_ = LoadGraph("Assets//speedUpIcon.png");
	assert(hSpeedUpIcon_ >= 0);
	EIconPos_ = { 0,0 };
	SUIconPos_ = { 0,0 };
	IsEIOnLoad_ = false;
	IsSUIOnLoad_ = false;
	IsAliveEI_ = false;
	IsAliveSUI_ = false;

	stage = GetParent()->FindGameObject<Stage>();
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
	if (!IsAliveEI_) {
		while (!IsEIOnLoad_) {
			EInum_ = { GetRand(STAGE::WIDTH),GetRand(STAGE::HEIGHT) };
			if (stage->GetStage(EInum_.y, EInum_.x) <= 0) {
				EIconPos_ = { EInum_.x * STAGE::TILE_SIZE,EInum_.y * STAGE::TILE_SIZE };
				IsEIOnLoad_ = true;
			}
		}
	}
	if (!IsAliveSUI_) {
		while (!IsSUIOnLoad_) {
			SUInum_ = { GetRand(STAGE::WIDTH),GetRand(STAGE::HEIGHT) };
			if (stage->GetStage(SUInum_.y, SUInum_.x) <= 0) {
				SUIconPos_ = { SUInum_.x * STAGE::TILE_SIZE,SUInum_.y * STAGE::TILE_SIZE };
				IsSUIOnLoad_ = true;
			}
		}
	}
}

void Item::Draw()
{
	Camera* cam = (Camera*)FindObject("Camera");

	DrawGraph((EIconPos_.x + cam->camX) * cam->camDist, (EIconPos_.y + cam->camY) * cam->camDist, hEyeIcon_, TRUE);
	DrawGraph((SUIconPos_.x + cam->camX) * cam->camDist, (SUIconPos_.y + cam->camY) * cam->camDist, hSpeedUpIcon_, TRUE);
#if 0 //ボックス
	DrawBoxAA(0, 0, 40, 40, GetColor(255, 255, 0), FALSE);
	DrawBoxAA(40, 40, 80, 80, GetColor(255, 255, 0), FALSE);
#endif
}

void Item::Release()
{
}
