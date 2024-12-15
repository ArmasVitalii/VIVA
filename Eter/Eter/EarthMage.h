#pragma once

#include "AbstractMage.h"

class EarthMage : public AbstractMage
{
public:
    EarthMage();
    void usePower() const override;
};
