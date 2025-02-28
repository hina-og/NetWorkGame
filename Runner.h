#pragma once
#include "Engine/GameObject.h"
#include "Player.h"

class Runner
	: public GameObject
{
	int speed_;
	int x;
	int y;
	const int initPosX = 1280 / 2;
	const int initPosY = 720 / 2;
	int state_;

	float angle_;

	XMINT2 num_;
	bool IsOnLoad_;
public:
	Runner(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

