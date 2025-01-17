#pragma once
#include "Engine/GameObject.h"
#include "Camera.h"

//struct PlayerData
//{
//	
//};

class Hunter
	: public GameObject
{
	int speed_;
	int x;
	int y;
	const int initPosX = 1280 / 2;
	const int initPosY = 720 / 2;
public:
	Hunter(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

