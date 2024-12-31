#pragma once

#include <string>
#include <iostream>

class AbstractMagic
{
protected:
    std::string m_description;
    bool        m_hasBeenUsed{false};
public:
    AbstractMagic() = default;
    virtual ~AbstractMagic() = default;
    virtual void getDescription() const = 0;
    virtual void usePower() const = 0;
    virtual bool hasBeenUsed() const;
};
