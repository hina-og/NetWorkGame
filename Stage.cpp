#include "Stage.h"

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
	for (int y = 0; y < STAGE::HEIGHT; y++)
	{
		for (int x = 0; x < STAGE::WIDTH; x++)
		{
			if (stage[y][x] == 1)
			{
				DrawBox(x * STAGE::TILE_SIZE, y * STAGE::TILE_SIZE, x * STAGE::TILE_SIZE + STAGE::TILE_SIZE, y * STAGE::TILE_SIZE + STAGE::TILE_SIZE, GetColor(255,255,255), TRUE);
			}
			else
			{
				
			}
		}
	}
	//DrawBox(0,0,100,100, GetColor(255,0,0), TRUE);
}

void Stage::Release()
{
}
