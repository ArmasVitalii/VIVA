#pragma once

#include "AbstractMage.h"

class WaterMage : public AbstractMage
{
public:
    WaterMage();
    void getDescription() const override;
    void usePower() const override;
};
