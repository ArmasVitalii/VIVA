#pragma once

#include "AbstractMagic.h"

class Sparks : public AbstractMagic
{
public:
    Sparks();
    void getDescription() const override;
    void usePower() const override;
};
