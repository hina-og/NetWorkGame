#pragma once
#include "Engine/GameObject.h"

class Hunter
	: public GameObject
{
	int x = 100;
	int y = 100;
public:
	Hunter(GameObject* parent);

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;
};

