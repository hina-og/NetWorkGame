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
	bool isConnected;  // �ڑ���Ԃ��Ǘ�����t���O
	Conect* conect;    // Conect �N���X�̃C���X�^���X������
};
