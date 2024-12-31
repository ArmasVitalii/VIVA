#pragma once

#include "AbstractMage.h"

class FireMage : public AbstractMage
{
public:
    FireMage();
    void getDescription() const override;
    void usePower() const override;
};
