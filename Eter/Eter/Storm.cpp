#include "Storm.h"

Storm::Storm()
{
    m_description = "Storm: All cards covered by other cards return to their owners' hands.";
}

void Storm::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Storm::usePower() const
{
    std::cout << "Storm power activated: All covered cards return to their owners' hands." << std::endl;
}
