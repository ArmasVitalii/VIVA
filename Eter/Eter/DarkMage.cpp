#include "DarkMage.h"

DarkMage::DarkMage()
{
    m_description = "DarkMage: Moves a stack of cards with one's own card on top to another empty position on the board.";
}

void DarkMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void DarkMage::usePower() const
{
    std::cout << "DarkMage uses power to move a stack of cards!" << std::endl;
}
