#pragma once

#include "AbstractMagic.h"

class StormSurge : public AbstractMagic
{
public:
    StormSurge();
    void getDescription() const override;
    void usePower() const override;
};
