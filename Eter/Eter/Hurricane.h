#pragma once

#include "AbstractMagic.h"

class Hurricane : public AbstractMagic
{
public:
    Hurricane();
    void getDescription() const override;
    void usePower() const override;
};
