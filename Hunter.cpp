﻿#include "Hunter.h"
#include "Stage.h"
#include "Runner.h"
#include <cmath>  // acos, PI などを使うために必要
#include<algorithm>
#include<numbers>

#define PI    3.1415926535897932384626433832795f

Hunter::Hunter(GameObject* parent)
{
    objectName_ = "Hunter";

    client = new Client();

}

void Hunter::Initialize()
{
    hArrow_ = LoadGraph("Assets//arrow.png");
    assert(hArrow_ >= 0);
    speed_ = 2;

    transform_.position_.x = initPosX;
    transform_.position_.y = initPosY;

    state_ = CANLOOK;
}

void Hunter::Update()
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

    Runner* pRunner = GetParent()->FindGameObject<Runner>();
    if(pRunner != nullptr)
        angle_ = DirectionCalculation(pRunner->GetPosition());

    // ステージとの当たり判定のチェック
    Stage* stage = (Stage*)FindObject("Stage");

    if (CollisionStageX(stage, transform_.position_.x, transform_.position_.x + STAGE::TILE_SIZE / 2))
    {
        transform_.position_.x = prevX;
    }
    if (CollisionStageY(stage, transform_.position_.y, transform_.position_.y + STAGE::TILE_SIZE / 2))
    {
        transform_.position_.y = prevY;
    }
    pData.job = 0;
    pData.x = transform_.position_.x;
    pData.y = transform_.position_.y;
    pData.state = 1;

    client->SetSendData(pData);
    client->Connect();
    client->SetPlayerData(pData);
}

void Hunter::Draw()
{
    switch (state_)
    {
    case NONE:
    {
        break;
    }
    case SPEEDUP:
    {
        break;
    }
    case CANLOOK:
    {
        DrawRotaGraph(transform_.position_.x - STAGE::TILE_SIZE, transform_.position_.y - STAGE::TILE_SIZE, 1.0, angle_, hArrow_, TRUE, FALSE);
        break;
    }
    default:
        break;
    }
    DrawCircle(transform_.position_.x, transform_.position_.y, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
    DrawBox(transform_.position_.x - STAGE::TILE_SIZE / 2 + 1, transform_.position_.y - STAGE::TILE_SIZE / 2 + 1, transform_.position_.x + STAGE::TILE_SIZE / 2, transform_.position_.y + STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), FALSE);
}

void Hunter::Release()
{
    delete client;
}

