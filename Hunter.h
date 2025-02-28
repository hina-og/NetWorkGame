#pragma once
#include "Player.h"



class Hunter
	: public Player
{
	int speed_;

	const int initPosX = 1280 /2;
	const int initPosY = 720 / 2 ;
	int state_;

	float angle_;
	float rate_;
	int hArrow_;

	float DirectionCalculation(XMFLOAT3 _position);

public:
	Hunter(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;


};