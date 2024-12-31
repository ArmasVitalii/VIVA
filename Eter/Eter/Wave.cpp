#include "Wave.h"

Wave::Wave()
{
    m_description = "Wave: Move a stack to an adjacent empty position. Play a card on the new empty position.";
}

void Wave::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Wave::usePower() const
{
    std::cout << "Wave power activated: Move a stack to an adjacent empty position. Play a card on the new empty position." << std::endl;
}
