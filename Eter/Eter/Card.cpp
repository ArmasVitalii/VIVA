#include "Card.h"

Card::Card(uint8_t value, PlayerEnum playerID, bool isIllusion)
	:m_cardValue{ value }, m_playerID{ playerID }, m_isIllusion{ isIllusion }
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

bool Card::isIllusion() const
{
	return m_isIllusion;
}

void Card::discoverIllusion()
{
	m_hasBeenDiscovered = true;
	m_isIllusion = false;
}

uint8_t Card::getRealValue() const
{
	return (m_isIllusion || m_hasBeenDiscovered) ? 1u : m_cardValue;
}
