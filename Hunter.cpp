#include "Hunter.h"
#include "Camera.h"
#include "Stage.h"


Hunter::Hunter(GameObject* parent)
{
	
}

void Hunter::Initialize()
{
	speed_ = 2;
	x = initPosX;
	y = initPosY;
}

void Hunter::Update()
{
	Camera* cam = (Camera*)FindObject("Camera");

	if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
	{
		cam->camX += speed_;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
	{
		cam->camX -= speed_;
	}
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
	{
		cam->camY += speed_;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
	{
		cam->camY -= speed_;
	}

}

void Hunter::Draw()
{
	Camera* cam = (Camera*)FindObject("Camera");
	DrawCircle(initPosX, initPosY, STAGE::TILE_SIZE / 2 * cam->camDist, GetColor(255, 0, 0), TRUE);
}

void Hunter::Release()
{
}