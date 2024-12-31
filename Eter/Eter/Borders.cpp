#include "Borders.h"

Borders::Borders()
{
    m_description = "Borders: Place a neutral card on the board defining at least one boundary. Then play a card from your hand.";
}

void Borders::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Borders::usePower() const
{
    std::cout << "Borders power activated: Place a neutral card and then play a card from your hand." << std::endl;
}
