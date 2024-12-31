#include "AirMage.h"

AirMage::AirMage()
{
    m_description = "AirMage: Transforms an empty space on the board into a pit.";
}

void AirMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void AirMage::usePower() const
{
    std::cout << "AirMage uses power to create a pit!" << std::endl;
}
