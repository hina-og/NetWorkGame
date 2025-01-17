#include "Hunter.h"
#include "Camera.h"

Hunter::Hunter(GameObject* parent)
{
	
}

void Hunter::Initialize()
{
	x = initPosX;
	y = initPosY;
}

void Hunter::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		x -= 5;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		x += 5;
	}
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		y -= 5;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		y += 5;
	}
}

void Hunter::Draw()
{
	Camera* cam = (Camera*)FindObject("Camera");
	DrawCircle(initPosX, initPosY, 20 * cam->camDist, GetColor(255, 0, 0), TRUE);
}

void Hunter::Release()
{
}