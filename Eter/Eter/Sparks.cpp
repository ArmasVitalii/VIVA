#include "Sparks.h"

Sparks::Sparks()
{
    m_description = "Sparks: Choose any of your own cards covered by the opponent and play it immediately on another position.";
}

void Sparks::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Sparks::usePower() const
{
    std::cout << "Sparks power activated: Choose and play one of your own covered cards immediately on another position." << std::endl;
}
