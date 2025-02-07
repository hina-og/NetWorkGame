#pragma once
#include "Engine/GameObject.h"
#include "Camera.h"
#include "Stage.h"

struct Point
{
	int x_;
	int y_;
};

class Hunter
	: public GameObject
{
	int speed_;
	int x;
	int y;

	Point position;

	const int initPosX = 1280 / 2;
	const int initPosY = 720 / 2 ;
	int state_;

	float angle_;
	float rate_;
	int hArrow_;
public:

	Hunter(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	bool CollisionStage(Stage* stage);
	bool CollisionStageX(Stage* stage, int _x1, int _x2);
	bool CollisionStageY(Stage* stage, int _y1, int _y2);
};

