#include "ControlledExplosion.h"

ControlledExplosion::ControlledExplosion()
{
    m_description = "ControlledExplosion: The board explodes!";
}

void ControlledExplosion::getDescription() const
{
    std::cout << m_description << std::endl;
}

void ControlledExplosion::usePower() const
{
    std::cout << "ControlledExplosion power activated: The board explodes!" << std::endl;
}
