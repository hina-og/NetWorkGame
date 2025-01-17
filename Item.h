#pragma once
#include "Engine/GameObject.h"

class Stage;
class Camera;

class Item :
    public GameObject
{
protected:
    int hIcon_;
    XMINT2 graphSize_;
    XMINT2 position_;
    XMINT2 num_;
    bool IsOnLoad_;
    bool IsAlive_;
    Stage* stage;
    Camera* cam;
public:
    Item(GameObject* parent);
    ~Item();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
private:
    int hEyeIcon_;
    int hSpeedUpIcon_;

    XMINT2 EIconPos_;
    XMINT2 SUIconPos_;
    XMINT2 EInum_;
    XMINT2 SUInum_;

    bool IsEIOnLoad_;
    bool IsSUIOnLoad_;

    bool IsAliveEI_;
    bool IsAliveSUI_;

    
};

