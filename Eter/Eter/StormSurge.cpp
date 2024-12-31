#include "StormSurge.h"

StormSurge::StormSurge()
{
    m_description = "StormSurge: Removes a stack of cards containing 2 or more cards from the game.";
}

void StormSurge::getDescription() const
{
    std::cout << m_description << std::endl;
}

void StormSurge::usePower() const
{
    std::cout << "StormSurge power activated: Removes a stack of cards containing 2 or more cards from the game." << std::endl;
}
