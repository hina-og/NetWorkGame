#pragma once
#include "Engine/GameObject.h"
#include "Client.h"
#include "Stage.h"
#include <vector>

class Player
	: public GameObject
{
protected:
	int state_;
	int job_;
	int speed_;

	

	std::vector<PLAYER> prevPlayerList;
	std::vector<PLAYER> playerList;
	PLAYER pData;
	Client* client;


	float DirectionCalculation(XMFLOAT3 _position);
	bool CollisionStage(Stage* stage);
	bool CollisionStageX(Stage* stage, int _x1, int _x2);
	bool CollisionStageY(Stage* stage, int _x1, int _x2);

public:
	bool me;//©•ª‚ª‘€ì‚·‚éƒLƒƒƒ‰‚©‚Ç‚¤‚©
	void SetData(PLAYER _pData);
};
