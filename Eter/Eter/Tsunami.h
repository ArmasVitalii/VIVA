#pragma once

#include "AbstractMagic.h"

class Tsunami : public AbstractMagic
{
public:
    Tsunami();
    void getDescription() const override;
    bool usePower(Game& game) override;
};
