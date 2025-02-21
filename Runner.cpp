#include "Runner.h"
#include"Camera.h"
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
    Camera* cam = (Camera*)FindObject("Camera");

    int prevX = x;
    int prevY = y;
    int prevCamX = cam->camX;
    int prevCamY = cam->camY;

    if (CheckHitKey(KEY_INPUT_LEFT) || CheckHitKey(KEY_INPUT_A))
    {
        x -= speed_;
        /*cam->camX += speed_;
        if (x <= 40 * 4 + 20 && cam->overCamX < 40 * 10)
        {
            cam->overCamX += speed_;
        }*/
        if (cam->camX < 480)
        {
            cam->camX += speed_;
        }
        else
        {
            //cam->overCamX -= speed_;
            if (cam->overCamX >= 0)
            {
                cam->overCamX -= speed_;
            }
            else
            {
                cam->overCamX += speed_;
            }
        }
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) || CheckHitKey(KEY_INPUT_D))
    {
        x += speed_;
        //cam->camX -= speed_;
        if (cam->camX > -480)
        {
            cam->camX -= speed_;
        }
        else
        {
            if (cam->overCamX <= 0)
            {
                cam->overCamX -= speed_;
            }
            else
            {
                cam->overCamX += speed_;
            }
        }
    }
    if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W))
    {
        y -= speed_;
        cam->camY += speed_;
        /*if (y <= 40 * 3 + 20 && cam->overCamX < 40 * 8 + 20)
        {
            cam->overCamY += speed_;
        }*/
    }
    if (CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S))
    {
        y += speed_;
        cam->camY -= speed_;
    }
}

void Runner::Draw()
{
    Camera* cam = (Camera*)FindObject("Camera");
    DrawCircle(transform_.position_.x, transform_.position_.y, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
}

void Runner::Release()
{
}
