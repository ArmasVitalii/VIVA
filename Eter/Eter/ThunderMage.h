#pragma once

#include "AbstractMage.h"

class ThunderMage : public AbstractMage
{
public:
    ThunderMage();
    void getDescription() const override;
    bool usePower(Game& game) const override;
};
