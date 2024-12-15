#pragma once

#include "AbstractMage.h"

class FireMage : public AbstractMage
{
public:
    FireMage();
    void usePower() const override;
};
