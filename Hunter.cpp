#include "Hunter.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"
#include <cmath>  // acos, PI などを使うために必要
#include<algorithm>
#include<numbers>

#define PI    3.1415926535897932384626433832795f

Hunter::Hunter(GameObject* parent)
	: GameObject(parent, "Hunter"), x(0), y(0)
{
}

void Hunter::Initialize()
{
    hArrow_ = LoadGraph("Assets//arrow.png");
    assert(hArrow_ >= 0);
    speed_ = 2;
    x = initPosX;
    y = initPosY;

    state_ = CANLOOK;
}

void Hunter::Update()
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

    // プレイヤー位置と自分の位置を取得
    XMFLOAT2 p1, p2;
    transform_.position_ = { (float)(x - cam->camX), (float)(y - cam->camY) , 0.0f };
    Player* pPlayer = GetParent()->FindGameObject<Player>();
    p1 = { pPlayer->GetPosition().x, pPlayer->GetPosition().y };
    p2 = { 1.0, 0.0 };

    // ベクトル計算
    VECTOR v1 = { p1.x - transform_.position_.x, p1.y - transform_.position_.y, 0.0f };
    VECTOR v2 = { p2.x - transform_.position_.x, p2.y - transform_.position_.y , 0.0f };

    // ベクトル正規化
    v1 = VNorm(v1);
    v2 = VNorm(v2);

    // 角度計算 (ラジアンを度に変換)
    float angleRad = atan2(v1.y, v1.x);
    angle_ = angleRad;
    rate_ = 1.0f;

    // ステージとの当たり判定のチェック
    Stage* stage = (Stage*)FindObject("Stage");
    if (stage != nullptr && CollisionStage(stage))
    {
        // 壁に衝突した場合の処理
        x = prevX;
        y = prevY;
        cam->camX = prevCamX;
        cam->camY = prevCamY;
    }
    
}

void Hunter::Draw()
{
    Camera* cam = (Camera*)FindObject("Camera");
    if (cam == nullptr) return;

    if (cam->isZoom_)
    {
        DrawCircle(initPosX - cam->overCamX, initPosY - cam->overCamY, STAGE::TILE_SIZE / 2 * cam->camDist, GetColor(255, 0, 0), TRUE);
        DrawBox(initPosX - STAGE::TILE_SIZE, initPosY - STAGE::TILE_SIZE, initPosX + STAGE::TILE_SIZE, initPosY + STAGE::TILE_SIZE, GetColor(255, 0, 0), FALSE);
    }
    else
    {
        DrawCircle(x, y, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
        DrawBox(x - STAGE::TILE_SIZE / 2, y - STAGE::TILE_SIZE / 2, x + STAGE::TILE_SIZE / 2, y + STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), FALSE);
    }
    std::string str = std::to_string(cam->overCamX);
    DrawString(x, y, str.c_str(), GetColor(0, 255, 255));
    DrawRotaGraph(transform_.position_.x, transform_.position_.y,rate_,angle_, hArrow_, TRUE);
}

void Hunter::Release()
{
}

bool Hunter::CollisionStage(Stage* stage)
{
    int tileX = x / STAGE::TILE_SIZE;
    int tileY = y / STAGE::TILE_SIZE;

    //if (tileX < 0 || tileX >= STAGE::WIDTH || tileY < 0 || tileY >= STAGE::HEIGHT)
    //{
    //    return false;
    //}

    return stage->GetTile(tileY, tileX) == 1;
}