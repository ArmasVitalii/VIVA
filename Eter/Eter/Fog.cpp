#include "Fog.h"

Fog::Fog()
{
    m_description = "Fog: Play another illusion.";
}

void Fog::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Fog::usePower() const
{
    std::cout << "Fog power activated: Play another illusion." << std::endl;
}
