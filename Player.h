#pragma once
#include "Engine/GameObject.h"
#include "Client.h"
#include "Stage.h"
#include"Camera.h"
#include <vector>

class Player
	: public GameObject
{
protected:
	int state_;
	int job_;
	int speed_;
	bool player_;

	XMINT2 position_;
	XMINT2 num_;
	bool IsOnLoad_;
	bool IsAlive_;
	Stage* stage;
	Camera* cam;
	

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
public:
	void SetPlayer(bool _player) { player_ = _player; }
	auto ClinetPointer() { return client; }
};
