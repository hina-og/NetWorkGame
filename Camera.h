#pragma once
#include "Engine/GameObject.h"

class Camera
	: public GameObject
{
public:
	int camX;
	int camY;
	int overCamX;
	int overCamY;
	int camDist;
	bool isZoom_;

	Camera(GameObject* parent);
	~Camera();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};