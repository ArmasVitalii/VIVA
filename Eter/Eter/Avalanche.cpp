#include "Avalanche.h"

Avalanche::Avalanche()
{
    m_description = "Avalanche: Choose two adjacent stacks horizontally/vertically and shift them by one position towards an empty space.";
}

void Avalanche::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Avalanche::usePower() const
{
    std::cout << "Avalanche power activated: Shift two adjacent stacks by one position towards an empty space." << std::endl;
}
