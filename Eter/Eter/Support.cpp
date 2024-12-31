#include "Support.h"

Support::Support()
{
    m_description = "Support: Increase the value of one of your own cards (1/2/3) by 1.";
}

void Support::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Support::usePower() const
{
    std::cout << "Support power activated: Increase the value of one of your own cards by 1." << std::endl;
}
