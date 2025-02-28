#include "Runner.h"
#include "Stage.h"

Runner::Runner(GameObject* parent)
{
    objectName_ = "Runner";
    speed_ = 2;
    transform_.position_.x = initPosX;
    transform_.position_.y = initPosY;

    state_ = CANLOOK;
}

void Runner::Initialize()
{
}

void Runner::Update()
{
    int prevX = transform_.position_.x;
    int prevY = transform_.position_.y;

    if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
    {
        transform_.position_.x -= speed_;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
    {
        transform_.position_.x += speed_;
    }
    if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
    {
        transform_.position_.y -= speed_;
    }
    if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
    {
        transform_.position_.y += speed_;
    }
}

void Runner::Draw()
{
    DrawCircle(transform_.position_.x, transform_.position_.y, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
}

void Runner::Release()
{
}
