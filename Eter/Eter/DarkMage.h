#pragma once

#include "AbstractMage.h"

class DarkMage : public AbstractMage
{
public:
    DarkMage();
    void getDescription() const override;
    void usePower() const override;
};
