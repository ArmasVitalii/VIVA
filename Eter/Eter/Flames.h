#pragma once

#include "AbstractMagic.h"

class Flames : public AbstractMagic
{
public:
    Flames();
    void getDescription() const override;
    void usePower() const override;
};
