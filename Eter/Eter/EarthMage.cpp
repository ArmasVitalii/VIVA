#include "EarthMage.h"

EarthMage::EarthMage()
{
    m_name = "Earth Mage";
    m_description = "A mage who controls the forces of the earth.";
}

void EarthMage::usePower() const
{
    std::cout << m_name << " raises an unyielding stone wall!" << std::endl;
}
