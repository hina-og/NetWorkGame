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
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		camX += 2;
		//x -= 5;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		camX -= 2;
		//x += 5;
	}
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		camY += 2;
		//y -= 5;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		camY -= 2;
		//y += 5;
	}
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
