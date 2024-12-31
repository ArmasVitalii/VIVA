#include "Flames.h"

Flames::Flames()
{
    m_description = "Flames: Turns the opponent's illusion face up. Then play a card on any position on the board.";
}

void Flames::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Flames::usePower() const
{
    std::cout << "Flames power activated: Turns the opponent's illusion face up and play a card." << std::endl;
}
