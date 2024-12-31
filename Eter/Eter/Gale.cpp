#include "Gale.h"

Gale::Gale()
{
    m_description = "Gale: Moves any visible card horizontally or vertically to a position adjacent to a card with a lower number.";
}

void Gale::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Gale::usePower() const
{
    std::cout << "Gale power activated: Moves a visible card to a new position adjacent to a lower number card." << std::endl;
}
