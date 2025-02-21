#include "Camera.h"

Camera::Camera(GameObject* parent)
	: GameObject(parent, "Camera")
{
	
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	camX = 0;
	camY = 0;
	overCamX = 0;
	overCamY = 0;
	camDist = 1;//ズーム倍率
	isZoom_ = false;
}

void Camera::Update()
{
	//　　いったんズームなし

	/*if (CheckHitKey(KEY_INPUT_J))
	{
		camDist = 1;
		isZoom_ = false;
	}
	if (CheckHitKey(KEY_INPUT_K))
	{
		camDist = 4;
		isZoom_ = true;
	}*/
}

void Camera::Draw()
{
}

void Camera::Release()
{
}
