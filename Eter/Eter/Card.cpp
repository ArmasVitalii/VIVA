#include "Card.h"

Card::Card(uint8_t value, PlayerEnum playerID)
	:m_cardValue{ value }, m_playerID{ playerID }
{
}

bool Card::operator==(const Card& other) const
{
	return (m_cardValue == other.m_cardValue) && (m_playerID == other.m_playerID);
}

uint8_t Card::getValue() const
{
	return m_cardValue;
}

PlayerEnum Card::getPlayerID() const
{
	return m_playerID;
}