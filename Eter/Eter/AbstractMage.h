#pragma once

#include <string>
#include <iostream>

class AbstractMage
{
protected:
    std::string m_description;

public:
    AbstractMage() = default;
    virtual ~AbstractMage() = default;
    virtual void getDescription() const = 0;
    virtual void usePower() const = 0;
};
