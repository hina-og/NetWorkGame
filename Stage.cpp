#include "Stage.h"
#include "Camera.h"

Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage")
{
	
}

Stage::~Stage()
{
}

void Stage::Initialize()
{	
	int direction = 0;
	for (int y = 0; y < STAGE::HEIGHT; y++)
	{
		for (int x = 0; x < STAGE::WIDTH; x++)
		{
			if (x == 0 || x == STAGE::WIDTH - 1 ||
				y == 0 || y == STAGE::HEIGHT - 1)
			{
				stage[y][x] = 1;
			}
			else
			{
				if (x % 2 == 1 || y % 2 == 1)
				{
					stage[y][x] = 0;
				}
				else
				{
					stage[y][x] = 1;
				}
			}
		}
	}

	for (int y = 0; y < STAGE::HEIGHT; y++)
	{
		for (int x = 0; x < STAGE::WIDTH; x++)
		{
			if (!(x == 0 || x == STAGE::WIDTH - 1 ||
				y == 0 || y == STAGE::HEIGHT - 1) &&
				!(x % 2 == 1 || y % 2 == 1))
			{
				direction = GetRand(4);

				switch (direction)
				{
				case 0:
					stage[y - 1][x] = 1;
					break;
				case 1:
					stage[y][x - 1] = 1;
					break;
				case 2:
					stage[y + 1][x] = 1;
					break;
				case 3:
					stage[y][x + 1] = 1;
					break;
				default:
					break;
				}
			}
		}
	}
	
}

void Stage::Update()
{
	
}

void Stage::Draw()
{
	Camera* cam = (Camera*)FindObject("Camera");
	for (int y = 0; y < STAGE::HEIGHT; y++)
	{
		for (int x = 0; x < STAGE::WIDTH; x++)
		{
			if (stage[y][x] == 1)
			{
				//DrawBox(x * STAGE::TILE_SIZE, y * STAGE::TILE_SIZE, x * STAGE::TILE_SIZE + STAGE::TILE_SIZE, y * STAGE::TILE_SIZE + STAGE::TILE_SIZE, GetColor(255,255,255), TRUE);

				if (cam->isZoom_)
				{
					/*DrawBox(((x * STAGE::TILE_SIZE + cam->camX) * cam->camDist) - 1280 / 2 - 1280 / 2 / cam->camDist,
						    ((y * STAGE::TILE_SIZE + cam->camY) * cam->camDist) - 720 / 2 - 720 / 2 / cam->camDist,
							((x * STAGE::TILE_SIZE + STAGE::TILE_SIZE + cam->camX) * cam->camDist) - 1280 / 2 - 1280 / 2 / cam->camDist,
							((y * STAGE::TILE_SIZE + STAGE::TILE_SIZE + cam->camY) * cam->camDist) - 720 / 2 - 720 / 2 / cam->camDist,
						     GetColor(255, 255, 255), TRUE);*/
					//DrawBox((x * STAGE::TILE_SIZE * cam->camDist) - (1280 - 1280 / cam->camDist) + cam->camX * cam->camDist /* - 1280 / 2 - 1280 / 2 / cam->camDist*/,
					//		(y * STAGE::TILE_SIZE * cam->camDist) - (720 - 720 / cam->camDist) + cam->camY * cam->camDist /* - 720 / 2 - 720 / 2 / cam->camDist*/,
					//		(x * STAGE::TILE_SIZE * cam->camDist + STAGE::TILE_SIZE * cam->camDist) - (1280 - 1280 / cam->camDist) + cam->camX * cam->camDist /* - 1280 / 2 - 1280 / 2 / cam->camDist*/,
					//		(y * STAGE::TILE_SIZE * cam->camDist + STAGE::TILE_SIZE * cam->camDist) - (720 - 720 / cam->camDist) + cam->camY * cam->camDist /* - 720 / 2 - 720 / 2 / cam->camDist*/,
					//		GetColor(255, 255, 255), TRUE);
					
					DrawBox((x * STAGE::TILE_SIZE * cam->camDist) - 1920 + cam->camX * cam->camDist,
							(y * STAGE::TILE_SIZE * cam->camDist) - 1080 + cam->camY * cam->camDist,
						(x * STAGE::TILE_SIZE * cam->camDist + STAGE::TILE_SIZE * cam->camDist) - 1920 + cam->camX * cam->camDist,
							(y * STAGE::TILE_SIZE * cam->camDist + STAGE::TILE_SIZE * cam->camDist) - 1080 + cam->camY * cam->camDist,
							GetColor(255, 255, 255), TRUE);
					//1 :1280,720
					//2 : 640,360
					//4 ; 320,180
					//20:  64, 36
				}
				else
				{
					DrawBox(x * STAGE::TILE_SIZE, 
						    y * STAGE::TILE_SIZE,
						    x * STAGE::TILE_SIZE + STAGE::TILE_SIZE,
						    y * STAGE::TILE_SIZE + STAGE::TILE_SIZE,
						    GetColor(255, 255, 255), TRUE);
				}
			}
		}
	}
	//DrawBox(0,0,100,100, GetColor(255,0,0), TRUE);
}

void Stage::Release()
{
}
