#include "Runner.h"
#include "Stage.h"

Runner::Runner(GameObject* parent)
{
    speed_ = 2;
    x = initPosX;
    y = initPosY;

    state_ = CANLOOK;
}

void Runner::Initialize()
{
}

void Runner::Update()
{
    int prevX = x;
    int prevY = y;

    if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
    {
        x -= speed_;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
    {
        x += speed_;
    }
    if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
    {
        y -= speed_;
    }
    if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
    {
        y += speed_;
    }
}

void Runner::Draw()
{
    DrawCircle(transform_.position_.x, transform_.position_.y, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
}

void Runner::Release()
{
}
