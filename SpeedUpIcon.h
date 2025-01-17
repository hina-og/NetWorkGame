#pragma once
#include "Item.h"
class SpeedUpIcon :
    public Item
{
public:
    SpeedUpIcon(GameObject* parent);
    ~SpeedUpIcon();
    void Initialize() override;
    void Release() override;
private:
};

