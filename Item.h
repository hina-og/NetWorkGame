#pragma once
#include "Engine/GameObject.h"

class Stage;
class Camera;

class Item :
    public GameObject
{
protected:
    int hIcon_;
    int state_;
    std::string fileName_;
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
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Draw() override;
    virtual void Release() override;

    int GetState() { return state_; }
private:
};

