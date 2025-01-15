#pragma once

#include "AbstractMagic.h"

class WaterVortex : public AbstractMagic
{
public:
    WaterVortex();
    void getDescription() const override;
    bool usePower(Game& game) override;
};
