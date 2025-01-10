#pragma once
#include "Engine/GameObject.h"

class Hunter
	: public GameObject
{
	int x = 100;
	int y = 100;
public:
	Hunter(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};

