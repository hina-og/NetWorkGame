#include "Player.h"
#include "Stage.h"
#include "Runner.h"
#include "Hunter.h"
//#include "Conect.h"

//#include<ws2tcpip.h> 
//#include <WS2tcpip.h>
//#pragma comment( lib, "ws2_32.lib" )


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


bool Player::CollisionStage(Stage* stage)
{
    int tileX = transform_.position_.x / STAGE::TILE_SIZE;
    int tileY = transform_.position_.y / STAGE::TILE_SIZE;

    //if (tileX < 0 || tileX >= STAGE::WIDTH || tileY < 0 || tileY >= STAGE::HEIGHT)
    //{
    //    return false;
    //}

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
