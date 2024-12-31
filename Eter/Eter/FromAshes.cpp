#include "FromAshes.h"

FromAshes::FromAshes()
{
    m_description = "FromAshes: Choose one of your own cards removed from the game and play it immediately.";
}

void FromAshes::getDescription() const
{
    std::cout << m_description << std::endl;
}

void FromAshes::usePower() const
{
    std::cout << "FromAshes power activated: Choose and play one of your own removed cards immediately." << std::endl;
}
