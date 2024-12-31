#pragma once

#include "AbstractMagic.h"

class FromAshes : public AbstractMagic
{
public:
    FromAshes();
    void getDescription() const override;
    void usePower() const override;
};
