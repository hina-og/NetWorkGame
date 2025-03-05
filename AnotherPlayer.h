#pragma once
#include "Engine//GameObject.h"
#include<vector>
#include"Runner.h"
#include"Hunter.h"

class PlayScene;

using std::vector;

class AnotherPlayer :
    public GameObject
{
public:
	AnotherPlayer(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	auto GetpRunners() { return pRunners_; }
	auto GetpHunnter() { return pHunter_; }
private:
	bool ImHunter_;
	PlayScene* pPScene_;
	vector<Runner*> pRunners_;
	Hunter* pHunter_;
};

