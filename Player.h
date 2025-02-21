#pragma once
#include "Engine/GameObject.h"
#include "Camera.h"

class Player
	: public GameObject
{
public:
	Player(GameObject* parent);
	~Player();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
private:
	int job_;
};
