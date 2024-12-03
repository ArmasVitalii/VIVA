#include "Gamemode.h"


Gamemode::Gamemode(bool is4x4, std::list<uint8_t> cardList, uint8_t maxNumberOfGames, bool hasMage, bool hasMagic, bool hasExplosions, bool hasIlusions, bool hasTimer)
	:m_is4x4{ is4x4 },
	m_cardList{ cardList },
	m_maxNumberOfGames{ maxNumberOfGames },
	m_hasMage{ hasMage },
	m_hasMagic{ hasMagic },
	m_hasExplosions{ hasExplosions },
	m_hasIlusions{ hasIlusions },
	m_hasTimer{ hasTimer }
{
}

bool Gamemode::getIs4x4() const
{
	return m_is4x4;
}

const std::list<uint8_t>& Gamemode::getCardList() const
{
	return m_cardList;
}

uint8_t Gamemode::getMaxNumberOfGames() const
{
	return m_maxNumberOfGames;
}

bool Gamemode::gethasMage() const
{
	return m_hasMage;
}

bool Gamemode::gethasMagical() const
{
	return m_hasMagic;
}

bool Gamemode::gethasExplosions() const
{
	return m_hasExplosions;
}

bool Gamemode::gethasIlusions() const
{
	return m_hasIlusions;
}

bool Gamemode::gethasTimer() const
{
	return m_hasTimer;
}
