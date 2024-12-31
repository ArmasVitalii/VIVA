#pragma once

#include "AbstractMage.h"

class AirMage : public AbstractMage
{
public:
    AirMage();
    void getDescription() const override;
    void usePower() const override;
};
