#pragma once

#include "AbstractMagic.h"

class FromAshes : public AbstractMagic
{
public:
    FromAshes();
    void getDescription() const override;
    bool usePower(Game& game) override;
};
