#include "Destruction.h"

Destruction::Destruction()
{
    m_description = "Destruction: Removes the last card played by the opponent from the game.";
}

void Destruction::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Destruction::usePower() const
{
    std::cout << "Destruction power activated: Removes the last card played by the opponent." << std::endl;
}
