#include "IceMage.h"

IceMage::IceMage()
{
    m_description = "IceMage: Moves a stack of cards with the opponent's card on top to another empty position on the board.";
}

void IceMage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void IceMage::usePower() const
{
    std::cout << "IceMage uses power to move an opponent's stack of cards!" << std::endl;
}
