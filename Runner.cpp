#include "Runner.h"
#include "Hunter.h"
#include "Stage.h"

Runner::Runner(GameObject* parent)
{
    objectName_ = "Runner";
    player_ = false;
    client = new Client();
    pData.playerID = 0;

    me = true;
}

void Runner::Initialize()
{
    transform_.position_.x = initPosX;
    transform_.position_.y = initPosY;

    speed_ = 1;
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
    pData.job = 1;
    pData.x = transform_.position_.x;
    pData.y = transform_.position_.y;
    pData.state = 1;

   
    if (player_) 
    { //自身が操作するplayerならデータを送って受け取る
        client->SetSendData(pData);
        client->Connect();
        client->SetPlayerData(pData);
    }

    if (client->AddPlayerNum() > 0)//通信しているプレイヤーが増えたら
    {
        int addNum = 0;
        for (int i = 0; i < client->AddPlayerNum(); i++)
        {
            for (int prev = 0; prev < prevPlayerList.size(); prev++)
            {
                for (int now = 0; now < playerList.size(); now++)
                {
                    //前のフレームですでに通信済みのIDがあれば
                    if (prevPlayerList[prev].playerID != playerList[now].playerID)
                    {
                        continue;
                    }
                    addNum = now;
                    break;
                }
                if (addNum != 0)
                    break;
            }
            if (playerList[addNum].job == 0)
            {
                Hunter* hunter = Instantiate<Hunter>(this);
                hunter->SetData(playerList[addNum]);
                hunter->me = false;
            }
            else
            {
                Runner* runner = Instantiate<Runner>(this);
                runner->SetData(playerList[addNum]);
                runner->me = false;
            }
        }
    }
    prevPlayerList = playerList;
}

void Runner::Draw()
{
    DrawCircle(transform_.position_.x, transform_.position_.y, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
    for (int i = 0; i < playerList.size(); i++)
    {
        if (playerList[i].job == 0)
        {
            DrawCircle(playerList[i].x, playerList[i].y, STAGE::TILE_SIZE / 2, GetColor(0, 0, 255), TRUE);
        }
        else
        {
            DrawCircle(playerList[i].x, playerList[i].y, STAGE::TILE_SIZE / 2, GetColor(255, 0, 0), TRUE);
        }   
    }
}

void Runner::Release()
{
}
