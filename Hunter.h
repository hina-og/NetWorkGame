#pragma once
#include "Engine/GameObject.h"

class Hunter
	: public GameObject
{
	int x = 100;
	int y = 100;
public:
	Hunter(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

