#pragma once
#include "Item.h"
class EyeIcon :
    public Item
{
public:
    EyeIcon(GameObject* parent);
    ~EyeIcon();
    void Initialize() override;
    void Update() override;
    void Release() override;
private:
};

