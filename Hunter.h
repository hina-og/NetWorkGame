#pragma once
#include "Engine/GameObject.h"

class Hunter
	: public GameObject
{
	int x = 70;
	int y = 70;
public:
	Hunter(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};

