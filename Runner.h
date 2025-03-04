#pragma once
#include "Player.h"

class Runner
	: public Player
{
	const int initPosX = 1280 / 2 - 20;
	const int initPosY = 720 / 2 - 20;

	

	float angle_;

	bool IsOnLoad_;
public:
	Runner(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

