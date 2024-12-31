#pragma once

#include "AbstractMagic.h"

class Tsunami : public AbstractMagic
{
public:
    Tsunami();
    void getDescription() const override;
    void usePower() const override;
};
