#pragma once

#include "AbstractMagic.h"

class Lava : public AbstractMagic
{
public:
    Lava();
    void getDescription() const override;
    void usePower() const override;
};