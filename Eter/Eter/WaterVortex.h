#pragma once

#include "AbstractMagic.h"

class WaterVortex : public AbstractMagic
{
public:
    WaterVortex();
    void getDescription() const override;
    void usePower() const override;
};
