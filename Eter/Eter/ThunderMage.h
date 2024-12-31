#pragma once

#include "AbstractMage.h"

class ThunderMage : public AbstractMage
{
public:
    ThunderMage();
    void getDescription() const override;
    void usePower() const override;
};
