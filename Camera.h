#pragma once
#include "Engine/GameObject.h"

const int CameraWidth{ 320 };
const int CameraHeight{ 200 };
class Camera
	: public GameObject
{
public:
	int camX;
	int camY;
	int overCamX;//マップ外が表示されないようにする変数
	int overCamY;//マップ外が表示されないようにする変数
	int camDist;
	bool isZoom_;

	Camera(GameObject* parent);
	~Camera();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};