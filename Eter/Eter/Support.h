#pragma once

#include "AbstractMagic.h"

class Support : public AbstractMagic
{
public:
    Support();
    void getDescription() const override;
    void usePower() const override;
};
