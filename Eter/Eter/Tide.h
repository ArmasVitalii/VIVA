#pragma once

#include "AbstractMagic.h"

class Tide : public AbstractMagic
{
public:
    Tide();
    void getDescription() const override;
    void usePower() const override;
};
