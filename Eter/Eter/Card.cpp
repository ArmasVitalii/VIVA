#include "Card.h"

Card::Card(int value, bool whoPlayer) :m_value{value}, m_whoPlayed{whoPlayer} {}

bool Card::operator==(const Card& other) const
{
	return (m_value == other.m_value) && (m_whoPlayed == other.m_whoPlayed);
}

const int& Card::getValue() const
{
	return m_value;
}

const bool& Card::getWhoPlayed() const
{
	return m_whoPlayed;
}