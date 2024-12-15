#include "FireMage.h"

FireMage::FireMage()
{
    m_name = "Fire Mage";
    m_description = "A mage who wields the power of fire.";
}

void FireMage::usePower() const
{
    std::cout << m_name << " unleashes a blazing fireball!" << std::endl;
}
