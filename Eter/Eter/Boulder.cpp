#include "Boulder.h"

Boulder::Boulder()
{
    m_description = "Boulder: Cover any illusion with a card from your hand without turning the illusion face up.";
}

void Boulder::getDescription() const
{
    std::cout << m_description << std::endl;
}

void Boulder::usePower() const
{
    std::cout << "Boulder power activated: Cover any illusion with a card from your hand without turning the illusion face up." << std::endl;
}
