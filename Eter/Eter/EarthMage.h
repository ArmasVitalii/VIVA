#pragma once

#include "AbstractMage.h"

class EarthMage : public AbstractMage
{
public:
    EarthMage();
    void getDescription() const override;
    void usePower() const override;
};
