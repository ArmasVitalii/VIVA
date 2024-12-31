#include "Hurricane.h"

Hurricane::Hurricane()
{
    m_description = "Hurricane: Shifts a fully occupied row by one position in the desired direction.";
}

void Hurricane::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Hurricane::usePower() const
{
    std::cout << "Hurricane power activated: Shifts a row by one position." << std::endl;
}
