#pragma once

#include "AbstractMagic.h"

class Storm : public AbstractMagic
{
public:
    Storm();
    void getDescription() const override;
    void usePower() const override;
};
