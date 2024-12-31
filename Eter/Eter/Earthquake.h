#pragma once

#include "AbstractMagic.h"

class Earthquake : public AbstractMagic
{
public:
    Earthquake();
    void getDescription() const override;
    void usePower() const override;
};
