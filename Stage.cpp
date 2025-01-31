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
    for (int y = 0; y < STAGE::HEIGHT; y++)
    {
        for (int x = 0; x < STAGE::WIDTH; x++)
        {
            if (x == 0 || x == STAGE::WIDTH - 1 || y == 0 || y == STAGE::HEIGHT - 1)
            {
                stage[y][x] = 1;
            }
            else
            {
                stage[y][x] = 0;
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
    if (cam == nullptr) return;

    /*for (int y = 0; y < STAGE::HEIGHT; y++)
    {
        for (int x = 0; x < STAGE::WIDTH; x++)
        {
            if (stage[y][x] == 1)
            {
                if (cam->isZoom_)
                {
                    DrawBox((x * STAGE::TILE_SIZE * cam->camDist) - 1920 + cam->camX * cam->camDist,
                        (y * STAGE::TILE_SIZE * cam->camDist) - 1080 + cam->camY * cam->camDist,
                        (x * STAGE::TILE_SIZE * cam->camDist + STAGE::TILE_SIZE * cam->camDist) - 1920 + cam->camX * cam->camDist,
                        (y * STAGE::TILE_SIZE * cam->camDist + STAGE::TILE_SIZE * cam->camDist) - 1080 + cam->camY * cam->camDist,
                        GetColor(255, 255, 255), TRUE);
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
    }*/
}

void Stage::Release()
{
}

int Stage::GetTile(int y, int x)
{
    if (x < 0 || x >= STAGE::WIDTH || y < 0 || y >= STAGE::HEIGHT)
    {
        return -1;
    }
    return stage[y][x];
}