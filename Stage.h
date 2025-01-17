#pragma once
#include "Engine/GameObject.h"


namespace STAGE
{
	const int HEIGHT = 18;
	const int WIDTH = 32;
	const int TILE_SIZE = 40;
};

class Stage
	: public GameObject
{
	int stage[STAGE::HEIGHT][STAGE::WIDTH];
public:
	Stage(GameObject* parent);
	~Stage();

	//‰Šú‰»
	void Initialize() override;

	//XV
	void Update() override;

	//•`‰æ
	void Draw() override;

	//ŠJ•ú
	void Release() override;

	int GetStage(int _y,int _x) { return stage[_y][_x]; }

	
};

