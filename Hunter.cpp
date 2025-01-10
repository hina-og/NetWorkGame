#include "Hunter.h"

Hunter::Hunter(GameObject* parent)
{
}

void Hunter::Initialize()
{
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

	if (x < 20)
	{
		x = 20;
	}
	if(x > 1260)
	{
		x = 1260;
	}
	if (y < 20)
	{
		y = 20;
	}
	if (y > 700)
	{
		y = 700;
	}
}

void Hunter::Draw()
{
	DrawCircle(x, y, 20, GetColor(255, 0, 0), TRUE);
}

void Hunter::Release()
{
}
