#pragma once
#include "Engine/GameObject.h"
class Item :
    public GameObject
{
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
};

