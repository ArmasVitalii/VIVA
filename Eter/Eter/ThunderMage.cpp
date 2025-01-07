#include "ThunderMage.h"

ThunderMage::ThunderMage()
{
    m_description = "ThunderMage: Moves any row at the edge of the board to another edge. The moved row must occupy at least 3 positions.";
}

void ThunderMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

bool ThunderMage::usePower(Game& game) const
{
    std::cout << "ThunderMage uses power to move a row to another edge!" << std::endl;
}
