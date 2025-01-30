#pragma once
#include "Engine/GameObject.h"
#include "Camera.h"
#include "Stage.h"

class Hunter
	: public GameObject
{
	int speed_;
	int x;
	int y;
	const int initPosX = 1280 / 2;
	const int initPosY = 720 / 2;
	int state_;

	float angle_;
	int hArrow_;
public:

	Hunter(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	bool CollisionStage(Stage* stage);
};

