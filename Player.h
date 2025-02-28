#pragma once
#include "Engine/GameObject.h"
#include "Client.h"
#include "Stage.h"

//class Conect;

class Player
	: public GameObject
{
	int job_;
	bool startConect;
	bool isConnected;  // �ڑ���Ԃ��Ǘ�����t���O
	//Conect* conect;    // Conect �N���X�̃C���X�^���X������

protected:
	PLAYER pData;
	Client* client;

	bool CollisionStage(Stage* stage);
	bool CollisionStageX(Stage* stage, int _x1, int _x2);
	bool CollisionStageY(Stage* stage, int _x1, int _x2);
};
