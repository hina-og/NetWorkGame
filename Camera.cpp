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
	camDist = 1;
}

void Camera::Update()
{
	if (CheckHitKey(KEY_INPUT_J))
	{
		camDist = 1;
	}
	if (CheckHitKey(KEY_INPUT_K))
	{
		camDist = 5;
	}
}

void Camera::Draw()
{
}

void Camera::Release()
{
}
