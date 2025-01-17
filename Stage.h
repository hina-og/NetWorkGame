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

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	int GetStage(int _y,int _x) { return stage[_y][_x]; }

	
};

