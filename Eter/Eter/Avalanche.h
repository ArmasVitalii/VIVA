#pragma once

#include "AbstractMagic.h"

class Avalanche : public AbstractMagic
{
public:
    Avalanche();
    void getDescription() const override;
    void usePower() const override;
};
