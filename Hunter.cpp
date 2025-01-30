#include "Hunter.h"
#include "Camera.h"
#include "Stage.h"
#include "Player.h"

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

    // ステージとの当たり判定のチェック
    Stage* stage = (Stage*)FindObject("Stage");
    if (stage != nullptr && CollisionStage(stage))
    {
        // 壁に衝突した場合の処理
        x = prevX;
        y = prevY;
    }
}

void Hunter::Draw()
{
    Camera* cam = (Camera*)FindObject("Camera");
    if (cam == nullptr) return;

    if (cam->isZoom_)
    {
        DrawCircle(initPosX, initPosY, STAGE::TILE_SIZE / 2 * cam->camDist, GetColor(255, 0, 0), TRUE);
        DrawBox(initPosX - STAGE::TILE_SIZE, initPosY - STAGE::TILE_SIZE, initPosX + STAGE::TILE_SIZE, initPosY + STAGE::TILE_SIZE, GetColor(255, 0, 0), FALSE);
    }
    else
    {
        DrawCircle(x - cam->camX, y - cam->camY, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
        DrawBox(x - cam->camX - STAGE::TILE_SIZE / 2, y - cam->camY - STAGE::TILE_SIZE / 2, x - cam->camX + STAGE::TILE_SIZE / 2, y - cam->camY + STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), FALSE);
    }
}

void Hunter::Release()
{
}

bool Hunter::CollisionStage(Stage* stage)
{
    int tileX = x / STAGE::TILE_SIZE;
    int tileY = y / STAGE::TILE_SIZE;

    if (tileX < 0 || tileX >= STAGE::WIDTH || tileY < 0 || tileY >= STAGE::HEIGHT)
    {
        return false;
    }

    return stage->GetTile(tileY, tileX) == 1;
}