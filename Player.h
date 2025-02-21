#pragma once
#include "Engine/GameObject.h"
#include "Camera.h"

class Conect;

class Player
	: public GameObject
{
public:
	Player(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
private:
	int job_;
	bool startConect;
	bool isConnected;  // 接続状態を管理するフラグ
	Conect* conect;    // Conect クラスのインスタンスを持つ
};
