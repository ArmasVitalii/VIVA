#pragma once

#include "AbstractMage.h"

class IceMage : public AbstractMage
{
public:
    IceMage();
    void getDescription() const override;
    void usePower() const override;
};
