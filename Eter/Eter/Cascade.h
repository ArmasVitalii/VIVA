#pragma once

#include "AbstractMagic.h"

class Cascade : public AbstractMagic
{
public:
    Cascade();
    void getDescription() const override;
    void usePower() const override;
};
