#pragma once

#include "AbstractMagic.h"

class Borders : public AbstractMagic
{
public:
    Borders();
    void getDescription() const override;
    void usePower() const override;
};
