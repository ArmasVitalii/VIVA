#include "WaterVortex.h"

WaterVortex::WaterVortex()
{
    m_description = "WaterVortex: Move 2 cards from the same row, separated by an empty space, onto that space. The higher numbered card goes on top.";
}

void WaterVortex::getDescription() const
{
    std::cout << m_description << std::endl;
}

void WaterVortex::usePower() const
{
    std::cout << "WaterVortex power activated: Move 2 cards onto an empty space. The higher numbered card goes on top." << std::endl;
}
