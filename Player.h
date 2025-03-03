#pragma once
#include "Engine/GameObject.h"
#include "Client.h"
#include "Stage.h"

class Player
	: public GameObject
{
protected:
	int state_;
	int job_;
	int speed_;

	PLAYER pData;
	Client* client;


	float DirectionCalculation(XMFLOAT3 _position);
	bool CollisionStage(Stage* stage);
	bool CollisionStageX(Stage* stage, int _x1, int _x2);
	bool CollisionStageY(Stage* stage, int _x1, int _x2);
};
