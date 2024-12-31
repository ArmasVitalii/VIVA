#include "Mirage.h"

Mirage::Mirage()
{
    m_description = "Mirage: Replace your placed illusion with another illusion.";
}

void Mirage::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Mirage::usePower() const
{
    std::cout << "Mirage power activated: Replace your illusion with another illusion." << std::endl;
}
