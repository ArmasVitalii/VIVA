#pragma once

#include "AbstractMagic.h"

class Borders : public AbstractMagic
{
public:
    Borders();
    void getDescription() const override;
    bool usePower(Game& game) override;
};
