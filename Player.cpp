#include "Player.h"
#include "Stage.h"
#include "Runner.h"
#include "Hunter.h"

//void Player::Initialize()
//{
//	switch (job_) {
//	case RUNNER:
//	{
//		Instantiate<Runner>(this);
//		break;
//	}
//	case HUNTER:
//	{
//		Instantiate<Hunter>(this);
//		break;
//	}
//	default:
//		break;
//	}
//}

float Player::DirectionCalculation(XMFLOAT3 _position)
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

bool Player::CollisionStage(Stage* stage)
{
    int tileX = transform_.position_.x / STAGE::TILE_SIZE;
    int tileY = transform_.position_.y / STAGE::TILE_SIZE;

    return stage->IsWall(tileY, tileX) == 1;
}

bool Player::CollisionStageX(Stage* stage, int _x1, int _x2)
{
    int tileX = (_x1 - STAGE::TILE_SIZE / 2) / STAGE::TILE_SIZE;
    int tileY = transform_.position_.y / STAGE::TILE_SIZE;

    if (stage->IsWall(tileY, tileX))
    {
        return true;
    }

    tileX = _x2 / STAGE::TILE_SIZE;
    if (stage->IsWall(tileY, tileX))
    {
        return true;
    }
    return false;
}

bool Player::CollisionStageY(Stage* stage, int _y1, int _y2)
{
    int tileX = transform_.position_.x / STAGE::TILE_SIZE;
    int tileY = (_y1 - STAGE::TILE_SIZE / 2) / STAGE::TILE_SIZE;

    if (stage->IsWall(tileY, tileX))
    {
        return true;
    }
    tileX = transform_.position_.x / STAGE::TILE_SIZE;
    tileY = _y2 / STAGE::TILE_SIZE;
    if (stage->IsWall(tileY, tileX))
    {
        return true;
    }
    return false;
}
