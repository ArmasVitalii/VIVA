#include "Tsunami.h"

Tsunami::Tsunami()
{
    m_description = "Tsunami: Choose a row. The opponent cannot place cards on that row during their next turn.";
}

void Tsunami::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Tsunami::usePower() const
{
    std::cout << "Tsunami power activated: The opponent cannot place cards on the chosen row during their next turn." << std::endl;
}
