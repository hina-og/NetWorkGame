#include "Hunter.h"
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
    rate_ = 1.0f;
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
    

    client->SetPlayerData(pData);
    client->Connect();
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

float Hunter::DirectionCalculation(XMFLOAT3 _position)
{
    // プレイヤー位置と自分の位置を取得
    XMFLOAT2 p1, p2;
    transform_.position_ = { (float)(transform_.position_.x), (float)(transform_.position_.y) , 0.0f };
    p1 = { _position.x, _position.y };
    p2 = { 1.0, 0.0 };

    // ベクトル計算
    VECTOR v1 = { p1.x - transform_.position_.x, p1.y - transform_.position_.y, 0.0f };
    VECTOR v2 = { p2.x - transform_.position_.x, p2.y - transform_.position_.y , 0.0f };

    // ベクトル正規化
    v1 = VNorm(v1);
    v2 = VNorm(v2);

    // 角度計算 (ラジアンを度に変換)
    float angleRad = atan2(v1.y, v1.x);
    return angleRad;
}

