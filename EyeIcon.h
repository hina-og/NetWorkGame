#pragma once
#include "Item.h"
class EyeIcon :
    public Item
{
public:
    EyeIcon(GameObject* parent);
    void Initialize() override;
    ~EyeIcon();
    void Release() override;
private:
};

